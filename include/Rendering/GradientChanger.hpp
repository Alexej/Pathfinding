#ifndef DE003256_8D3B_4E42_B430_0C4C8445B891
#define DE003256_8D3B_4E42_B430_0C4C8445B891

#include <SFML/Graphics/Color.hpp>

#include "Node.hpp"
#include "RenderingHelpers.hpp"
#include "NodeStateColors.hpp"

namespace Pathfinding::Rendering
{
    struct Gradients
    {
        private:
            using PHColorGradient = Pathfinding::Helpers::ColorGradient;
        public:
            PHColorGradient gradientBlockedRed;
            PHColorGradient gradientBlockedBlue;
            PHColorGradient gradientGoalRed;
            PHColorGradient gradientGoalGreen;
    };

    class GradientChanger
    {
        public:
            void init(NodeStateColors & colors)
            {
                startColor = &colors.startNodeColor;
                blockedColor = &colors.blockedNodeColor;
            }

            void updateBlockedColor()
            {
                gradients.gradientBlockedRed(blockedColor->r, 5);
                gradients.gradientBlockedBlue(blockedColor->b, 1);
            }

            void updateStartColor()
            {
                gradients.gradientGoalRed(startColor->r, 5);   
                gradients.gradientGoalGreen(startColor->g, 5);
            }

        private:
            Gradients gradients;
            sf::Color * startColor;
            sf::Color * blockedColor;
    };
}

#endif /* DE003256_8D3B_4E42_B430_0C4C8445B891 */
