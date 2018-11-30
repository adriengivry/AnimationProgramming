/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Animation/Timeline.h"
#include "AnimationProgramming/Tools/IniManager.h"
#include "AnimationProgramming/Rendering/Renderer.h"

AnimationProgramming::Animation::Timeline::Timeline()
{
	InitializeEffectors();
}

void AnimationProgramming::Animation::Timeline::InitializeEffectors()
{
	m_effectors[ETimelineEffector::REWIND] = Tools::IniManager::Timeline->Get<bool>("rewind_effector");
	m_effectors[ETimelineEffector::IGNORE_LOOPING] = Tools::IniManager::Timeline->Get<bool>("ignore_transitioning_effector");
	m_effectors[ETimelineEffector::IGNORE_TRANSITIONING] = Tools::IniManager::Timeline->Get<bool>("ignore_looping_effector");
	m_effectors[ETimelineEffector::IGNORE_FRAME_INTERPOLATION] = Tools::IniManager::Timeline->Get<bool>("ignore_frame_interpolation_effector");
}

bool AnimationProgramming::Animation::Timeline::IsPlaying() const
{
	return m_currentState == ETimelineState::PLAYING;
}

bool AnimationProgramming::Animation::Timeline::IsTransitioning() const
{
	return m_currentState == ETimelineState::TRANSITIONING;
}

bool AnimationProgramming::Animation::Timeline::IsPaused() const
{
	return m_currentState == ETimelineState::PAUSE;
}

bool AnimationProgramming::Animation::Timeline::IsReversed() const
{
	return m_effectors.at(ETimelineEffector::REWIND) ? !m_reverse : m_reverse;
}

bool AnimationProgramming::Animation::Timeline::IsLooping() const
{
	return m_loop && !m_effectors.at(ETimelineEffector::IGNORE_LOOPING);
}

bool AnimationProgramming::Animation::Timeline::IsLastKeyFrame(bool p_ignorePlayingDirection) const
{
	return m_currentKeyFrame == GetLastKeyFrame(p_ignorePlayingDirection);
}

bool AnimationProgramming::Animation::Timeline::IsFirstKeyFrame(bool p_ignorePlayingDirection) const
{
	return m_currentKeyFrame == GetFirstKeyFrame(p_ignorePlayingDirection);
}

void AnimationProgramming::Animation::Timeline::SetEffector(ETimelineEffector p_effector, bool p_state)
{
	m_effectors[p_effector] = p_state;
}

bool AnimationProgramming::Animation::Timeline::GetEffector(ETimelineEffector p_effector) const
{
	return m_effectors.at(p_effector);
}

void AnimationProgramming::Animation::Timeline::ToggleEffector(ETimelineEffector p_effector)
{
	SetEffector(p_effector, !m_effectors[p_effector]);
}

uint32_t AnimationProgramming::Animation::Timeline::GetCurrentKeyFrame() const
{
	return m_currentKeyFrame;
}

uint32_t AnimationProgramming::Animation::Timeline::GetNextKeyFrame(bool p_ignorePlayingDirection) const
{
	if (!p_ignorePlayingDirection && IsReversed())
		return GetPreviousKeyFrame(true);

	return m_currentKeyFrame == m_endKeyFrame ? m_startKeyFrame : m_currentKeyFrame + 1;
}

uint32_t AnimationProgramming::Animation::Timeline::GetPreviousKeyFrame(bool p_ignorePlayingDirection) const
{
	if (!p_ignorePlayingDirection && IsReversed())
		return GetNextKeyFrame(true);

	return m_currentKeyFrame == m_startKeyFrame ? m_endKeyFrame : m_currentKeyFrame - 1;
}

uint32_t AnimationProgramming::Animation::Timeline::GetFirstKeyFrame(bool p_ignorePlayingDirection) const
{
	if (p_ignorePlayingDirection || !IsReversed())
		return m_startKeyFrame;
	else
		return m_endKeyFrame;
}

uint32_t AnimationProgramming::Animation::Timeline::GetLastKeyFrame(bool p_ignorePlayingDirection) const
{
	if (p_ignorePlayingDirection || !IsReversed())
		return m_endKeyFrame;
	else
		return m_startKeyFrame;
}

