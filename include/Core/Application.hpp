#ifndef D723E2D5_1943_4166_87CC_73F5C9C47544
#define D723E2D5_1943_4166_87CC_73F5C9C47544

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdint>
#include <memory>

#include "Renderer.hpp"
#include "LatticeGraph.hpp"
#include "ApplicationState.hpp"
#include "EventManager.hpp"
#include "Menu.hpp"
#include "DStarLite.hpp"
#include "GraphOperations.hpp"
#include "IApplication.hpp"
#include "IAStar.hpp"
#include "PathfinderCache.hpp"

namespace Pathfinding::Abstract { class ALatticeGraphWrapper; }
namespace Pathfinding::Helpers { class ApplicationBuilder; }

namespace Pathfinding::Core
{
    class Application final : public Pathfinding::Abstract::IApplication
    {
        friend Pathfinding::Helpers::ApplicationBuilder;
    private:
        using PAIMenu = Pathfinding::Abstract::IMenu;
        using PAIEventManager = Pathfinding::Abstract::IEventManager;
        using PAIDStarLite = Pathfinding::Abstract::IDStarLite;
        using PALatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PAIGraphOperations = Pathfinding::Abstract::IGraphOperations;
        using PAIRenderer = Pathfinding::Abstract::IRenderer;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PAALatticeGraphWrapper = Pathfinding::Abstract::ALatticeGraphWrapper;
        using PAIAStar = Pathfinding::Abstract::IAStar;
        using PDPathfinderCachee = Pathfinding::Datastructures::PathfinderCache;
    public:
        Application() = default;
        
        void run();
        
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
        
        void step();
        
    private:
        std::unique_ptr<PAIRenderer> rendererUPtr;
        std::unique_ptr<PAIMenu> menuUPtr;
        std::unique_ptr<PAIEventManager> eventManagerUPtr;
        std::unique_ptr<PAIDStarLite> dstarLiteUPtr;
        std::unique_ptr<PAIAStar> aStarUPtr;
        std::unique_ptr<PAIGraphOperations> graphOpsUPtr;
        std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapUPtr;

        PCApplicationState appState;
        int32_t accumulator;
        sf::RenderWindow window;
        PDPathfinderCachee aStarCache;
        PDPathfinderCachee dStarCache;
        
        GraphDimension *dimensionPtr;
        AlgorithmStepSpeed *algoStepSpeedPtr;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
