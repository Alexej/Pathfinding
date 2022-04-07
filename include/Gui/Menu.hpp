#ifndef EAA44AE2_6A11_4F15_8B18_A067DC162051
#define EAA44AE2_6A11_4F15_8B18_A067DC162051

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

#include "ApplicationState.hpp"
#include "IMenu.hpp"
#include "MenuCallBacks.hpp"

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

    public:
        Menu() = default;

        Menu(
            PCApplicationState *appStatePtr,
            PDPathfinderCache *aCache,
            PDPathfinderCache *dCache);

        void show() override;

        void addCallbacks(MenuCallBacks callBacks) override;

        void showGraph(std::vector<int32_t> values, std::string name) override;

        void showMouseWheelEventComboBox();

        
    private:
        void showCommonElements();

        void showReadyStateElements();

        void showNodeInfoInMenu();

        void showNodeInfoFlag();

        void showSearchingElements();

        void showAutoStepFlag();

        void showPathFlags();

        void showNumberOfNodesComboBox();

        void showSearchResults();

        void showDoneState();

        void showAStarPath();

        void showStepSpeed();

    private:
        float offset;
        float height;
        float width;
        PCApplicationState *appStatePtr;
        PCGraphDimension *dimensionPtr;
        PCAlgorithmStepSpeed *algoStepSpeedPtr;
        PDPathfinderCache *aCache;
        PDPathfinderCache *dCache;

    private:
        MenuCallBacks callBacks;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
