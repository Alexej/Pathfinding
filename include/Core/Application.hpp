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
#include "LatticeGraphOperations.hpp"

using namespace Pathfinding::Constants;
using Pathfinding::Datastructures::LatticeGraph;
using Pathfinding::Datastructures::GraphLocation;
using Pathfinding::Helpers::LatticeGraphOperations;


namespace Pathfinding::Core
{
    class Application
    {
        public:
            Application();
            void run();
            void update();
            void draw();
            void handleInput();
        private:
            sf::RenderWindow window;
            Renderer renderer;
            std::deque<sf::Event> events;
            LatticeGraph graph;
            ApplicationState appState;
            LatticeGraphOperations graphOps;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
