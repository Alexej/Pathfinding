#ifndef EAA44AE2_6A11_4F15_8B18_A067DC162051
#define EAA44AE2_6A11_4F15_8B18_A067DC162051

#include <SFML/Graphics/RenderWindow.hpp>

namespace Pathfinding::Core
{
    struct ApplicationState;
}

namespace Pathfinding::Gui
{
    using Pathfinding::Core::ApplicationState;
    class Menu
    {
        public:
            Menu(ApplicationState * appStat, int32_t offset, int32_t height, int32_t width);
            void show();
        private:
            bool nodeSizeLargeEnoughForInfo();
        private:
            float offset; 
            float height; 
            float width;
            ApplicationState * appStatePtr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
