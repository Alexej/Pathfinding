#ifndef D723E2D5_1943_4166_87CC_73F5C9C47544
#define D723E2D5_1943_4166_87CC_73F5C9C47544

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <deque>

#include "Renderer.hpp"
#include "LatticeGraph.hpp"
#include "ApplicationState.hpp"
#include "EventManager.hpp"
#include "Menu.hpp"
#include "DStarLite.hpp"
#include "GraphOperations.hpp"

namespace Pathfinding::Core
{

    class Application
    {
    private:
        using PGMenu = Pathfinding::Gui::Menu;
        using PEEventManager = Pathfinding::Events::EventManager;
        using PADStarLite = Pathfinding::Algorithms::DStarLite;
        using PALatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PHGraphOperations = Pathfinding::Helpers::GraphOperations;

    public:
        Application();
        void run();

    private:
        void createObbjects();
        void draw();
        void update(sf::Clock &deltaClock);
        void handleInput(sf::Event event);
        void handleNumberOfNodesChange(int32_t index);
        void startAlgorithm();
        void reset();
        void done();
        void noPath();
        void randomGraph();

    private:
        ApplicationState appState;
        sf::RenderWindow window;
        Renderer renderer;
        PALatticeGraph graph;
        PEEventManager eventManager;
        PGMenu menu;
        PADStarLite dstar;
        PHGraphOperations graphOps;
        GraphDimension *dimensionPtr;
        AlgorithmStepSpeed *algoStepSpeedPtr;
        int32_t accumulator;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
