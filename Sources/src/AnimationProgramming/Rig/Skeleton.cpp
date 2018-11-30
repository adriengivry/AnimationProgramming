/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Rig/Skeleton.h"

void AnimationProgramming::Rig::Skeleton::CreateSkeletonFromBindPose()
{
	CreateBones();
	DefineBonesParent();
}

void AnimationProgramming::Rig::Skeleton::CreateBones()
{
	for (uint32_t boneIndex = 0; boneIndex < Core::AnimationEngine::GetSkeletonBoneCount(); ++boneIndex)
	{
		auto[position, rotation] = Core::AnimationEngine::GetSkeletonBindPoseBoneLocalTransform(boneIndex);
		std::string boneName = Core::AnimationEngine::GetSkeletonBoneName(boneIndex);
		m_bones.emplace_back(boneName, boneIndex, position, rotation);
	}
}

void AnimationProgramming::Rig::Skeleton::DefineBonesParent()
{
	for (Bone& bone : m_bones)
	{
		int32_t parentIndex = Core::AnimationEngine::GetSkeletonBoneParentIndex(bone.GetIndex());

		if (parentIndex != -1)
			bone.SetParent(m_bones[parentIndex]);
	}
}

std::vector<AnimationProgramming::Rig::Bone>& AnimationProgramming::Rig::Skeleton::GetBones()
{
	return m_bones;
}