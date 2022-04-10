#include "GradientChanger.hpp"

namespace Pathfinding::Rendering
{
    void ColorGradient::operator()(uint8_t &color, uint8_t incrementStep)
    {
        int32_t color32 = static_cast<int32_t>(color);
        int32_t incrementStep32 = static_cast<int32_t>(incrementStep);
        if (increment)
        {
            int32_t incrementedColor32 = color32 + incrementStep32;
            if (incrementedColor32 <= static_cast<int32_t>(Pathfinding::Constants::MAX_COLOR_CHANNEL))
            {
                color = static_cast<uint8_t>(incrementedColor32);
            }
            else
            {
                increment = false;
            }
        }
        else if (!increment)
        {
            int32_t decrementedcolor32 = color32 - incrementStep32;
            if (decrementedcolor32 >= static_cast<int32_t>(Pathfinding::Constants::MIN_COLOR_CHANNEL))
            {
                color = static_cast<uint8_t>(decrementedcolor32);
            }
            else
            {
                increment = true;
            }
        }
    }

    void BlockedAndStartGradientChanger::init(NodeStateColors &colors)
    {
        startColor = &colors.startNodeColor;
        blockedColor = &colors.blockedNodeColor;
    }

    void BlockedAndStartGradientChanger::updateColors(Pathfinding::Core::AlgorithmState state)
    {
        switch (state)
        {
        case Pathfinding::Core::AlgorithmState::NO_PATH:
            updateBlockedColor();
            break;
        case Pathfinding::Core::AlgorithmState::FOUND_PATH:
            updateStartColor();
            break;
        }
    }

    void BlockedAndStartGradientChanger::updateBlockedColor()
    {
        gradientBlockedRed(blockedColor->r, 5);
        gradientBlockedBlue(blockedColor->b, 1);
    }

    void BlockedAndStartGradientChanger::updateStartColor()
    {
        gradientGoalRed(startColor->r, 5);
        gradientGoalGreen(startColor->g, 5);
    }
}