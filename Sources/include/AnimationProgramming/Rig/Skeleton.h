/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _SKELETON_H
#define _SKELETON_H

#include <string>
#include <vector>

#include "AnimationProgramming/Core/AnimationEngine.h"
#include "AnimationProgramming/Rig/Bone.h"

namespace AnimationProgramming::Rig
{
	/**
	* Represents a set of bones
	*/
	class Skeleton final
	{
	public:
		/**
		* Constructor of the skeleton
		*/
		Skeleton() = default;

		/**
		* Recreate the skeleton hierarchy using the bind pose
		*/
		void CreateSkeletonFromBindPose();

		/**
		* Create the bones, following the directives of the BonesHierarchy (Must be created before calling CreateBone())
		*/
		void CreateBones();

		/**
		* Defines parent/child relations for each bones
		*/
		void DefineBonesParent();

		/**
		* Get a vector of bones
		*/
		std::vector<Bone>& GetBones();

	private:
		std::vector<Bone> m_bones;
	};
}

#endif // _SKELETON_H