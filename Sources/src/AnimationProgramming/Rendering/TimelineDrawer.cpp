/**
* Project AnimationProgramming
* @author Adrien Givry
* @version 1.0
*/

#include "AnimationProgramming/Rendering/TimelineDrawer.h"
#include "AnimationProgramming/Rendering/Renderer.h"

AnimationProgramming::Rendering::TimelineDrawer::TimelineDrawer(float p_frameSpacing, float p_frameIndicatorLength, uint8_t p_currentFrameIndicatorThickness, const AltMath::Vector3f & p_orientation) :
	m_frameSpacing(p_frameSpacing),
	m_frameIndicatorLength(p_frameIndicatorLength),
	m_currentFrameIndicatorThickness(p_currentFrameIndicatorThickness),
	m_orientation(p_orientation),
	m_indicatorDisabledColor(220, 220, 220),
	m_digitSpacing(1.5f),
	m_digitWidth(4.0f),
	m_digitHeight(7.5f)
{
}

void AnimationProgramming::Rendering::TimelineDrawer::Draw(const Animation::Timeline& p_timeline, const AltMath::Vector3f & p_worldPosition)
{
	/* Draw key frames */
	DrawKeyFrames(p_timeline, p_worldPosition);

	/* Draw current and last frame numbers */
	DrawFrameCounter(p_timeline, p_worldPosition + AltMath::Vector3f(0.0f, 0.0f, 20.0f));

	/* Draw timeline state indicators */
	AltMath::Vector3f indicatorsStartPoint(p_worldPosition + AltMath::Vector3f(0.0f, 0.0f, -10.0f));
	DrawPlayIndicator(p_timeline, indicatorsStartPoint + AltMath::Vector3f(-20.0f, 0.0f, 0.0f));
	DrawPauseIndicator(p_timeline, indicatorsStartPoint + AltMath::Vector3f(0.0f, 0.0f, 0.0f));
	DrawTransitionIndicator(p_timeline, indicatorsStartPoint + AltMath::Vector3f(20.0f, 0.0f, 0.0f));
}

void AnimationProgramming::Rendering::TimelineDrawer::DrawKeyFrames(const Animation::Timeline & p_timeline, const AltMath::Vector3f & p_worldPosition)
{
	AltMath::Vector3f startPoint(p_worldPosition);
	uint32_t framesCount = p_timeline.GetLastKeyFrame(true) + 1;

	startPoint.x -= ((framesCount - 1) * m_frameSpacing) * 0.5f;

	AltMath::Vector3f leftLoopIndicator(startPoint);
	leftLoopIndicator.x -= m_frameSpacing;

	AltMath::Vector3f rightLoopIndicator(startPoint);
	rightLoopIndicator.x += framesCount * m_frameSpacing;

	if (p_timeline.IsLooping())
	{
		if (p_timeline.IsReversed())
			Rendering::Renderer::DrawLine(leftLoopIndicator + m_orientation * (m_frameIndicatorLength * 0.2f), leftLoopIndicator + m_orientation * (m_frameIndicatorLength * 0.8f), p_timeline.IsPaused() ? Data::Color(150, 150, 150) : Data::Color(0, 150, 0));
		else
			Rendering::Renderer::DrawLine(rightLoopIndicator + m_orientation * (m_frameIndicatorLength * 0.2f), rightLoopIndicator + m_orientation * (m_frameIndicatorLength * 0.8f), p_timeline.IsPaused() ? Data::Color(150, 150, 150) : Data::Color(0, 150, 0));
	}

	for (uint32_t i = 0; i < framesCount; ++i)
	{
		AltMath::Vector3f linePosition = startPoint + AltMath::Vector3f(m_frameSpacing * i, 0.0f, 0.0f);

		Rendering::Renderer::DrawLine(linePosition, linePosition + m_orientation * m_frameIndicatorLength, p_timeline.IsPaused() ? Data::Color(150, 150, 150) : Data::Color::Black);

		if (p_timeline.GetCurrentKeyFrame() == i)
		{
			float alpha = p_timeline.CalculateInterpolationAlpha();

			if (p_timeline.IsTransitioning())
				alpha = 0.0f;
			else if (p_timeline.IsReversed())
				alpha = -alpha;

			AltMath::Vector3f alphaOffset(alpha * m_frameSpacing, 0.0f, 0.0f);

			for (uint8_t starID = 1; starID < m_currentFrameIndicatorThickness; ++starID)
			{
				float lineSizeCoefficient = m_frameIndicatorLength * (starID / static_cast<float>(m_currentFrameIndicatorThickness));
				Rendering::Renderer::DrawStar(linePosition + m_orientation * lineSizeCoefficient + alphaOffset, !p_timeline.IsTransitioning() ? Data::Color::Red : Data::Color::Blue, 3.0f);
			}
		}
	}
}

