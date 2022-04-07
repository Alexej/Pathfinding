#ifndef DE003256_8D3B_4E42_B430_0C4C8445B891
#define DE003256_8D3B_4E42_B430_0C4C8445B891

#include <SFML/Graphics/Color.hpp>

#include "Node.hpp"
#include "NodeStateColors.hpp"
#include "ApplicationState.hpp"

namespace Pathfinding::Rendering
{
    class ColorGradient
    {
    public:
        void operator()(uint8_t &color, uint8_t incrementStep);

    private:
        bool increment = true;
    };

    class BlockedAndStartGradientChanger
    {
    public:
        void init(NodeStateColors &colors);

        void updateColors(Pathfinding::Core::AlgorithmState state);

    private:
        void updateBlockedColor();

        void updateStartColor();

    private:
        ColorGradient gradientBlockedRed;
        ColorGradient gradientBlockedBlue;
        ColorGradient gradientGoalRed;
        ColorGradient gradientGoalGreen;

        sf::Color *startColor;
        sf::Color *blockedColor;
    };
}

#endif /* DE003256_8D3B_4E42_B430_0C4C8445B891 */
