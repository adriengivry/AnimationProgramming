/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _IDRAWER_H
#define _IDRAWER_H

#include <AltMath/AltMath.h>

namespace AnimationProgramming::Rendering
{
	/**
	* IDrawer is an interface that any Drawer should implement. A Drawer is basically a class that can parse a given class and render it in world space
	*/
	template<typename T>
	class IDrawer
	{
		/**
		* Draw the given object in world space
		* @param p_toDraw
		* @param p_worldPosition
		*/
		virtual void Draw(const T& p_toDraw, const AltMath::Vector3f& p_worldPosition) = 0;
	};
}

#endif // _IDRAWER_H