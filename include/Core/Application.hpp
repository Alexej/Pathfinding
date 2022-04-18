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
#include "IGraphOperations.hpp"
#include "AIncrementalInformedAlgorithm.hpp"
#include "IEventManager.hpp"
#include "IMenu.hpp"
#include "IApplication.hpp"
#include "MouseData.hpp"
#include "BindingsContainer.hpp"
#include "DrawablePath.hpp"
#include "DFSMazeGenerator.hpp"
#include "NodeStateColors.hpp"
#include "IFontLoader.hpp"
#include "GradientChanger.hpp"
#include "IRenderer.hpp"
#include "IDrawNodeStrategy.hpp"
#include "InformedSearchFunctions.hpp"

namespace Pathfinding::Core { class ApplicationBuilder; }
namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Core
{
    class Application final : public Pathfinding::Abstract::IApplication
    {
        friend Pathfinding::Core::ApplicationBuilder;

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

        void generateMaze();
        
        void step();

    private:
        void runAStar();

        void drawPath(const std::vector<const Pathfinding::Datastructures::Node *> & path, sf::Color color);

    private:
        std::unique_ptr<Pathfinding::Abstract::IMenu> menuUPtr = nullptr;
        std::unique_ptr<Pathfinding::Abstract::IEventManager> eventManagerUPtr = nullptr;
        std::unique_ptr<Pathfinding::Abstract::AIncrementalInformedAlgorithm> dstarLiteUPtr = nullptr;
        std::unique_ptr<Pathfinding::Abstract::IAStar> aStarUPtr = nullptr;
        std::unique_ptr<Pathfinding::Abstract::IGraphOperations> graphOpsUPtr = nullptr;
        std::unique_ptr<Pathfinding::Abstract::IRenderer> rendererUPtr = nullptr;
        std::shared_ptr<Pathfinding::Abstract::ALatGraphWr> latGraphWrapUPtr = nullptr;
        std::shared_ptr<Pathfinding::Abstract::IFontLoader> fontLoaderSPtr = nullptr;
        std::shared_ptr<Pathfinding::Abstract::IDrawNodeStrategy> drawStrategy = nullptr;

        Pathfinding::Core::ApplicationState appState;
        int32_t accumulator;
        sf::RenderWindow window;
        Pathfinding::Datastructures::PathfinderCache aStarCache;
        Pathfinding::Datastructures::PathfinderCache dStarCache;
        RandomIntegers ri;
        Pathfinding::Rendering::DrawablePath drawablePath;
        Pathfinding::Algorithms::DFSMazeGenerator dfsmg;
        Pathfinding::Rendering::NodeStateColors colors;
        Pathfinding::Rendering::BlockedAndStartGradientChanger gradChager;
        Pathfinding::Events::BindingsContainer bindings;

        GraphDimension *dimensionPtr = nullptr;
        Pathfinding::Datastructures::InformedSearchFunctions searchFunctions;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
