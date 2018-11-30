/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Core/AnimationEngine.h"
#include "AnimationProgramming/Simulations/CSimulation.h"
#include "AnimationProgramming/Tools/IniManager.h"

using namespace AnimationProgramming;
using namespace AnimationProgramming::Core;
using namespace AnimationProgramming::Tools;
using namespace AnimationProgramming::Simulations;

int main()
{ 
	IniManager::Initialize();

	CSimulation simulation;

	uint16_t windowWidth = IniManager::Window->Get<uint16_t>("width");
	uint16_t windowHeight = IniManager::Window->Get<uint16_t>("height");

	AnimationEngine::Run(simulation, windowWidth, windowHeight);

	return EXIT_SUCCESS;
}