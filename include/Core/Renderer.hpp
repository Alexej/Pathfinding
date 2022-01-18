#ifndef EE121C46_77A1_42C0_82FD_AA5B2F176C40
#define EE121C46_77A1_42C0_82FD_AA5B2F176C40

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
}

using Pathfinding::Datastructures::LatticeGraph;
using Pathfinding::Datastructures::Node;

namespace Pathfinding::Core
{
    struct ApplicationState;
    class Renderer
    {
    public:
        Renderer();
        void render(sf::RenderWindow &window, const LatticeGraph & graph, int32_t nodeSideLength, bool showNodeInfo);
    private:
        void loadFont(std::string font);
        void drawNode(sf::RenderWindow &window, const Node &node, sf::Vector2f coords);
        void renderNodeInfo(sf::RenderWindow &window, const Node &node, sf::Vector2f coords, int32_t nodeSideLength);
    private:
        sf::RectangleShape nodeRect;
        sf::Text text;
        sf::Font font;
    };
}

#endif /* EE121C46_77A1_42C0_82FD_AA5B2F176C40 */
