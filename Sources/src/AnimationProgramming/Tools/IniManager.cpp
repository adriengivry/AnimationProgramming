/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Tools/IniManager.h"

std::unique_ptr<GyvrIni::Core::IniFile> AnimationProgramming::Tools::IniManager::Window;
std::unique_ptr<GyvrIni::Core::IniFile> AnimationProgramming::Tools::IniManager::Rendering;
std::unique_ptr<GyvrIni::Core::IniFile> AnimationProgramming::Tools::IniManager::Timeline;
std::unique_ptr<GyvrIni::Core::IniFile> AnimationProgramming::Tools::IniManager::Animation;

void AnimationProgramming::Tools::IniManager::Initialize()
{
	Window		= std::make_unique<GyvrIni::Core::IniFile>("config/window.ini");
	Rendering	= std::make_unique<GyvrIni::Core::IniFile>("config/rendering.ini");
	Timeline	= std::make_unique<GyvrIni::Core::IniFile>("config/timeline.ini");
	Animation	= std::make_unique<GyvrIni::Core::IniFile>("config/animation.ini");
}

void AnimationProgramming::Tools::IniManager::SetupAnimationInstanceFromIniFile(Animation::AnimationInstance& p_animationInstance, const std::string& p_iniFilePath)
{
	GyvrIni::Core::IniFile iniFile(p_iniFilePath);

	p_animationInstance.frameDuration			= iniFile.Get<float>("frame_duration");
	p_animationInstance.speedCoefficient		= iniFile.Get<float>("speed_coefficient");
	p_animationInstance.transitionDuration		= iniFile.Get<float>("transition_duration");
	p_animationInstance.loop					= iniFile.Get<bool>("loop");
	p_animationInstance.reverse					= iniFile.Get<bool>("reverse");
	p_animationInstance.interpolateKeyFrames	= iniFile.Get<bool>("interpolate_key_frames");
}
