#ifndef EAA44AE2_6A11_4F15_8B18_A067DC162051
#define EAA44AE2_6A11_4F15_8B18_A067DC162051

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

namespace Pathfinding::Core
{
    class ApplicationState;
    class GraphDimension;
}

namespace Pathfinding::Gui
{
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::GraphDimension;
    class Menu
    {
        private:
            using fPtrVI = std::function<void(int32_t)>;
            using fPtrVV = std::function<void(int32_t)>;
        public:
            Menu() = default;
            Menu(ApplicationState * appStat, int32_t offset, int32_t height, int32_t width);
            void show();
            void addNumberOfNodesChangedCallback(fPtrVI callBack);
            void addStepCallBack(fPtrVV callBack);
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
            fPtrVI numberOfNodesChangedCallBack = nullptr;
            fPtrVV stepCallbBack = nullptr;
            GraphDimension * dimensionPtr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
