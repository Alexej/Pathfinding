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

using namespace Pathfinding::Constants;
using Pathfinding::Datastructures::LatticeGraph;
using Pathfinding::Datastructures::GraphLocation;
using Pathfinding::Events::EventManager;

namespace Pathfinding::Core
{
    enum class MouseAction {SETTING_START, SETTING_GOAL, BLOCKING_NODE, CLEARING_NODE, IDLE};
    class Application
    {
        public:
            Application();
            void run();
            void draw();
            void update(sf::Clock & deltaClock);
            void handleInput(sf::Event event);
            void handleNumberOfNodesChange();
        private:
            void leftMouseButtonPressed(sf::Vector2i pos);
            void rightMouseButtonPressed(sf::Vector2i pos);
            void mouseMoved(sf::Vector2i pos);
            void mouseButtonReleased(sf::Vector2i pos);
        private:
            MouseAction currentMouseAction = MouseAction::IDLE;
            ApplicationState appState;
            sf::RenderWindow window;
            Renderer renderer;
            LatticeGraph graph;
            EventManager eventManager;
            Menu menu;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
