#ifndef E7969F18_4838_4B8E_9C02_D784C49BD79C
#define E7969F18_4838_4B8E_9C02_D784C49BD79C

#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace Pathfinding::Events { class BindingsContainer; }

namespace Pathfinding::Abstract
{
    class IEventManager
    {
        private:
            using PEBindingsContainer = Pathfinding::Events::BindingsContainer;
        public:            
            virtual void pushEvent(sf::Event event) = 0;
            
            virtual void processEvents(const PEBindingsContainer & bindings) = 0;
            
            virtual ~IEventManager() = default;
            
    };
}

#endif /* E7969F18_4838_4B8E_9C02_D784C49BD79C */
