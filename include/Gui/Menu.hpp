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
            using fPtrVI = std::function<void(int64_t)>;
            using fPtrVV = std::function<void(void)>;
        public:
            Menu() = default;
            Menu(ApplicationState * appStat, int64_t offset, int64_t height, int64_t width);
            void show();
            void addNumberOfNodesChangedCallback(fPtrVI callBack);
            void addStepCallBack(fPtrVV callBack);
            void addStartCallback(fPtrVV callBack);
            bool initialized() const;
        private:
            void showCommonElements();
            void showReadyStateElements();
            void showNodeInfoInMenu();
            void showNodeInfoFlag();
            void showSearchingElements();
        private:
            float offset; 
            float height; 
            float width;
            ApplicationState * appStatePtr;
            bool nodeInfo;
        private:
            fPtrVI numberOfNodesChangedCallBack = nullptr;
            fPtrVV startCallBack = nullptr;
            GraphDimension * dimensionPtr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
