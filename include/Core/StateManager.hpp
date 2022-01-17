#ifndef D16546E5_91C6_4DC0_BD14_6DF112E17937
#define D16546E5_91C6_4DC0_BD14_6DF112E17937

#include <stack>
#include <memory>

namespace Pathfinding::Core::Abstract
{
    class AState;
}

using Pathfinding::Core::Abstract::AState;

namespace Pathfinding::Core
{
    class StateManager
    {
        public:
            void handleEvent();
            void update();
            void draw();
        private:
            std::stack<std::unique_ptr<AState>> states;
    };
}

#endif /* D16546E5_91C6_4DC0_BD14_6DF112E17937 */
