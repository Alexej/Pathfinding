#ifndef B9E46EEC_476A_469D_9500_CFB8E28280E2
#define B9E46EEC_476A_469D_9500_CFB8E28280E2

#include <SFML/Window/Event.hpp>

namespace Pathfinding::Events
{
    struct MouseEvent
    {
        MouseEvent(bool eventOnly_, sf::Event::EventType event_, sf::Mouse::Button button_)
        : eventOnly(eventOnly_), event(event_), button(button_){}
        bool eventOnly = false;
        sf::Event::EventType event;
        sf::Mouse::Button button;
    };
}

#endif /* B9E46EEC_476A_469D_9500_CFB8E28280E2 */
