/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Animation/Animator.h"
#include "AnimationProgramming/Tools/IniManager.h"

AnimationProgramming::Animation::Animator::Animator(Rig::Skeleton & p_skeleton) :
	m_skeleton(p_skeleton)
{
	/* Listening for FrameChangedEvent allows the animator to update his data only when he needs to */
	m_timeline.FrameChangedEvent.AddListener(std::bind(&Animator::UpdateFrameTransformations, this));
}

bool AnimationProgramming::Animation::Animator::HasAnimation() const
{
	return m_currentAnimation != nullptr;
}

AnimationProgramming::Animation::Timeline& AnimationProgramming::Animation::Animator::GetTimeline()
{
	return m_timeline;
}

void AnimationProgramming::Animation::Animator::SetGlobalSpeedCoefficient(float p_coefficient)
{
	m_globalSpeedCoefficient = p_coefficient;
}

float AnimationProgramming::Animation::Animator::GetGlobalSpeedCoefficient()
{
	return m_globalSpeedCoefficient;
}

void AnimationProgramming::Animation::Animator::PlayAnimation(Animation::AnimationInstance& p_toPlay)
{
	/* Verify if we should play a transition before playing the new animation */
	bool willingForTransition = HasAnimation() && !m_timeline.GetEffector(ETimelineEffector::IGNORE_TRANSITIONING);

	/** 
	* The previous alpha is used to re-caclulate the start point of the transition
	* (We use the actual interpolation result as the transition starting point)
	*/
	float previousAlpha = m_timeline.CalculateInterpolationAlpha();

	m_currentAnimation = &p_toPlay;
	m_timeline.SyncToAnimation(p_toPlay);
	m_timeline.Reset();

	if (willingForTransition)
	{
		/* Prepare and play the new animation WITH transition */
		CalculateTransitionStartAndEndPoint(previousAlpha);
		m_timeline.PlayTransition(p_toPlay.transitionDuration);
	}
	else
	{
		/* Prepare and play the new animation WITHOUT transition */
		UpdateFrameTransformations();
		m_timeline.Play();
	}
}

void AnimationProgramming::Animation::Animator::StopAnimation()
{
	/* Clear animation informations */
	m_currentKeyFrameTransformations.clear();
	m_nextKeyFrameTransformations.clear();

	/* Remove the current animation */
	m_currentAnimation = nullptr;

	/* Pause the timeline */
	m_timeline.Pause();
	
	/* Reset the skeleton to his bind pose */
	ApplyBindPoseToSkeleton();

	/* Send the data*/
	SendSkinningMatricesToGPU();
}

void AnimationProgramming::Animation::Animator::Update(float p_deltaTime)
{
	if (HasAnimation())
	{
		m_timeline.Update(p_deltaTime * m_globalSpeedCoefficient * m_currentAnimation->speedCoefficient);
		ApplyAnimationToSkeleton();
		SendSkinningMatricesToGPU();
	}
}

void AnimationProgramming::Animation::Animator::UpdateFrameTransformations()
{
	m_currentKeyFrameTransformations.clear();
	m_nextKeyFrameTransformations.clear();

	for (Rig::Bone& bone : m_skeleton.GetBones())
	{
		const Animation::AnimationInfo& animationInfo = m_currentAnimation->attachedAnimation;

		m_currentKeyFrameTransformations.push_back(animationInfo.GetBoneTransformations(bone.GetIndex(), m_timeline.GetCurrentKeyFrame()));
		m_nextKeyFrameTransformations.push_back(animationInfo.GetBoneTransformations(bone.GetIndex(), m_timeline.GetNextKeyFrame()));
	}
}

void AnimationProgramming::Animation::Animator::CalculateTransitionStartAndEndPoint(float p_previousAlpha)
{
	for (Rig::Bone& bone : m_skeleton.GetBones())
	{
		auto[startPosition, startRotation] = CalculateInterpolation(bone.GetIndex(), p_previousAlpha);
		m_currentKeyFrameTransformations[bone.GetIndex()].first = startPosition;
		m_currentKeyFrameTransformations[bone.GetIndex()].second = startRotation;

		auto[newEndPosition, newEndRotation] = m_currentAnimation->attachedAnimation.GetBoneTransformations(bone.GetIndex(), m_timeline.GetFirstKeyFrame());
		m_nextKeyFrameTransformations[bone.GetIndex()].first = newEndPosition;
		m_nextKeyFrameTransformations[bone.GetIndex()].second = newEndRotation;
	}
}

AnimationProgramming::Data::Transformation AnimationProgramming::Animation::Animator::CalculateInterpolation(uint32_t p_boneIndex, float p_alpha)
{
	/* Get the start and end informations used for the interpolation */
	AltMath::Vector3f& startPosition = m_currentKeyFrameTransformations[p_boneIndex].first;
	AltMath::Vector3f& endPosition = m_nextKeyFrameTransformations[p_boneIndex].first;
	AltMath::Quaternion& startRotation = m_currentKeyFrameTransformations[p_boneIndex].second;
	AltMath::Quaternion& endRotation = m_nextKeyFrameTransformations[p_boneIndex].second;

	/* Calculate the actual interpolation */
	AltMath::Vector3f currentPosition = AltMath::Vector3f::Lerp(startPosition, endPosition, p_alpha);
	AltMath::Quaternion currentRotation = AltMath::Quaternion::Slerp(startRotation, endRotation, p_alpha);

	return std::make_pair(currentPosition, currentRotation);
}

void AnimationProgramming::Animation::Animator::ApplyAnimationToSkeleton()
{
	for (Rig::Bone& bone : m_skeleton.GetBones())
	{
		float alpha = m_timeline.CalculateInterpolationAlpha();
		auto[currentPosition, currentRotation] = CalculateInterpolation(bone.GetIndex(), alpha);
		bone.SetRelativePositionAndRotation(currentPosition, currentRotation);
	}
}

void AnimationProgramming::Animation::Animator::ApplyBindPoseToSkeleton()
{
	for (Rig::Bone& bone : m_skeleton.GetBones())
		bone.ResetPositionAndRotation();
}

void AnimationProgramming::Animation::Animator::SendSkinningMatricesToGPU()
{
	/* Prepare a set of data to send to GPU */
	std::vector<AltMath::Matrix4f> skinningPoseData;

	for (Rig::Bone& bone : m_skeleton.GetBones())
	{
		/* We ignore IK for now */
		if (!bone.IsIK())
		{
			AltMath::Matrix4f boneCurrentWorldMatrix = bone.GetTransform().GetWorldMatrix();
			AltMath::Matrix4f boneDefaultWorldMatrix = bone.GetDefaultTransform().GetWorldMatrix();

			/* The GPU is waiting for matrices resulting from : BoneCurrentWorldMatrix * Inverse(BoneTPoseWorldMatrix) */
			skinningPoseData.push_back(boneCurrentWorldMatrix * boneDefaultWorldMatrix.Inverse());
		}
	}

	/* Send the actual data to GPU */
	Core::AnimationEngine::SetSkinningPose(skinningPoseData);
}