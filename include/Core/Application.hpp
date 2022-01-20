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
#include "GraphLocation.hpp"
#include "EventManager.hpp"
#include "Menu.hpp"
#include "DStarLite.hpp"
#include "GraphOperations.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Gui::Menu;
    using Pathfinding::Events::EventManager;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::GraphLocation;
    using Pathfinding::Helpers::GraphOperations;

    class Application
    {
    public:
        Application();
        void run();

    private:
        void draw();
        void update(sf::Clock &deltaClock);
        void handleInput(sf::Event event);
        void handleNumberOfNodesChange();
    private:
        ApplicationState appState;
        sf::RenderWindow window;
        Renderer renderer;
        LatticeGraph graph;
        EventManager eventManager;
        Menu menu;
        DStarLite dstar;
        GraphOperations graphOps;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
