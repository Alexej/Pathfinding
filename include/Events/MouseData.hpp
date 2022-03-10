#ifndef EF091C2C_702A_4E72_882C_6AB418436A17
#define EF091C2C_702A_4E72_882C_6AB418436A17

#include <SFML\System\Vector2.hpp>

namespace Pathfinding::Events
{
    struct MouseData
    {
        MouseData(sf::Vector2i cursorPosition_) : cursorPosition(cursorPosition_) {}
        
        MouseData(sf::Vector2i cursorPosition_, int32_t wheelDelta_) 
        
        : cursorPosition(cursorPosition_), wheelDelta(wheelDelta_) {}
        
        sf::Vector2i cursorPosition;
        int32_t wheelDelta;
    };
}

#endif /* EF091C2C_702A_4E72_882C_6AB418436A17 */
