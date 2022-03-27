#ifndef B9E46EEC_476A_469D_9500_CFB8E28280E2
#define B9E46EEC_476A_469D_9500_CFB8E28280E2

#include <SFML/Window/Event.hpp>

namespace Pathfinding::Events
{
    struct MouseEvent
    {
        bool eventOnly = false;
        sf::Event::EventType event;
        sf::Mouse::Button button;
    };
}

#endif /* B9E46EEC_476A_469D_9500_CFB8E28280E2 */
