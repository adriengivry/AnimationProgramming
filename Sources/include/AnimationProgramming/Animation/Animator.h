/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ANIMATOR_H
#define _ANIMATOR_H

#include <string>

#include "AnimationProgramming/Animation/Timeline.h"
#include "AnimationProgramming/Animation/AnimationInstance.h"
#include "AnimationProgramming/Rig/Skeleton.h"

namespace AnimationProgramming::Animation
{
	/**
	* The animator is used to update and apply an animation to a skeleton (CPU and GPU for hardware skinning)
	*/
	class Animator final
	{
	public:
		/**
		* Create the animator reponsible of the animation of the given skeleton
		* @param p_skeleton
		*/
		Animator(Rig::Skeleton& p_skeleton);

		/**
		* Return true if there is a binded animation
		*/
		bool HasAnimation() const;

		/**
		* Return the timeline used by this Animator
		*/
		Timeline& GetTimeline();

		/**
		* Return the global speed coefficient
		*/
		float GetGlobalSpeedCoefficient();

		/**
		* Set a global speed multiplier for the animator
		* @param p_coefficient
		*/
		void SetGlobalSpeedCoefficient(float p_coefficient);

		/**
		* Play the given animation from the key 0 to the last key
		* @param p_toPlay
		*/
		void PlayAnimation(Animation::AnimationInstance& p_toPlay);

		/**
		* Stop the current animation and return in T-Pose
		*/
		void StopAnimation();

		/**
		* If there is an animation, the timeline is updated and the animation is applied to the skeleton
		* and the actual pose is send to GPU
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Update the new start and end transformations for each bones to the current and next frame (Needed for interpolation)
		*/
		void UpdateFrameTransformations();

		/**
		* Set the current skeleton transformations as the transition start point, and set the first frame
		* of the new animation to transit to as the transition end point.
		* @param p_previousAlpha (Used to get the previous transformation interpolation result)
		*/
		void CalculateTransitionStartAndEndPoint(float p_previousAlpha);

		/**
		* Return a transformation that is the result of the interpolation between the start and end frame
		* @param p_boneIndex
		* @param p_alpha
		*/
		Data::Transformation CalculateInterpolation(uint32_t p_boneIndex, float p_alpha);

		/**
		* Apply the current animation frame to the skeleton (Interpolate frames on animation demand)
		*/
		void ApplyAnimationToSkeleton();

		/**
		* Apply the bind pose (Or T-Pose) to the skeleton
		*/
		void ApplyBindPoseToSkeleton();

		/**
		* Send every matrices needed for hardware skinning to the GPU
		*/
		void SendSkinningMatricesToGPU();

	private:
		/* Timeline relatives */
		Timeline m_timeline;

		/* Linked things */
		Rig::Skeleton&					m_skeleton;
		Animation::AnimationInstance*	m_currentAnimation = nullptr;

		/* Current and next key frame transformations (One transformation per bone per frame) */
		std::vector<Data::Transformation> m_currentKeyFrameTransformations;
		std::vector<Data::Transformation> m_nextKeyFrameTransformations;

		/* Other settings */
		float m_globalSpeedCoefficient = 1.0f;
	};
}

#endif // _ANIMATOR_H
