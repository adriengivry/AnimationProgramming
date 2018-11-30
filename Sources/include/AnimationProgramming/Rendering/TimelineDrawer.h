/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#pragma once
#ifndef _TIMELINEDRAWER_H
#define _TIMELINEDRAWER_H

#include "AnimationProgramming/Rendering/IDrawer.h"
#include "AnimationProgramming/Animation/Timeline.h"
#include "AnimationProgramming/Data/Color.h"

namespace AnimationProgramming::Rendering
{
	/**
	* TimelineDrawer is a class able to render timeline info in world space
	*/
	class TimelineDrawer final : public IDrawer<Animation::Timeline>
	{
	public:
		/**
		* Constructor of the timeline drawer
		* @param p_frameSpacing
		* @param p_frameIndicatorLength
		* @param p_currentFrameIndicatorThickness
		* @param p_orientation
		*/
		TimelineDrawer(float p_frameSpacing, float p_frameIndicatorLength, uint8_t p_currentFrameIndicatorThickness, const AltMath::Vector3f& p_orientation);

		/**
		* Draw the given timeline in world space at the given location
		* @param p_timeline
		* @param p_worldPosition
		*/
		void Draw(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition);

	private:
		void DrawKeyFrames(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition);
		void DrawFrameCounter(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition);
		void DrawPlayIndicator(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition);
		void DrawPauseIndicator(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition);
		void DrawTransitionIndicator(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition);

	private:
		float m_frameSpacing;
		float m_frameIndicatorLength;
		uint8_t m_currentFrameIndicatorThickness;
		AltMath::Vector3f m_orientation;

		/* Indicators settings */
		AnimationProgramming::Data::Color m_indicatorDisabledColor;

		/* Digits settings */
		float m_digitSpacing;
		float m_digitWidth;
		float m_digitHeight;
	};
}

#endif // _TIMELINEDRAWER_H