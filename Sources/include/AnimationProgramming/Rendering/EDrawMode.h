/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _EDRAWMODE_H
#define _EDRAWMODE_H

namespace AnimationProgramming::Rendering
{
	/**
	* The draw mode is used to indicate to OpenGL how things should get renderer on the screen
	*/
	enum class EDrawMode
	{
		NORMAL,
		WIREFRAME
	};
}

#endif // _EDRAWMODE_H