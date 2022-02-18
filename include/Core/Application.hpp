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
#include <memory>

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
        using PAIRenderer = Pathfinding::Abstract::IRenderer;

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
        void step();
    private:
        std::unique_ptr<PAIRenderer> rendererUPtr;
        std::unique_ptr<PGMenu> menuUPtr;
        std::unique_ptr<PEEventManager> eventManagerUPtr;
        std::unique_ptr<PADStarLite> dstarLiteUPtr;
        std::unique_ptr<PHGraphOperations> graphOpsUPtr;

        ApplicationState appState;
        sf::RenderWindow window;
        PALatticeGraph graph;

        int32_t accumulator;
        // For easier access
        GraphDimension *dimensionPtr;
        AlgorithmStepSpeed *algoStepSpeedPtr;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
