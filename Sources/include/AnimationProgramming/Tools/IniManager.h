/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _INIMANAGER_H
#define _INIMANAGER_H

#include <memory>

#include <GyvrIni/GyvrIni.h>

#include "AnimationProgramming/Animation/AnimationInstance.h"

namespace AnimationProgramming::Tools
{
	/**
	* This struct regroup every ini files for static usage
	*/
	struct IniManager final
	{
		/* Prevent this static class from being instancied */
		IniManager() = delete;
		
		/**
		* Load every ini data into the memory. This must be called before trying to access any ini file
		*/
		static void Initialize();

		/**
		* Parse the given ini file and store data from this file into an animation instance
		* @param p_animationInstance
		* @param p_iniFilePath
		*/
		static void SetupAnimationInstanceFromIniFile(Animation::AnimationInstance& p_animationInstance, const std::string& p_iniFilePath);

		static std::unique_ptr<GyvrIni::Core::IniFile> Window;
		static std::unique_ptr<GyvrIni::Core::IniFile> Rendering;
		static std::unique_ptr<GyvrIni::Core::IniFile> Timeline;
		static std::unique_ptr<GyvrIni::Core::IniFile> Animation;
	};
}

#endif // _INIMANAGER_H