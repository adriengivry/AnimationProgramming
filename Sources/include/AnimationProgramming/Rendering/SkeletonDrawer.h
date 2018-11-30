/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SKELETONDRAWER_H
#define _SKELETONDRAWER_H

#include "AnimationProgramming/Rendering/IDrawer.h"
#include "AnimationProgramming/Rig/Skeleton.h"
#include "AnimationProgramming/Rig/Bone.h"

namespace AnimationProgramming::Rendering
{
	/**
	* SkeletonDrawer is a class able to render skeletons in world space
	*/
	class SkeletonDrawer final : public IDrawer<Rig::Skeleton>
	{
	public:
		/**
		* Constructor of the SkeletonDrawer class
		* @param p_defaultBoneColor
		* @param p_rootBoneColor
		* @param p_jointColor
		*/
		SkeletonDrawer(const Data::Color& p_defaultBoneColor, const Data::Color& p_rootBoneColor, const Data::Color& p_jointColor, float p_boneSize);

		/**
		* Draw the given skeleton in world space at the given location
		* @param p_skeleton
		* @param p_worldPosition
		*/
		virtual void Draw(const Rig::Skeleton& p_skeleton, const AltMath::Vector3f& p_worldPosition) override;

	private:
		const Data::Color m_defaultBoneColor;
		const Data::Color m_rootBoneColor;
		const Data::Color m_jointColor;
		const float m_boneSize;
	};
}

#endif // _SKELETONDRAWER_H