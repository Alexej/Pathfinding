#ifndef D956F987_718E_4625_80CB_EB681F69EE92
#define D956F987_718E_4625_80CB_EB681F69EE92

#include <SFML/Graphics/Color.hpp>

namespace Pathfinding::Datastructures { enum class NodeState; }

namespace Pathfinding::Rendering
{
    struct NodeStateColors
    {
        public:
            NodeStateColors();
            sf::Color getColor(Pathfinding::Datastructures::NodeState state) const;
            void reset();
        public:
            sf::Color freeNodeColor;
            sf::Color frontierNodeColor;
            sf::Color visitedNodeColor;
            sf::Color blockedNodeColor;
            sf::Color startNodeColor;
            sf::Color goalNodeColor;
    };
}

#endif /* D956F987_718E_4625_80CB_EB681F69EE92 */
