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
    public:
        Menu() = default;

        Menu(
            Pathfinding::Core::ApplicationState *appStatePtr,
            Pathfinding::Datastructures::PathfinderCache *aCache,
            Pathfinding::Datastructures::PathfinderCache *dCache);

        void show() override;

        void addCallbacks(MenuCallBacks callBacks) override;

        void showGraph(std::vector<int32_t> values, std::string name) const override;

        void update(sf::RenderWindow & window, sf::Time deltaClock) override;

        void processEvent(const sf::Event & event) override;

        void shutDown() override;

        void init(sf::RenderWindow & window) override;

        void render(sf::RenderWindow & window) override;

        
    private:
        void showGraphs() const;

        void showMouseWheelEventComboBox();

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
    
        void showRuntimeOptions();

        void showNodeInfo();

        void showAlgorithmState();

        void showResetButton();

        void showStartOptions();

        void showStartButton();

        void showRandomGraph();

        void showMazeButton();


    private:
        float offset;
        float height;
        float width;
        Pathfinding::Core::ApplicationState *appStatePtr;
        Pathfinding::Core::AlgorithmStepSpeed *algoStepSpeedPtr;
        Pathfinding::Datastructures::PathfinderCache *aCache;
        Pathfinding::Datastructures::PathfinderCache *dCache;
        Pathfinding::Core::GraphDimension *dimensionPtr;

    private:
        MenuCallBacks callBacks;
    };
}

#endif /* EAA44AE2_6A11_4F15_8B18_A067DC162051 */
