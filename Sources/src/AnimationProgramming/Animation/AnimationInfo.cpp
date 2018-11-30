/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Core/AnimationEngine.h"

#include "AnimationProgramming/Animation/AnimationInfo.h"

AnimationProgramming::Animation::AnimationInfo::AnimationInfo(uint32_t p_frames) :
	m_bonesCount(Core::AnimationEngine::GetSkeletonBoneCount())
{
	m_startKey = 0;
	m_endKey = p_frames - 1;

	for (uint32_t i = 0; i < p_frames; ++i)
	{
		std::vector<Data::Transformation> boneTransformation;

		for (uint32_t boneIndex = 0; boneIndex < m_bonesCount; ++boneIndex)
			boneTransformation.emplace_back(AltMath::Vector3f(0.0f, 0.0f, 0.0f), AltMath::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));

		m_animationTransformations.push_back(boneTransformation);
	}
}

AnimationProgramming::Animation::AnimationInfo::AnimationInfo(const std::string & p_animationName) :
	m_bonesCount(Core::AnimationEngine::GetSkeletonBoneCount()),
	m_keyCount(Core::AnimationEngine::GetAnimationKeyFrameCount(p_animationName)),
	m_startKey(0),
	m_endKey(m_keyCount - 1)
{
	for (uint32_t currentKey = 0; currentKey < m_keyCount; ++currentKey)
	{
		std::vector<Data::Transformation> boneTransformations;

		for (uint32_t boneID = 0; boneID < m_bonesCount; ++boneID)
			boneTransformations.push_back(Core::AnimationEngine::GetSkeletonAnimationBoneLocalTransform(boneID, p_animationName, currentKey));

		m_animationTransformations.push_back(boneTransformations);
	}
}

void AnimationProgramming::Animation::AnimationInfo::SetBoneRelativeTransformation(uint32_t p_boneIndex, uint32_t p_frame, Data::Transformation p_relativeTransformations)
{
	m_animationTransformations[p_frame][p_boneIndex] = p_relativeTransformations;
}

AnimationProgramming::Data::Transformation AnimationProgramming::Animation::AnimationInfo::GetBoneTransformations(uint32_t p_boneID, uint32_t p_keyFrame) const
{
	return m_animationTransformations[p_keyFrame][p_boneID];
}

uint32_t AnimationProgramming::Animation::AnimationInfo::GetStartKey(bool p_excludeZero) const
{
	return m_startKey + (p_excludeZero ? 1 : 0);
}

uint32_t AnimationProgramming::Animation::AnimationInfo::GetEndKey() const
{
	return m_endKey;
}

uint32_t AnimationProgramming::Animation::AnimationInfo::GetNextKey(uint32_t p_key, bool p_excludeZero) const
{
	return p_key == GetEndKey() ? GetStartKey(p_excludeZero) : p_key + 1;
}

uint32_t AnimationProgramming::Animation::AnimationInfo::GetPreviousKey(uint32_t p_key, bool p_excludeZero) const
{
	return p_key == GetStartKey(p_excludeZero) ? GetEndKey() : p_key - 1;
}

uint32_t AnimationProgramming::Animation::AnimationInfo::GetBonesCount() const
{
	return m_bonesCount;
}
