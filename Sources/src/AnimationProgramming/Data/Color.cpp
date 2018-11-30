/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Data/Color.h"

const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Red		= Color{ 255, 0, 0 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Green	= Color{ 0, 255, 0 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Blue		= Color{ 0, 0, 255 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::White	= Color{ 255, 255, 255 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Black	= Color{ 0, 0, 0 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Yellow	= Color{ 255, 255, 0 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Cyan		= Color{ 0, 255, 255 };
const AnimationProgramming::Data::Color AnimationProgramming::Data::Color::Magenta	= Color{ 255, 0, 255 };

AnimationProgramming::Data::Color::Color(uint8_t p_r, uint8_t p_g, uint8_t p_b) : r(p_r), g(p_g), b(p_b) {}

std::tuple<float, float, float> AnimationProgramming::Data::Color::GetNormalized() const
{
	return std::make_tuple(r / 255.f, g / 255.f, b / 255.f);
}
