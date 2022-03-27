#ifndef D9DC23B1_9143_4917_B212_390EBA2EE1DF
#define D9DC23B1_9143_4917_B212_390EBA2EE1DF

#include <functional>
#include <deque>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "MouseEvent.hpp"
#include "IEventManager.hpp"
#include "MouseData.hpp"
#include "Binding.hpp"

namespace Pathfinding::Events
{
    class EventManager final : public Pathfinding::Abstract::IEventManager
    {
    public:        
        explicit EventManager(sf::RenderWindow *window);
        
        void addBinding(Binding binding) override;
        
        void pushEvent(sf::Event event) override;
        
        void processEvents() override;
        

    private:
        sf::RenderWindow *windowPtr;
        std::deque<sf::Event> eventQueue;
        std::vector<Binding> bindings;
    };
}

#endif /* D9DC23B1_9143_4917_B212_390EBA2EE1DF */
