#ifndef EE121C46_77A1_42C0_82FD_AA5B2F176C40
#define EE121C46_77A1_42C0_82FD_AA5B2F176C40

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "IRenderer.hpp"


namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
    enum class NodeState;
}

namespace Pathfinding::Core
{
    class ApplicationState;
    class GraphDimension;
    class Renderer final : public Pathfinding::Abstract::IRenderer
    {
    private:
        using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDNodeState = Pathfinding::Datastructures::NodeState;

    public:
        Renderer() = default;
        Renderer(sf::RenderWindow *window, ApplicationState *state);
        void render(const PDLatticeGraph &graph) override;
        void renderPath(std::vector<PDNode *> path) override;
        void update() override;
        void reset() override;

    private:
        void init();
        void loadFont(std::string font);
        void drawNode(const PDNode &node, sf::Vector2f coords);
        void renderNodeInfo(const PDNode &node, sf::Vector2f coords);
        void renderPathLineEndPoints(std::vector<PDNode *> path, sf::Vector2f pointPositionOffset);
        void renderPathLines(std::vector<PDNode *> path, sf::Vector2f pointPositionOffset);
        sf::Color stateColor(PDNodeState state);
        void updateColor();
    private:
        sf::RectangleShape nodeRect;
        sf::Text text;
        sf::Font font;
        sf::CircleShape nodePoint;
        sf::RectangleShape diagonalLine;
        sf::RectangleShape straightLine;
        sf::RenderWindow *windowPtr = nullptr;
        ApplicationState *appStatePtr = nullptr;
        GraphDimension *dimensionPtr = nullptr;
        sf::Color goalNodeDiff = sf::Color::Black;
        sf::Color visitedNodeDiff = sf::Color::Black;
        sf::Color goalColor;
        sf::Color visitedColor;
        bool colorUp = false;
    };
}

#endif /* EE121C46_77A1_42C0_82FD_AA5B2F176C40 */
