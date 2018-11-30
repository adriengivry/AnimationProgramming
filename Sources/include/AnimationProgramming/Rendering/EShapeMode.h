/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _ESHAPEMODE_H
#define _ESHAPEMODE_H

namespace AnimationProgramming::Rendering
{
	/**
	* The shape mode is used to draw different kind of shapes with the Renderer
	*/
	enum class EShapeMode
	{
		POINTS,
		LINES,
		TRIANGLES,
		QUADS,
		POLYGON
	};
}

#endif // _ESHAPEMODE_H