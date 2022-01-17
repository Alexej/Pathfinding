#ifndef A32D7AB6_3CC7_40CF_8D83_283F2DC5E412
#define A32D7AB6_3CC7_40CF_8D83_283F2DC5E412

#include <deque>
#include <SFML/Window/Event.hpp>

namespace Pathfinding::Core
{
    class EventManager
    {
        public:
            void pushEvent(sf::Event event);
            void processEvents();
        private:
            std::deque<sf::Event> eventQueue;
    };
}

#endif /* A32D7AB6_3CC7_40CF_8D83_283F2DC5E412 */
