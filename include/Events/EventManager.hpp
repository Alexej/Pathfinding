#ifndef D9DC23B1_9143_4917_B212_390EBA2EE1DF
#define D9DC23B1_9143_4917_B212_390EBA2EE1DF

#include <functional>
#include <deque>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "MouseEvent.hpp"

namespace Pathfinding::Events
{
    class EventManager
    {
    public:
        EventManager() = default;
        explicit EventManager(sf::RenderWindow *window);
        void addBinding(MouseEvent event, std::function<void(sf::Vector2i)> callbackFunc);
        void pushEvent(sf::Event event);
        void processEvents();

    private:
        sf::RenderWindow *windowPtr;
        std::deque<sf::Event> eventQueue;
        std::vector<std::pair<MouseEvent, std::function<void(sf::Vector2i)>>> callBacks;
    };
}

#endif /* D9DC23B1_9143_4917_B212_390EBA2EE1DF */
