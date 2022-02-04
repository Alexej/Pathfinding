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

namespace Pathfinding::Core
{

    class ApplicationState;
    class GraphDimension;
    class Renderer
    {
    private:
        using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PDNode = Pathfinding::Datastructures::Node;

    public:
        Renderer() = default;
        Renderer(sf::RenderWindow *window, ApplicationState *state);
        void render(const PDLatticeGraph &graph);
        void renderPath(std::vector<PDNode *> path);
        void init();

    private:
        void loadFont(std::string font);
        void drawNode(const PDNode &node, sf::Vector2f coords);
        void renderNodeInfo(const PDNode &node, sf::Vector2f coords);

    private:
        sf::RectangleShape nodeRect;
        sf::Text text;
        sf::Font font;
        sf::RenderWindow *windowPtr = nullptr;
        ApplicationState *appStatePtr = nullptr;
        GraphDimension *dimensionPtr = nullptr;

        /**
         * ! absolute path bad, fix later.
         */
        std::string fontPath = "C:\\Users\\alexe\\Desktop\\project\\Pathfinding\\dependencies\\fonts\\";
    };
}

#endif /* EE121C46_77A1_42C0_82FD_AA5B2F176C40 */
