#ifndef EAA44AE2_6A11_4F15_8B18_A067DC162051
#define EAA44AE2_6A11_4F15_8B18_A067DC162051

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

#include "ApplicationState.hpp"
#include "IMenu.hpp"

namespace Pathfinding::Core { struct ApplicationState; }
namespace Pathfinding::Core { class GraphDimension; }
namespace Pathfinding::Core { class AlgorithmStepSpeed; }
namespace Pathfinding::Datastructures { struct PathfinderCache; }

namespace Pathfinding::Gui
{
    class Menu final : public Pathfinding::Abstract::IMenu
    {
        private:
            using PCApplicationState = Pathfinding::Core::ApplicationState;
            using PCGraphDimension = Pathfinding::Core::GraphDimension;
            using PCAlgorithmStepSpeed = Pathfinding::Core::AlgorithmStepSpeed;
            using PDPathfinderCache = Pathfinding::Datastructures::PathfinderCache;
            using fPtrVI = std::function<void(int32_t)>;
            using fPtrVV = std::function<void(void)>;
        public:
            Menu() = default;

            Menu(
                PCApplicationState * appStatePtr, 
                PDPathfinderCache * aCache,
                PDPathfinderCache * dCache);

            void show() override;

            void addNumberOfNodesChangedCallBack(fPtrVI callBack) override;

            void addStepCallBack(fPtrVV callBack) override;

            void addStartCallBack(fPtrVV callBack) override;

            void addResetCallBack(fPtrVV callBack) override;

            void addRandomGraphCallBack(fPtrVV callBack) override;

            bool initialized() const override;

            void showGraph(std::vector<int32_t> values, std::string name) override;

        private:
            void showCommonElements();

            void showReadyStateElements();

            void showNodeInfoInMenu();

            void showNodeInfoFlag();

            void showSearchingElements();

            void showAutoStepFlag();

            void showPathFlags();

            void showAlgorithmStepSpeedComboBox();

            void showNumberOfNodesComboBox();

            void showSearchResults();

            void showDoneState();

            void showAStarPath();
            
        private:
            float offset; 
            float height; 
            float width;
            PCApplicationState * appStatePtr;
            PCGraphDimension * dimensionPtr;
            PCAlgorithmStepSpeed * algoStepSpeedPtr;
            PDPathfinderCache * aCache;
            PDPathfinderCache * dCache;
            
        private:
            fPtrVI numberOfNodesChangedCallBack = nullptr;
            fPtrVV startCallBack = nullptr;
            fPtrVV resetCallback = nullptr;
            fPtrVV stepCallBack = nullptr;
            fPtrVV randomGraphCallBack = nullptr;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
