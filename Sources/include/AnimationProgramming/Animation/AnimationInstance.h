/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ANIMATIONINSTANCE_H
#define _ANIMATIONINSTANCE_H

#include "AnimationProgramming/Animation/AnimationInfo.h"

namespace AnimationProgramming::Animation
{
	/**
	* The animation instance struct represents an animation with a set of settings. It is used by the animator
	*/
	struct AnimationInstance final
	{
		/**
		* Create the animation instance
		* @param p_animationInfo
		*/
		AnimationInstance(const Animation::AnimationInfo& p_animationInfo);

		/* The attached animation (AnimationInfo). Cannot be changed after creation */
		const Animation::AnimationInfo& attachedAnimation;

		/* Tweakable settings */
		float frameDuration			= 0.03333f;
		float speedCoefficient		= 1.0f;
		float transitionDuration	= 0.1f;
		bool loop					= false;
		bool reverse				= false;
		bool interpolateKeyFrames	= true;
	};
}

#endif // _ANIMATIONINSTANCE_H
