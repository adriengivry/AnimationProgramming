/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include <Engine/Engine.h>
#include <Engine/Simulation.h>

#include "AnimationProgramming/Core/AnimationEngine.h"

void AnimationProgramming::Core::AnimationEngine::Run(ISimulation& p_simulation, uint16_t p_windowWidth, uint16_t p_windowHeight)
{
	::Run(&p_simulation, p_windowWidth, p_windowHeight);
}

void AnimationProgramming::Core::AnimationEngine::SetSkinningPose(std::vector<AltMath::Matrix4f>& p_bonesTransformations)
{
	std::vector<float> gpuData;
	uint32_t boneCount = static_cast<uint32_t>(p_bonesTransformations.size());

	for (AltMath::Matrix4f& boneTransformation : p_bonesTransformations)
		for (uint8_t i = 0; i < 16; ++i)
			gpuData.push_back(boneTransformation.ToArray()[i]);

	::SetSkinningPose(gpuData.data(), boneCount);
}

uint32_t AnimationProgramming::Core::AnimationEngine::GetSkeletonBoneCount()
{
	/* The minus 6 here is used to ignore IK (Can crash if I don't) */
	return static_cast<uint32_t>(::GetSkeletonBoneCount() - 6);
}

std::string AnimationProgramming::Core::AnimationEngine::GetSkeletonBoneName(uint32_t p_boneIndex)
{
	return ::GetSkeletonBoneName(static_cast<int>(p_boneIndex));
}

uint32_t AnimationProgramming::Core::AnimationEngine::GetSkeletonBoneIndex(const std::string& p_boneName)
{
	return static_cast<uint32_t>(::GetSkeletonBoneIndex(p_boneName.c_str()));
}

int32_t AnimationProgramming::Core::AnimationEngine::GetSkeletonBoneParentIndex(uint32_t p_boneIndex)
{
	return static_cast<int32_t>(::GetSkeletonBoneParentIndex(p_boneIndex));
}

AnimationProgramming::Data::Transformation AnimationProgramming::Core::AnimationEngine::GetSkeletonBindPoseBoneLocalTransform(uint32_t p_boneIndex)
{
	float x, y, z, qx, qy, qz, qw;
	::GetSkeletonBoneLocalBindTransform(static_cast<int>(p_boneIndex), x, y, z, qw, qx, qy, qz);

	return std::make_pair(AltMath::Vector3f(x, y, z), AltMath::Quaternion(qx, qy, qz, qw));
}

AnimationProgramming::Data::Transformation AnimationProgramming::Core::AnimationEngine::GetSkeletonAnimationBoneLocalTransform(uint32_t p_boneIndex, const std::string& p_animationName, uint32_t p_keyFrame)
{
	float x, y, z, qx, qy, qz, qw;
	::GetAnimLocalBoneTransform(p_animationName.c_str(), static_cast<int>(p_boneIndex), static_cast<int>(p_keyFrame), x, y, z, qw, qx, qy, qz);

	return std::make_pair(AltMath::Vector3f(x, y, z), AltMath::Quaternion(qx, qy, qz, qw));
}

uint32_t AnimationProgramming::Core::AnimationEngine::GetAnimationKeyFrameCount(const std::string& p_animationName)
{
	return static_cast<uint32_t>(::GetAnimKeyCount(p_animationName.c_str()));
}