void AnimationProgramming::Animation::Timeline::GoToNextKeyFrame(bool p_ignorePlayingDirection)
{
	m_currentKeyFrame = GetNextKeyFrame(p_ignorePlayingDirection);
	FrameChangedEvent.Invoke();
}

void AnimationProgramming::Animation::Timeline::GoToPreviousKeyFrame(bool p_ignorePlayingDirection)
{
	m_currentKeyFrame = GetPreviousKeyFrame(p_ignorePlayingDirection);
	FrameChangedEvent.Invoke();
}

void AnimationProgramming::Animation::Timeline::SyncToAnimation(const Animation::AnimationInstance& p_animationInfo)
{
	m_startKeyFrame = p_animationInfo.attachedAnimation.GetStartKey();
	m_endKeyFrame = p_animationInfo.attachedAnimation.GetEndKey();
	m_frameDuration = p_animationInfo.frameDuration;
	m_loop = p_animationInfo.loop;
	m_reverse = p_animationInfo.reverse;
}

void AnimationProgramming::Animation::Timeline::Reset()
{
	m_currentKeyFrame = m_startKeyFrame;
	m_frameTimer = 0.0f;
	m_transitionTimer = 0.0f;
}

void AnimationProgramming::Animation::Timeline::Play()
{
	m_currentState = ETimelineState::PLAYING;
}

void AnimationProgramming::Animation::Timeline::PlayTransition(float p_duration)
{
	if (!m_effectors[ETimelineEffector::IGNORE_TRANSITIONING])
	{
		m_currentKeyFrame = GetFirstKeyFrame();
		m_transitionTimer = 0.0f;
		m_transitionDuration = p_duration;
		m_currentState = ETimelineState::TRANSITIONING;
	}
}

void AnimationProgramming::Animation::Timeline::Pause()
{
	m_pausePreviousState = m_currentState == ETimelineState::PAUSE ? m_pausePreviousState : m_currentState;
	m_currentState = ETimelineState::PAUSE;
}

void AnimationProgramming::Animation::Timeline::Resume()
{
	m_currentState = m_pausePreviousState;
	m_pausePreviousState = ETimelineState::PAUSE;
}

void AnimationProgramming::Animation::Timeline::TogglePause()
{
	if (m_currentState == ETimelineState::PAUSE)
		Resume();
	else
		Pause();
}

float AnimationProgramming::Animation::Timeline::CalculateInterpolationAlpha() const
{
	if (m_effectors.at(ETimelineEffector::IGNORE_FRAME_INTERPOLATION))
		return 0.0f;

	switch (m_currentState)
	{
	case ETimelineState::PLAYING: return m_frameTimer / m_frameDuration;
	case ETimelineState::TRANSITIONING: return m_transitionTimer / m_transitionDuration;
	}

	return 0.0f;
}

void AnimationProgramming::Animation::Timeline::Update(float p_deltaTime)
{
	switch (m_currentState)
	{
	case ETimelineState::PLAYING:
		UpdatePlayingState(p_deltaTime);
		break;

	case ETimelineState::TRANSITIONING:
		UpdateTransitioningState(p_deltaTime);
		break;
	}
}

void AnimationProgramming::Animation::Timeline::UpdatePlayingState(float p_deltaTime)
{
	m_frameTimer += p_deltaTime;

	while (m_frameTimer >= m_frameDuration)
	{
		m_frameTimer -= m_frameDuration;

		GoToNextKeyFrame();

		/* If we arrived at last frame and the animation shouldn't loop, we pause */
		if (IsLastKeyFrame() && (!m_loop || m_effectors[ETimelineEffector::IGNORE_LOOPING]))
			Pause();
	}
}

void AnimationProgramming::Animation::Timeline::UpdateTransitioningState(float p_deltaTime)
{
	m_transitionTimer += p_deltaTime;

	if (m_transitionTimer >= m_transitionDuration)
	{
		Play();
		FrameChangedEvent.Invoke();
	}
}