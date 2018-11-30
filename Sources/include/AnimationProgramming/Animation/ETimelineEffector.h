/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ETIMELINEEFFECTOR_H
#define _ETIMELINEEFFECTOR_H

namespace AnimationProgramming::Animation
{
	/**
	* Timeline effectors are used to apply non-constant modifications on the timeline
	*/
	enum class ETimelineEffector
	{
		REWIND,
		IGNORE_LOOPING,
		IGNORE_TRANSITIONING,
		IGNORE_FRAME_INTERPOLATION
	};
}

#endif // _ETIMELINEEFFECTOR_H
