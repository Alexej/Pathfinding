#ifndef EAA44AE2_6A11_4F15_8B18_A067DC162051
#define EAA44AE2_6A11_4F15_8B18_A067DC162051

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

#include "IMenu.hpp"

namespace Pathfinding::Core
{
    class ApplicationState;
    class GraphDimension;
    class AlgorithmStepSpeed;
}

namespace Pathfinding::Abstract
{
    class IApplicationState;
}

namespace Pathfinding::Gui
{
    class Menu final : public Pathfinding::Abstract::IMenu
    {
        private:
            using PAIApplicationState = Pathfinding::Abstract::IApplicationState;
            using PCGraphDimension = Pathfinding::Core::GraphDimension;
            using PCAlgorithmStepSpeed = Pathfinding::Core::AlgorithmStepSpeed;
            using fPtrVI = std::function<void(int32_t)>;
            using fPtrVV = std::function<void(void)>;
        public:
            Menu() = default;
            Menu(std::shared_ptr<PAIApplicationState> stateSPtr, int32_t offset, int32_t height, int32_t width);
            void show() override;
            void addNumberOfNodesChangedCallBack(fPtrVI callBack) override;
            void addStepCallBack(fPtrVV callBack) override;
            void addStartCallBack(fPtrVV callBack) override;
            void addResetCallBack(fPtrVV callBack) override;
            void addRandomGraphCallBack(fPtrVV callBack) override;
            bool initialized() const override;
        private:
            void showCommonElements();
            void showReadyStateElements();
            void showNodeInfoInMenu();
            void showNodeInfoFlag();
            void showSearchingElements();
            void printLargeText(std::string text, double factor);
            void showAutoStepFlag();
            void showPathFlags();
            void showAlgorithmStepSpeedComboBox();
            void showNumberOfNodesComboBox();
        private:
            float offset; 
            float height; 
            float width;
            bool nodeInfo;
            bool autoStep;
            bool showPathLines;
            bool showPath;
            std::shared_ptr<PAIApplicationState>  appStateSPtr;
        private:
            fPtrVI numberOfNodesChangedCallBack = nullptr;
            fPtrVV startCallBack = nullptr;
            fPtrVV resetCallback = nullptr;
            fPtrVV stepCallBack = nullptr;
            fPtrVV randomGraphCallBack = nullptr;
            PCGraphDimension * dimensionPtr;
            PCAlgorithmStepSpeed * algoStepSpeedPtr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
