/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include <Engine/Engine.h>

#include <GL/glew.h>

#include "AnimationProgramming/Rendering/Renderer.h"

AnimationProgramming::Rendering::EDrawMode AnimationProgramming::Rendering::Renderer::m_currentDrawMode;

void AnimationProgramming::Rendering::Renderer::EnableAlphaMode(bool p_enable)
{
	if (p_enable)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void AnimationProgramming::Rendering::Renderer::SetDrawMode(EDrawMode p_drawMode)
{
	m_currentDrawMode = p_drawMode;

	switch (p_drawMode)
	{
	case EDrawMode::NORMAL:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case EDrawMode::WIREFRAME:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	}
}

AnimationProgramming::Rendering::EDrawMode AnimationProgramming::Rendering::Renderer::GetDrawMode()
{
	return m_currentDrawMode;
}

void AnimationProgramming::Rendering::Renderer::SetLineThickness(float p_thickness)
{
	glLineWidth(static_cast<GLfloat>(p_thickness));
}

void AnimationProgramming::Rendering::Renderer::DrawGizmo(const AnimationProgramming::Data::Color & p_xColor, const AnimationProgramming::Data::Color & p_yColor, const AnimationProgramming::Data::Color & p_zColor, float p_size, const AltMath::Vector3f& p_position)
{
	auto[xr, xg, xb] = p_xColor.GetNormalized();
	auto[yr, yg, yb] = p_yColor.GetNormalized();
	auto[zr, zg, zb] = p_zColor.GetNormalized();

	::DrawLine(p_position.x, p_position.y, p_position.z, p_size, 0.0f, 0.0f, xr, xg, xb);
	::DrawLine(p_position.x, p_position.y, p_position.z, 0.0f, p_size, 0.0f, yr, yg, yb);
	::DrawLine(p_position.x, p_position.y, p_position.z, 0.0f, 0.0f, p_size, zr, zg, zb);
}

void AnimationProgramming::Rendering::Renderer::DrawLine(const AltMath::Vector3f& p_start, const AltMath::Vector3f& p_end, const AnimationProgramming::Data::Color& p_color)
{
	auto[r, g, b] = p_color.GetNormalized();

	::DrawLine(p_start.x, p_start.y, p_start.z, p_end.x, p_end.y, p_end.z, r, g, b);
}

void AnimationProgramming::Rendering::Renderer::DrawCross(const AltMath::Vector3f& p_position, const AnimationProgramming::Data::Color& p_color, float p_size)
{
	float halfSize = p_size / 2.0f;
	auto[r, g, b] = p_color.GetNormalized();

	::DrawLine(p_position.x - halfSize, p_position.y, p_position.z, p_position.x + halfSize, p_position.y, p_position.z, r, g, b);
	::DrawLine(p_position.x, p_position.y - halfSize, p_position.z, p_position.x, p_position.y + halfSize, p_position.z, r, g, b);
	::DrawLine(p_position.x, p_position.y, p_position.z - halfSize, p_position.x, p_position.y, p_position.z + halfSize, r, g, b);
}

void AnimationProgramming::Rendering::Renderer::DrawStar(const AltMath::Vector3f & p_position, const AnimationProgramming::Data::Color & p_color, float p_size)
{
	float halfSize = p_size / 2.0f;
	auto[r, g, b] = p_color.GetNormalized();

	::DrawLine(p_position.x - halfSize, p_position.y, p_position.z, p_position.x + halfSize, p_position.y, p_position.z, r, g, b);
	::DrawLine(p_position.x, p_position.y - halfSize, p_position.z, p_position.x, p_position.y + halfSize, p_position.z, r, g, b);
	::DrawLine(p_position.x, p_position.y, p_position.z - halfSize, p_position.x, p_position.y, p_position.z + halfSize, r, g, b);

	halfSize = p_size * 0.707f / 2.0f;
	::DrawLine(p_position.x - halfSize, p_position.y - halfSize, p_position.z - halfSize, p_position.x + halfSize, p_position.y + halfSize, p_position.z + halfSize, r, g, b);
	::DrawLine(p_position.x - halfSize, p_position.y + halfSize, p_position.z - halfSize, p_position.x + halfSize, p_position.y - halfSize, p_position.z + halfSize, r, g, b);
	::DrawLine(p_position.x + halfSize, p_position.y - halfSize, p_position.z - halfSize, p_position.x - halfSize, p_position.y + halfSize, p_position.z + halfSize, r, g, b);
	::DrawLine(p_position.x + halfSize, p_position.y + halfSize, p_position.z - halfSize, p_position.x - halfSize, p_position.y - halfSize, p_position.z + halfSize, r, g, b);
}

void AnimationProgramming::Rendering::Renderer::DrawShape(EShapeMode p_shapeMode, std::vector<AltMath::Vector3f>& p_vertices, const AnimationProgramming::Data::Color& p_color)
{
	uint32_t shapeComplexity = p_shapeMode != EShapeMode::POLYGON ? static_cast<uint32_t>(p_shapeMode) + 1 : p_vertices.size();
	
	for (uint32_t i = 0; i + shapeComplexity <= p_vertices.size(); i += shapeComplexity)
		for (uint32_t j = 0; j < shapeComplexity; ++j)
			DrawLine(p_vertices[i + j], p_vertices[(j + 1 == shapeComplexity) ? i : i + j + 1], p_color);
}

void AnimationProgramming::Rendering::Renderer::DrawNumber(uint32_t p_number, const AltMath::Vector3f& p_position, const Data::Color& p_color, float p_digitSpacing, float p_digitWidth, float p_digitHeight)
{
	std::vector<uint8_t> digits;

	/* Extract digits from the given number */
	while (p_number != 0 || digits.size() == 0)
	{
		digits.push_back(p_number % 10);
		p_number = p_number / 10;
	}

	/* Reverse the order to put them in the right order */
	std::reverse(digits.begin(), digits.end());

	for (uint8_t i = 0; i < digits.size(); ++i)
	{
		AltMath::Vector3f digitOffset = AltMath::Vector3f(i * (p_digitWidth + p_digitSpacing), 0.0f, 0.0f);
		AltMath::Vector3f numberOffset = AltMath::Vector3f((p_digitWidth + p_digitSpacing) * digits.size() * -0.5f, 0.0f, 0.0f);

		DrawDigit(digits[i], p_position + numberOffset + digitOffset, p_color, p_digitWidth, p_digitHeight);
	}
}

void AnimationProgramming::Rendering::Renderer::DrawDigit(uint8_t p_digit, const AltMath::Vector3f& p_position, const Data::Color& p_color, float p_width, float p_height)
{
	p_digit = p_digit % 10;

	std::vector<uint8_t> topNumbers{ 2, 3, 5, 6, 7, 8, 9, 0 };
	std::vector<uint8_t> bottomNumbers{ 2, 3, 5, 6, 8, 9, 0 };
	std::vector<uint8_t> topLeftNumbers{ 4, 5, 6, 8, 9, 0 };
	std::vector<uint8_t> topRightNumbers{ 1, 2, 3, 4, 7, 8, 9, 0 };
	std::vector<uint8_t> bottomLeftNumbers{ 2, 6, 8, 0 };
	std::vector<uint8_t> bottomRightNumbers{ 1, 3, 4, 5, 6, 7, 8, 9, 0 };
	std::vector<uint8_t> middleNumbers{ 2, 3, 4, 5, 6, 8, 9 };

	if (std::find(topNumbers.begin(), topNumbers.end(), p_digit) != topNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(0.0f, 0.0f, 1.0f) * p_height / 2.0f + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(0.0f, 0.0f, 1.0f) * p_height / 2.0f + AltMath::Vector3f(+1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_color);

	if (std::find(bottomNumbers.begin(), bottomNumbers.end(), p_digit) != bottomNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(0.0f, 0.0f, -1.0f) * p_height / 2.0f + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(0.0f, 0.0f, -1.0f) * p_height / 2.0f + AltMath::Vector3f(+1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_color);

	if (std::find(topLeftNumbers.begin(), topLeftNumbers.end(), p_digit) != topLeftNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f + AltMath::Vector3f(0.0f, 0.0f, 1.0f) * p_height / 2.0f, p_color);

	if (std::find(topRightNumbers.begin(), topRightNumbers.end(), p_digit) != topRightNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(1.0f, 0.0f, 0.0f) * p_width / 2.0f + AltMath::Vector3f(0.0f, 0.0f, 1.0f) * p_height / 2.0f, p_color);

	if (std::find(bottomLeftNumbers.begin(), bottomLeftNumbers.end(), p_digit) != bottomLeftNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f + AltMath::Vector3f(0.0f, 0.0f, -1.0f) * p_height / 2.0f, p_color);

	if (std::find(bottomRightNumbers.begin(), bottomRightNumbers.end(), p_digit) != bottomRightNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(1.0f, 0.0f, 0.0f) * p_width / 2.0f + AltMath::Vector3f(0.0f, 0.0f, -1.0f) * p_height / 2.0f, p_color);

	if (std::find(middleNumbers.begin(), middleNumbers.end(), p_digit) != middleNumbers.end())
		DrawLine(p_position + AltMath::Vector3f(-1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_position + AltMath::Vector3f(+1.0f, 0.0f, 0.0f) * p_width / 2.0f, p_color);
}

void AnimationProgramming::Rendering::Renderer::DrawGrid()
{
	float spacing = 50.0f;
	float halfSpacing = spacing * 0.5f;

	Data::Color gridColor(200, 200, 200);

	for (int32_t i = -20; i < 20; ++i)
	{
		float currentSpacing = i * spacing + halfSpacing;
		DrawLine(AltMath::Vector3f(currentSpacing, -1000.0f, 0.0f), AltMath::Vector3f(currentSpacing, 1000.0f, 0.0f), gridColor);
		DrawLine(AltMath::Vector3f(-1000.0f, currentSpacing, 0.0f), AltMath::Vector3f(1000.0f, currentSpacing, 0.0f), gridColor);
	}
}
