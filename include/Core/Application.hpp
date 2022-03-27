#ifndef D723E2D5_1943_4166_87CC_73F5C9C47544
#define D723E2D5_1943_4166_87CC_73F5C9C47544

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <memory>

#include "RandomIntegers.hpp"
#include "IAStar.hpp"
#include "PathfinderCache.hpp"
#include "ALatGraphWr.hpp"
#include "ApplicationState.hpp"
#include "IRenderer.hpp"
#include "IGraphOperations.hpp"
#include "AIncrementalInformedAlgorithm.hpp"
#include "IEventManager.hpp"
#include "IMenu.hpp"
#include "IApplication.hpp"
#include "MouseData.hpp"
#include "BindingsContainer.hpp"

namespace Pathfinding::Core { class ApplicationBuilder; }

namespace Pathfinding::Core
{
    class Application final : public Pathfinding::Abstract::IApplication
    {
        friend Pathfinding::Core::ApplicationBuilder;
    private:
        using PAIMenu = Pathfinding::Abstract::IMenu;
        using PAIEventManager = Pathfinding::Abstract::IEventManager;
        using PAAIncrementalInformedAlgorithm = Pathfinding::Abstract::AIncrementalInformedAlgorithm;
        using PAIGraphOperations = Pathfinding::Abstract::IGraphOperations;
        using PAIRenderer = Pathfinding::Abstract::IRenderer;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PAIAStar = Pathfinding::Abstract::IAStar;
        using PDPathfinderCachee = Pathfinding::Datastructures::PathfinderCache;
        using PEMouseData = Pathfinding::Events::MouseData;
        using PEBindingsContainer = Pathfinding::Events::BindingsContainer;

    public:
        Application() = default;
        
        void run();
        
        void mouseWheelMoved(PEMouseData mouseData);

    private:
        void draw();
        
        void update(sf::Clock &deltaClock);
        
        void handleInput(sf::Event event);
        
        void handleNumberOfNodesChange(int32_t index);
        
        void startAlgorithm();
        
        void reset();
        
        void done();
        
        void noPath();
        
        void randomGraph();

        void generateMaze();
        
        void step();

        void mouseWheelEventChanged(int32_t index);

    private:
        void runAStar();

    private:
        std::unique_ptr<PAIRenderer> rendererUPtr;
        std::unique_ptr<PAIMenu> menuUPtr;
        std::unique_ptr<PAIEventManager> eventManagerUPtr;
        std::unique_ptr<PAAIncrementalInformedAlgorithm> dstarLiteUPtr;
        std::unique_ptr<PAIAStar> aStarUPtr;
        std::unique_ptr<PAIGraphOperations> graphOpsUPtr;
        std::shared_ptr<PAALatGraphWr> latGraphWrapUPtr;

        PCApplicationState appState;
        int32_t accumulator;
        sf::RenderWindow window;
        PDPathfinderCachee aStarCache;
        PDPathfinderCachee dStarCache;
        RandomIntegers ri;
        
        GraphDimension *dimensionPtr;
        PEBindingsContainer bindings;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
