/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _BONE_H
#define _BONE_H

#include "AnimationProgramming/Rendering/Renderer.h"
#include "AnimationProgramming/Data/Transform.h"

namespace AnimationProgramming::Rig
{
	/**
	* Representation of a Bone (Part of a rig)
	*/
	class Bone final
	{
	public:
		/**
		* Constructor of the Bone class. The bone will be set as the root
		* @param p_name
		* @param p_index
		* @param p_localPosition
		* @param p_localRotation
		*/
		Bone(const std::string& p_name, uint32_t p_index, AltMath::Vector3f p_localPosition, AltMath::Quaternion p_localRotation);

		/**
		* Defines a parent to the bone
		* @param p_parent
		*/
		void SetParent(Bone& p_parent);

		/**
		* Set a position relative to the default transform (T-Pose)
		* @param p_localPosition
		*/
		void SetRelativePosition(AltMath::Vector3f p_localPosition);

		/**
		* Set a rotation relative to the default transform (T-Pose)
		* @param p_localRotation
		*/
		void SetRelativeRotation(AltMath::Quaternion p_localRotation);

		/**
		* Set a position and a rotation relative to the default transform (T-Pose)
		* @param p_localPosition
		* @param p_localRotation
		*/
		void SetRelativePositionAndRotation(AltMath::Vector3f p_localPosition, AltMath::Quaternion p_localRotation);

		/**
		* Reset the position and rotation of the bone to the default transform (T-Pose)
		*/
		void ResetPositionAndRotation();

		/**
		* Check if the bone is the root (Same as not having a parent)
		*/
		bool IsRoot() const;

		/**
		* Check if a bone is an IK
		*/
		bool IsIK() const;

		/**
		* Check if the bone has a parent
		*/
		bool HasParent() const;

		/**
		* Return the parent of the bone (HasParent() must be called before)
		*/
		Bone& GetParent();

		/**
		* Return the index of the bone
		*/
		uint32_t GetIndex();

		/**
		* Return a reference to the transform of the bone
		*/
		AnimationProgramming::Data::Transform& GetTransform();

		/**
		* Return a reference to the default transform of the bone
		*/
		AnimationProgramming::Data::Transform& GetDefaultTransform();

	private:
		/* Bone identity */
		std::string m_name;
		uint32_t m_index;
		Bone* m_parent;

		/* Current transform */
		AnimationProgramming::Data::Transform m_transform;

		/* Transform of the bind pose (T-Pose) */
		AnimationProgramming::Data::Transform m_defaultTransform;
	};
}

#endif // _BONE_H
