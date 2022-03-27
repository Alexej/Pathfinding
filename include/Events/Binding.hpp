#ifndef AB338952_A731_47BA_A7FE_E0F127AAA17C
#define AB338952_A731_47BA_A7FE_E0F127AAA17C

#include "MouseEvent.hpp"

namespace Pathfinding::Events
{
    struct Binding
    {
        std::string name;
        MouseEvent mouseEvent;
        std::function<void(MouseData)> callback;
    };
}

#endif /* AB338952_A731_47BA_A7FE_E0F127AAA17C */
