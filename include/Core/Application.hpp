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

namespace Pathfinding::Core { class ApplicationBuilder; }
namespace Pathfinding::Datastructures { struct Node; }

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
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PAIAStar = Pathfinding::Abstract::IAStar;
        using PDPathfinderCache = Pathfinding::Datastructures::PathfinderCache;
        using PEMouseData = Pathfinding::Events::MouseData;
        using PEBindingsContainer = Pathfinding::Events::BindingsContainer;
        using PRDrawablePath = Pathfinding::Rendering::DrawablePath;
        using PDNode = Pathfinding::Datastructures::Node;
        using PADSFMazeGenerator = Pathfinding::Algorithms::DFSMazeGenerator;
        using PRNodeStateColors = Pathfinding::Rendering::NodeStateColors;
        using PAIFontLoader = Pathfinding::Abstract::IFontLoader;
        using PRGradientChanger = Pathfinding::Rendering::GradientChanger;
        using PAIRenderer = Pathfinding::Abstract::IRenderer;

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

        void mouseWheelEventChanged(int32_t index);

    private:
        void runAStar();

        void drawPath(const std::vector<const PDNode *> & path, sf::Color color);

        void updateColors();

    private:
        std::unique_ptr<PAIMenu> menuUPtr = nullptr;
        std::unique_ptr<PAIEventManager> eventManagerUPtr = nullptr;
        std::unique_ptr<PAAIncrementalInformedAlgorithm> dstarLiteUPtr = nullptr;
        std::unique_ptr<PAIAStar> aStarUPtr = nullptr;
        std::unique_ptr<PAIGraphOperations> graphOpsUPtr = nullptr;
        std::unique_ptr<PAIRenderer> rendererUPtr = nullptr;
        std::shared_ptr<PAALatGraphWr> latGraphWrapUPtr = nullptr;
        std::shared_ptr<PAIFontLoader> fontLoaderSPtr = nullptr;

        PCApplicationState appState;
        int32_t accumulator;
        sf::RenderWindow window;
        PDPathfinderCache aStarCache;
        PDPathfinderCache dStarCache;
        RandomIntegers ri;
        PRDrawablePath drawablePath;
        PADSFMazeGenerator dfsmg;
        PRNodeStateColors colors;
        PRGradientChanger gradChager;

        GraphDimension *dimensionPtr = nullptr;
        PEBindingsContainer bindings;
    };
}

#endif /* D723E2D5_1943_4166_87CC_73F5C9C47544 */
