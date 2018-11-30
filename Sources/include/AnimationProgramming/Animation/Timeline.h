/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TIMELINE_H
#define _TIMELINE_H

#include "AnimationProgramming/Tools/Event.h"
#include "AnimationProgramming/Animation/AnimationInstance.h"
#include "AnimationProgramming/Animation/ETimelineState.h"
#include "AnimationProgramming/Animation/ETimelineEffector.h"

namespace AnimationProgramming::Animation
{
	/**
	* The timeline class is reponsible for the frame logic. It will invoke an event after every frame change
	*/
	class Timeline final
	{
	public:
		/**
		* Constructor of the timeline
		*/
		Timeline();

		/**
		* Initialize every effectors to their default value
		*/
		void InitializeEffectors();

		/**
		* Return if the timeline is in playing mode
		*/
		bool IsPlaying() const;

		/**
		* Return if the timeline is in transitioning mode
		*/
		bool IsTransitioning() const;

		/**
		* Return if the timeline is in pause mode
		*/
		bool IsPaused() const;

		/**
		* Return if the timeline playing way is reverse or not
		*/
		bool IsReversed() const;

		/**
		* Return if the timeline is set to loop mode
		*/
		bool IsLooping() const;

		/**
		* Return if the current key frame is the last of the timeline
		* @param p_ignorePlayingDirection
		*/
		bool IsLastKeyFrame(bool p_ignorePlayingDirection = false) const;

		/**
		* Return if the current key frame is the first of the timeline
		* @param p_ignorePlayingDirection
		*/
		bool IsFirstKeyFrame(bool p_ignorePlayingDirection = false) const;

		/**
		* Set an effector state
		* @param p_effector
		* @param p_state
		*/
		void SetEffector(ETimelineEffector p_effector, bool p_state);

		/**
		* Get an effector state
		* @param p_effector
		*/
		bool GetEffector(ETimelineEffector p_effector) const;

		/**
		* Toggle an effector
		* @param p_effector
		*/
		void ToggleEffector(ETimelineEffector p_effector);

		/**
		* Return the current key frame
		*/
		uint32_t GetCurrentKeyFrame() const;

		/**
		* Return the next key frame to the current one
		* @param p_ignorePlayingDirection
		*/
		uint32_t GetNextKeyFrame(bool p_ignorePlayingDirection = false) const;

		/**
		* Return the previous key frame to the current one
		* @param p_ignorePlayingDirection
		*/
		uint32_t GetPreviousKeyFrame(bool p_ignorePlayingDirection = false) const;

		/**
		* Return the first key frame of the timeline
		* @param p_ignorePlayingDirection
		*/
		uint32_t GetFirstKeyFrame(bool p_ignorePlayingDirection = false) const;

		/**
		* Return the last frame of the timeline
		* @param p_ignorePlayingDirection
		*/
		uint32_t GetLastKeyFrame(bool p_ignorePlayingDirection = false) const;

		/**
		* Go the the next frame (The one following the current key frame)
		* @param p_ignorePlayingDirection
		*/
		void GoToNextKeyFrame(bool p_ignorePlayingDirection = false);

		/**
		* Go the the previous frame (The one preceding the current key frame)
		* @param p_ignorePlayingDirection
		*/
		void GoToPreviousKeyFrame(bool p_ignorePlayingDirection = false);

		/**
		* Synchronise the timeline to a given animation (Start key, end key, duration, looping, reverse...)
		*/
		void SyncToAnimation(const Animation::AnimationInstance& p_animationInfo);

		/**
		* Reset the timeline
		*/
		void Reset();

		/**
		* Set the current state to the timeline to play mode
		*/
		void Play();

		/**
		* Run the transition logic for the given duration
		* @param p_duration
		*/
		void PlayTransition(float p_duration);

		/**
		* Pause the timeline
		*/
		void Pause();

		/**
		* Resume the timeline
		*/
		void Resume();

		/**
		* Toggle the pause state
		*/
		void TogglePause();

		/**
		* Return the current interpolation alpha, depends on the current state (Playing or Transitioning)
		*/
		float CalculateInterpolationAlpha() const;

		/**
		* Simply updates the timeline
		*/
		void Update(float p_deltaTime);

		/**
		* Update the timeline playing state
		* @param p_deltaTime
		*/
		void UpdatePlayingState(float p_deltaTime);

		/**
		* Update the timeline transitioning state
		* @param p_deltaTime
		*/
		void UpdateTransitioningState(float p_deltaTime);

	public:
		/**
		* This event is invoked when the current key frame index is changed
		*/
		AnimationProgramming::Tools::Event<> FrameChangedEvent;

	private:
		/* Key frame informations (Synced with the currently playing animation) */
		uint32_t m_currentKeyFrame;
		uint32_t m_startKeyFrame;
		uint32_t m_endKeyFrame;

		/* Frame-relatives */
		float m_frameTimer;
		float m_frameDuration;

		/* Transition-relatives */
		float m_transitionTimer;
		float m_transitionDuration;

		/* Current synced animation-relatives */
		bool m_loop;
		bool m_reverse;

		/* State management */
		ETimelineState m_pausePreviousState = ETimelineState::PAUSE;
		ETimelineState m_currentState = ETimelineState::PAUSE;

		/* Effectors-relatives */
		std::unordered_map<ETimelineEffector, bool> m_effectors;
	};
}

#endif // _TIMELINE_H