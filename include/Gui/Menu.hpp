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
    class Menu
    {
        private:
            using PCApplicationState = Pathfinding::Core::ApplicationState;
            using PCGraphDimension = Pathfinding::Core::GraphDimension;
            using fPtrVI = std::function<void(int32_t)>;
            using fPtrVV = std::function<void(void)>;
        public:
            Menu() = default;
            Menu(PCApplicationState * appStat, int32_t offset, int32_t height, int32_t width);
            void show();
            void addNumberOfNodesChangedCallBack(fPtrVI callBack);
            void addStepCallBack(fPtrVV callBack);
            void addStartCallBack(fPtrVV callBack);
            void addResetCallBack(fPtrVV callBack);
            void addRandomGraphCallBack(fPtrVV callBack);
            bool initialized() const;
        private:
            void showCommonElements();
            void showReadyStateElements();
            void showNodeInfoInMenu();
            void showNodeInfoFlag();
            void showSearchingElements();
            void printLargeText(std::string text, double factor);
            void showAutoStepFlag();
            void showPathFlags();
        private:
            float offset; 
            float height; 
            float width;
            bool nodeInfo;
            bool autoStep;
            bool showPathLines;
            bool showPath;
            PCApplicationState * appStatePtr;
        private:
            fPtrVI numberOfNodesChangedCallBack = nullptr;
            fPtrVV startCallBack = nullptr;
            fPtrVV resetCallback = nullptr;
            fPtrVV stepCallBack = nullptr;
            fPtrVV randomGraphCallBack = nullptr;
            PCGraphDimension * dimensionPtr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
