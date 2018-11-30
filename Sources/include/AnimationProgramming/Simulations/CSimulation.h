/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _CSIMULATION_H
#define _CSIMULATION_H

#include <Engine/Simulation.h>

#include "AnimationProgramming/Input/InputManager.h"
#include "AnimationProgramming/Rendering/Renderer.h"
#include "AnimationProgramming/Rig/Skeleton.h"
#include "AnimationProgramming/Animation/Animator.h"
#include "AnimationProgramming/Rendering/TimelineDrawer.h"
#include "AnimationProgramming/Rendering/SkeletonDrawer.h"

namespace AnimationProgramming::Simulations
{
	/**
	* The CSimulation class is the main simulation that is used in this project
	*/
	class CSimulation final : public ISimulation
	{
	public:
		/**
		* Constructor of the CSimulation class
		*/
		CSimulation();

	private:

		/**
		* Init the Simulation
		*/
		virtual void Init() override;

		/**
		* Load animations information
		*/
		void LoadAnimationsInfo();

		/**
		* Create custom animations
		*/
		void CreateCustomAnimations();

		/**
		* Create animation instances
		*/
		void CreateAnimationInstances();

		/**
		* Create the skeleton
		*/
		void CreateSkeleton();

		/**
		* Play the default animation
		*/
		void PlayDefaultAnimation();

		/**
		* Display inputs to the console
		*/
		void DisplayInputs();

		/**
		* Update the simulation
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Check inputs and apply logic depending on which key is pressed
		* @param p_deltaTime
		*/
		void CheckInputs(float p_deltaTime);

		/**
		* Update every animators
		*/
		void UpdateAnimators(float p_deltaTime);

		/**
		* Draw the scene
		*/
		void DrawScene();

		/**
		* Toggle the wireframe draw mode
		*/
		void ToggleWireframe();

		/**
		* Display the framerate (Calculated with the given deltaTime) to the console
		* @param p_deltaTime
		*/
		void PrintFramerate(float p_deltaTime);

		/**
		* Display a tip in the console to help user finding inputs
		*/
		void PrintHelpTip();

	private:
		/* Inputs */
		Input::InputManager m_inputManager;

		/* Rig stuffs */
		Rig::Skeleton m_skeleton;
		Animation::Animator m_animator;

		/* Drawers */
		Rendering::TimelineDrawer m_timelineDrawer;
		Rendering::SkeletonDrawer m_skeletonDrawer;

		/* Animations Data */
		std::unique_ptr<Animation::AnimationInfo> m_walkAnimation;
		std::unique_ptr<Animation::AnimationInfo> m_runAnimation;
		std::unique_ptr<Animation::AnimationInfo> m_dabAnimation;
		std::unique_ptr<Animation::AnimationInfo> m_squatAnimation;

		std::unique_ptr<Animation::AnimationInstance> m_walkAnimationInstance;
		std::unique_ptr<Animation::AnimationInstance> m_runAnimationInstance;
		std::unique_ptr<Animation::AnimationInstance> m_dabAnimationInstance;
		std::unique_ptr<Animation::AnimationInstance> m_squatAnimationInstance;
	};
}

#endif // _CSIMULATION_H

