/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _RENDERER_H
#define _RENDERER_H

#include <AltMath/AltMath.h>

#include "AnimationProgramming/Rendering/EDrawMode.h"
#include "AnimationProgramming/Rendering/EShapeMode.h"
#include "AnimationProgramming/Data/Color.h"

namespace AnimationProgramming::Rendering
{
	/**
	* A simple static class that simplify the rendering of some things, such as lines and basic shapes
	*/
	class Renderer final
	{
	public:
		/**
		* Deleted constructor to prevent instancing this static class
		*/
		Renderer() = delete;

		/**
		* Enable or disable the alpha mode
		* @param p_enable
		*/
		static void EnableAlphaMode(bool p_enable);

		/**
		* Set a draw mode
		* @param p_drawMode
		*/
		static void SetDrawMode(EDrawMode p_drawMode);

		/**
		* Return the current draw mode
		*/
		static EDrawMode GetDrawMode();

		/**
		* Define a custom line thickness
		* @param p_thickness
		*/
		static void SetLineThickness(float p_thickness);

		/**
		* Render a gizmo on the screen
		* @param p_xColor
		* @param p_yColor
		* @param p_zColor
		* @param p_size
		*/
		static void DrawGizmo(const AnimationProgramming::Data::Color& p_xColor, const AnimationProgramming::Data::Color& p_yColor, const AnimationProgramming::Data::Color& p_zColor, float p_size, const AltMath::Vector3f& p_position = AltMath::Vector3f::Zero);

		/**
		* Draw a line in the 3D space
		* @param p_start
		* @param p_end
		* @param p_color
		*/
		static void DrawLine(const AltMath::Vector3f& p_start, const AltMath::Vector3f& p_end, const AnimationProgramming::Data::Color& p_color);

		/**
		* Draw a 3D cross at the given position
		* @param p_position
		* @param p_color
		* @param p_size
		*/
		static void DrawCross(const AltMath::Vector3f& p_position, const AnimationProgramming::Data::Color& p_color, float p_size);

		/**
		* Draw a 3D star at the given position
		* @param p_position
		* @param p_color
		* @param p_size
		*/
		static void DrawStar(const AltMath::Vector3f& p_position, const AnimationProgramming::Data::Color& p_color, float p_size);

		/**
		* Draw a shape in 3D world
		* @param p_shapeMode
		* @param p_vertices
		* @param p_color
		*/
		static void DrawShape(EShapeMode p_shapeMode, std::vector<AltMath::Vector3f>& p_vertices, const AnimationProgramming::Data::Color& p_color);

		/**
		* Draw a number at the given position
		* @param p_number
		* @param p_position
		* @param p_color
		* @param p_digitSpacing
		* @param p_digitWidth
		* @param p_digitHeight
		*/
		static void DrawNumber(uint32_t p_number, const AltMath::Vector3f& p_position, const Data::Color& p_color = Data::Color::Black, float p_digitSpacing = 5.0f, float p_digitWidth = 10.0f, float p_digitHeight = 20.0f);

		/**
		* Draw a digit at the given position
		* @param p_digit
		* @param p_position
		* @param p_color
		* @param p_width
		* @param p_height
		*/
		static void DrawDigit(uint8_t p_digit, const AltMath::Vector3f& p_position, const Data::Color& p_color = Data::Color::Black, float p_width = 10.0f, float p_height = 20.0f);

		/**
		* Draw a grid on the floor
		*/
		static void DrawGrid();

	private:
		static EDrawMode m_currentDrawMode;
	};
}

#endif // _RENDERER_H