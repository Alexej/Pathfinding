#ifndef E7969F18_4838_4B8E_9C02_D784C49BD79C
#define E7969F18_4838_4B8E_9C02_D784C49BD79C

#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace Pathfinding::Events
{
    struct MouseEvent;
}

namespace Pathfinding::Abstract
{
    class IEventManager
    {
        private:
            using PEMouseEvent = Pathfinding::Events::MouseEvent;
        public:
            virtual void addBinding(PEMouseEvent event, std::function<void(sf::Vector2i)> callbackFunc) = 0;
            virtual void pushEvent(sf::Event event) = 0;
            virtual void processEvents() = 0;
    };
}

#endif /* E7969F18_4838_4B8E_9C02_D784C49BD79C */
