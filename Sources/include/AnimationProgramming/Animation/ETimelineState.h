/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ETIMELINESTATE_H
#define _ETIMELINESTATE_H

namespace AnimationProgramming::Animation
{
	/**
	* This enumeration contains differents states that timeline can go through
	*/
	enum class ETimelineState
	{
		PAUSE,
		PLAYING,
		TRANSITIONING
	};
}

#endif // _ETIMELINESTATE_H
