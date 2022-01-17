#ifndef A32D7AB6_3CC7_40CF_8D83_283F2DC5E412
#define A32D7AB6_3CC7_40CF_8D83_283F2DC5E412

#include <deque>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GraphLocation.hpp"


namespace Pathfinding::Helpers
{
    class LatticeGraphOperations;
}

using Pathfinding::Helpers::LatticeGraphOperations;
using Pathfinding::Datastructures::GraphLocation;

namespace Pathfinding::Core
{
    class EventManager
    {
        public:
            explicit EventManager(sf::RenderWindow * window, LatticeGraphOperations * graphOps);
            void pushEvent(sf::Event event);
            void processEvents();
        private:
            GraphLocation mapMouseToGraphCoordinates(sf::Vector2i pos);
        private:
            std::deque<sf::Event> eventQueue;
            LatticeGraphOperations * graphOpsPtr;
            sf::RenderWindow * windowPtr;
            bool settingWall = false;
            bool clearingWall = false;
            bool settingStart = false;
            bool settingGoal = false;
    };
}

#endif /* A32D7AB6_3CC7_40CF_8D83_283F2DC5E412 */