void AnimationProgramming::Rendering::TimelineDrawer::DrawFrameCounter(const Animation::Timeline & p_timeline, const AltMath::Vector3f & p_worldPosition)
{
	/* Draw current and last frame separated by a '/' */
	uint32_t currentFrame = p_timeline.GetCurrentKeyFrame() + 1;
	uint32_t lastFrame = p_timeline.GetLastKeyFrame(true) + 1;

	AltMath::Vector3f numbersWorldOffset(p_worldPosition);
	AltMath::Vector3f numbersSpacingAxis(1.0f, 0.0f, 0.0f);
	AltMath::Vector3f separationLocalPosition(2.5f, 0.0f, 5.0f);

	float numbersPadding = 40.0f;

	Renderer::DrawNumber(currentFrame, numbersWorldOffset + numbersSpacingAxis * -numbersPadding * 0.5f, Data::Color::Red, m_digitSpacing, m_digitWidth, m_digitHeight);
	Renderer::DrawLine(numbersWorldOffset + separationLocalPosition, numbersWorldOffset - separationLocalPosition, Data::Color::Black);
	Renderer::DrawNumber(lastFrame, numbersWorldOffset + numbersSpacingAxis * numbersPadding * 0.5f, Data::Color::Black, m_digitSpacing, m_digitWidth, m_digitHeight);
}

void AnimationProgramming::Rendering::TimelineDrawer::DrawPlayIndicator(const Animation::Timeline& p_timeline, const AltMath::Vector3f& p_worldPosition)
{
	std::vector<AltMath::Vector3f> vertices
	{
		p_worldPosition + AltMath::Vector3f(-5.0f, 0.0f, 5.0f),
		p_worldPosition + AltMath::Vector3f(5.0f, 0.0f, 0.0f),
		p_worldPosition + AltMath::Vector3f(-5.0f, 0.0f, -5.0f),
	};

	Renderer::DrawShape(EShapeMode::TRIANGLES, vertices, p_timeline.IsPlaying() ? Data::Color(50, 205, 90) : m_indicatorDisabledColor);
}

void AnimationProgramming::Rendering::TimelineDrawer::DrawPauseIndicator(const Animation::Timeline & p_timeline, const AltMath::Vector3f & p_worldPosition)
{
	std::vector<AltMath::Vector3f> vertices
	{
		p_worldPosition + AltMath::Vector3f(-2.0f, 0.0f, 5.0f),
		p_worldPosition + AltMath::Vector3f(-2.0f, 0.0f, -5.0f),
		p_worldPosition + AltMath::Vector3f(2.0f, 0.0f, 5.0f),
		p_worldPosition + AltMath::Vector3f(2.0f, 0.0f, -5.0f)
	};

	Renderer::DrawShape(EShapeMode::LINES, vertices, p_timeline.IsPaused() ? Data::Color(50, 205, 90) : m_indicatorDisabledColor);
}

void AnimationProgramming::Rendering::TimelineDrawer::DrawTransitionIndicator(const Animation::Timeline & p_timeline, const AltMath::Vector3f & p_worldPosition)
{
	std::vector<AltMath::Vector3f> vertices
	{
		p_worldPosition + AltMath::Vector3f(-5.0f, 0.0f, 0.0f),
		p_worldPosition + AltMath::Vector3f(5.0f, 0.0f, 0.0f),
		p_worldPosition + AltMath::Vector3f(5.0f, 0.0f, 0.0f),
		p_worldPosition + AltMath::Vector3f(1.0f, 0.0f, 3.0f),
		p_worldPosition + AltMath::Vector3f(5.0f, 0.0f, 0.0f),
		p_worldPosition + AltMath::Vector3f(1.0f, 0.0f, -3.0f)
	};

	Renderer::DrawShape(EShapeMode::LINES, vertices, p_timeline.IsTransitioning() ? Data::Color::Blue : m_indicatorDisabledColor);
}
