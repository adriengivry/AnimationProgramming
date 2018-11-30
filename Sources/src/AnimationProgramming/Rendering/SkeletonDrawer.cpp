/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Rendering/SkeletonDrawer.h"

AnimationProgramming::Rendering::SkeletonDrawer::SkeletonDrawer(const Data::Color& p_defaultBoneColor, const Data::Color& p_rootBoneColor, const Data::Color& p_jointColor, float p_boneSize) :
	m_defaultBoneColor(p_defaultBoneColor),
	m_rootBoneColor(p_rootBoneColor),
	m_jointColor(p_jointColor),
	m_boneSize(p_boneSize)
{
}

void AnimationProgramming::Rendering::SkeletonDrawer::Draw(const Rig::Skeleton& p_skeleton, const AltMath::Vector3f & p_worldPosition)
{
	Rig::Skeleton* skeleton = const_cast<Rig::Skeleton*>(&p_skeleton);

	for (Rig::Bone& bone : skeleton->GetBones())
	{
		if (!bone.IsIK())
		{
			AltMath::Vector3f bonePosition = bone.GetTransform().GetWorldPosition();
			AltMath::Vector3f parentBonePosition = bone.HasParent() ? bone.GetParent().GetTransform().GetWorldPosition() : bonePosition;

			Rendering::Renderer::DrawStar(bonePosition + p_worldPosition, bone.IsRoot() ? m_rootBoneColor : m_defaultBoneColor, 5.0f);
			Rendering::Renderer::DrawLine(bonePosition + p_worldPosition, parentBonePosition + p_worldPosition, m_jointColor);
		}
	}
}
