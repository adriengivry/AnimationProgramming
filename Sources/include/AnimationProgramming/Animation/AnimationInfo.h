/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ANIMATIONINFO_H
#define _ANIMATIONINFO_H

#include <vector>

#include <AltMath/AltMath.h>

#include "AnimationProgramming/Data/Transform.h"

namespace AnimationProgramming::Animation
{
	/**
	* Handle data about an animation
	*/
	class AnimationInfo final
	{
	public:
		/**
		* Create an empty animation data set with a given length in frames
		* @param p_frames
		*/
		AnimationInfo(uint32_t p_frames);

		/**
		* Create an animation data set using a string referencing a pre-loaded animation in WhiteBoxEngine
		* @param p_animationName
		*/
		AnimationInfo(const std::string& p_animationName);

		/**
		* Set a transformation for the given bone index at the given frame
		* @param p_boneIndex
		* @param p_frame
		* @param p_relativeTransformation
		*/
		void SetBoneRelativeTransformation(uint32_t p_boneIndex, uint32_t p_frame, Data::Transformation p_relativeTransformations);

		/**
		* Return a position and a rotation about the given bone for the given key frame of the animation
		* @param p_boneID
		* @param p_keyFrame
		*/
		Data::Transformation GetBoneTransformations(uint32_t p_boneID, uint32_t p_keyFrame) const;

		/**
		* Return the start key of the animation
		* @param p_excludeZero
		*/
		uint32_t GetStartKey(bool p_excludeZero = false) const;

		/**
		* Return the end key of the animation
		*/
		uint32_t GetEndKey() const;

		/**
		* Return the key following the given one
		* @param p_key
		* @param p_excludeZero
		*/
		uint32_t GetNextKey(uint32_t p_key, bool p_excludeZero = false) const;

		/**
		* Return the key preceding the given one
		* @param p_key
		* @param p_excludeZero
		*/
		uint32_t GetPreviousKey(uint32_t p_key, bool p_excludeZero = false) const;

		/**
		* Return the number of bones of the skeleton binded to the animation
		*/
		uint32_t GetBonesCount() const;

	private:
		uint32_t m_bonesCount	= 0;
		uint32_t m_keyCount		= 0;
		uint32_t m_startKey		= 0;
		uint32_t m_endKey		= 0;
		std::vector<std::vector<Data::Transformation>> m_animationTransformations;
	};
}

#endif // _ANIMATIONINFO_H