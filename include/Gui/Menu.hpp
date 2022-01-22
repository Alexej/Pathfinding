#ifndef EAA44AE2_6A11_4F15_8B18_A067DC162051
#define EAA44AE2_6A11_4F15_8B18_A067DC162051

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

namespace Pathfinding::Core
{
    class ApplicationState;
}

namespace Pathfinding::Gui
{
    using Pathfinding::Core::ApplicationState;
    class Menu
    {
        public:
            Menu(ApplicationState * appStat, int32_t offset, int32_t height, int32_t width);
            void show();
            void addNumberOfNodesChangedCallback(std::function<void(int32_t)> callBack);
            void addStepCallBack(std::function<void(void)> callBack);
            bool initialized() const;
        private:
            void showCommonElements();
            void showReadyStateElements();
        private:
            float offset; 
            float height; 
            float width;
            ApplicationState * appStatePtr;
            bool nodeInfo;
        private:
            std::function<void(int32_t)> numberOfNodesChangedCallBack = nullptr;
            std::function<void(void)> stepCallbBack = nullptr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
