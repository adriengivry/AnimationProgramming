/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ANIMATION_ENGINE_H
#define _ANIMATION_ENGINE_H

#include <AltMath/AltMath.h>

#include "AnimationProgramming/Data/Transform.h"

/* Forward declaration in global namespace */
class ISimulation;

namespace AnimationProgramming::Core
{
	/**
	* A small wrapper for the Engine given for this project.
	* It adds some comments to every methods and rewrite methods in a modern C++ style
	*/
	class AnimationEngine final
	{
	public:
		/**
		* Deleted constructor to prevent instancing this static class
		*/
		AnimationEngine() = delete;

		/**
		* Run the engine
		* @param p_simulation
		* @param p_windowWidth
		* @param p_windowHeight
		*/
		static void Run(ISimulation& p_simulation, uint16_t p_windowWidth, uint16_t p_windowHeight);

		/**
		* Set a skinning pose for the given skeleton
		* @param p_boneIndex
		* @param p_localMatrix
		*/
		static void SetSkinningPose(std::vector<AltMath::Matrix4f>& p_bonesTransformations);

		/**
		* Return the current skeleton bone count
		*/
		static uint32_t GetSkeletonBoneCount();

		/**
		* Return a skeleton bone name
		* @param p_boneIndex
		*/
		static std::string GetSkeletonBoneName(uint32_t p_boneIndex);

		/**
		* Return the skeleton bone index corresponding to the given name
		* @param p_boneName
		*/
		static uint32_t GetSkeletonBoneIndex(const std::string& p_boneName);

		/**
		* Return the index of the parent bone
		* @param p_boneIndex (-1 if the bone has no parent)
		*/
		static int32_t GetSkeletonBoneParentIndex(uint32_t p_boneIndex);

		/**
		* Get the local transform information about the given bone index for the Bind-Pose (alias T-Pose/Reset-Pose)
		* @param p_boneIndex
		*/
		static Data::Transformation GetSkeletonBindPoseBoneLocalTransform(uint32_t p_boneIndex);

		/**
		* Get the local transform information about the given bone index for the given animation at the given key frame
		* @param p_boneIndex
		* @param p_animationName
		* @param p_keyFrame
		*/
		static Data::Transformation GetSkeletonAnimationBoneLocalTransform(uint32_t p_boneIndex, const std::string& p_animationName, uint32_t p_keyFrame);

		/**
		* Return the number of key frames of the given animation
		* @param p_animationName
		*/
		static uint32_t GetAnimationKeyFrameCount(const std::string& p_animationName);
	};
}

#endif // _ANIMATION_ENGINE_H