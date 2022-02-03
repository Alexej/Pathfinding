#ifndef D723E2D5_1943_4166_87CC_73F5C9C47544
#define D723E2D5_1943_4166_87CC_73F5C9C47544

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <stdint.h>
#include <deque>

#include "Constants.hpp"
#include "Renderer.hpp"
#include "LatticeGraph.hpp"
#include "ApplicationState.hpp"
#include "Vector2.hpp"
#include "EventManager.hpp"
#include "Menu.hpp"
#include "DStarLite.hpp"
#include "GraphOperations.hpp"
#include "GraphDimension.hpp"


namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Gui::Menu;
    using Pathfinding::Events::EventManager;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::GraphOperations;
    using Pathfinding::Core::GraphDimension;

    class Application
    {
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
        LatticeGraph graph;
        EventManager eventManager;
        Menu menu;
        DStarLite dstar;
        GraphOperations graphOps;
        GraphDimension * dimension;
        int32_t accumulator; 
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
