#include "ApplicationBuilder.hpp"

#include <SFML/Window/Event.hpp>

#include "Constants.hpp"
#include "Application.hpp"
#include "LatticeGraph.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ApplicationState.hpp"
#include "EventManager.hpp"
#include "Menu.hpp"
#include "DStarLite.hpp"
#include "AIncrementalInformedAlgorithm.hpp"
#include "DiagonalHeuristic.hpp"
#include "DefaultCostFunction.hpp"
#include "AStar.hpp"
#include "PathfinderReturnType.hpp"
#include "GraphOperations.hpp"
#include "MouseEvent.hpp"
#include "NodeStateColors.hpp"
#include "Renderer.hpp"
#include "ILatticeGraphHelpers.hpp"
#include "MenuCallBacks.hpp"
#include "SFMLNodeStrategy.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Abstract::AIncrementalInformedAlgorithm;
    using Pathfinding::Abstract::IApplication;
    using Pathfinding::Abstract::IGraphOperations;
    using Pathfinding::Abstract::ILatticeGraph;
    using Pathfinding::Abstract::IFontLoader;
    using Pathfinding::Abstract::IRenderer;
    using Pathfinding::Algorithms::AStar;
    using Pathfinding::Algorithms::DefaultCostFunction;
    using Pathfinding::Algorithms::DiagonalHeuristic;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::LatticeGraphWrapper;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Events::EventManager;
    using Pathfinding::Events::MouseEvent;
    using Pathfinding::Gui::Menu;
    using Pathfinding::Gui::MenuCallBacks;
    using Pathfinding::Rendering::NodeStateColors;
    using Pathfinding::Rendering::Renderer;
    using Pathfinding::Rendering::SFMLNodeStrategy;
    using Pathfinding::Helpers::ILatticeGraphHelpers;
    using sf::Event::EventType::MouseButtonPressed;
    using sf::Event::EventType::MouseButtonReleased;
    using sf::Event::EventType::MouseMoved;
    using sf::Event::EventType::MouseWheelMoved;
    using std::placeholders::_1;

    ApplicationBuilder::ApplicationBuilder()
    {
        applicationUPtr = std::make_unique<Application>();
    }

    void ApplicationBuilder::setDimension(std::initializer_list<int32_t> numberOfNodesInRow)
    {
        dimension = GraphDimension(GRID_FIELD_WIDTH, numberOfNodesInRow);
    }

    void ApplicationBuilder::setCosts(int32_t diagonalCost_, int32_t straightCost_)
    {
        diagonalCost = diagonalCost_;
        straightCost = straightCost_;
    }

    void ApplicationBuilder::setFontLoader(std::shared_ptr<IFontLoader> fontLoaderSPtr_)
    {
        applicationUPtr->fontLoaderSPtr = fontLoaderSPtr_;
    }

    std::unique_ptr<IApplication> ApplicationBuilder::make()
    {
        applicationUPtr->accumulator = 0;
        instantiateObjects();
        initializeObjects();
        lastPreparations();

        /**
         * !implicit upcast!
         */
        return std::move(applicationUPtr);
    }

    void ApplicationBuilder::instantiateObjects()
    {
        std::shared_ptr<ILatticeGraph> latticeGraph = std::make_shared<LatticeGraph>(dimension.width(), dimension.height());
        applicationUPtr->latGraphWrapUPtr = std::make_shared<LatticeGraphWrapper>(latticeGraph);
        applicationUPtr->window.create(sf::VideoMode(APPLICATION_WINDOW_WIDTH, GRID_FIELD_HEIGHT), APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close);
        applicationUPtr->appState = ApplicationState(dimension);
        applicationUPtr->eventManagerUPtr = std::make_unique<EventManager>(&applicationUPtr->window);
        applicationUPtr->menuUPtr = std::make_unique<Menu>(&applicationUPtr->appState, &applicationUPtr->aStarCache, &applicationUPtr->dStarCache);
        applicationUPtr->dstarLiteUPtr = std::make_unique<DStarLite>(applicationUPtr->latGraphWrapUPtr);
        applicationUPtr->graphOpsUPtr = std::make_unique<GraphOperations>(&applicationUPtr->appState, applicationUPtr->latGraphWrapUPtr);
        applicationUPtr->aStarUPtr = std::make_unique<AStar>();
        applicationUPtr->drawablePath.init(&applicationUPtr->appState);
        applicationUPtr->rendererUPtr = std::make_unique<Renderer>();
        applicationUPtr->drawStrategy = std::make_shared<SFMLNodeStrategy>(applicationUPtr->fontLoaderSPtr->getFont("NugoSansLight"), 
                                                                            applicationUPtr->colors, 
                                                                            applicationUPtr->appState,
                                                                            applicationUPtr->window);
    }

    void ApplicationBuilder::initializeObjects()
    {
        createEventManagerBindings();
        setMenuCallBacks();
        initDStarLite();
        initAStar();
    }

    void ApplicationBuilder::lastPreparations()
    {
        applicationUPtr->graphOpsUPtr->addEdgeChangeCallBack(std::bind(&AIncrementalInformedAlgorithm::addChangedNode,
                                                                       applicationUPtr->dstarLiteUPtr.get(), _1));
        applicationUPtr->window.setFramerateLimit(APP_FPS);
        applicationUPtr->dimensionPtr = &applicationUPtr->appState.dimension;
        applicationUPtr->gradChager.init(applicationUPtr->colors);
    }

    void ApplicationBuilder::createEventManagerBindings()
    {
        constexpr sf::Mouse::Button NO_MOUSE_BUTTON = sf::Mouse::Left;

        auto callBack = std::bind(&IGraphOperations::leftMouseButtonPressed, applicationUPtr->graphOpsUPtr.get(), _1);
        auto mouseWheelEvent = MouseEvent(EVENT_AND_KEY, MouseButtonPressed, sf::Mouse::Left);
        applicationUPtr->bindings.addBinding({"LeftMouseButtonPressed" ,mouseWheelEvent, callBack});

        callBack = std::bind(&IGraphOperations::rightMouseButtonPressed, applicationUPtr->graphOpsUPtr.get(), _1);
        mouseWheelEvent = MouseEvent(EVENT_AND_KEY, MouseButtonPressed, sf::Mouse::Right);
        applicationUPtr->bindings.addBinding({"RightMouseButtonPressed" ,mouseWheelEvent, callBack});

        callBack = std::bind(&IGraphOperations::mouseButtonReleased, applicationUPtr->graphOpsUPtr.get(), _1);
        mouseWheelEvent = MouseEvent(EVENT_ONLY, MouseButtonReleased, NO_MOUSE_BUTTON);
        applicationUPtr->bindings.addBinding({"MouseButtonReleased" ,mouseWheelEvent, callBack});

        callBack = std::bind(&IGraphOperations::mouseMoved, applicationUPtr->graphOpsUPtr.get(), _1);
        mouseWheelEvent = MouseEvent(EVENT_ONLY, MouseMoved, NO_MOUSE_BUTTON);
        applicationUPtr->bindings.addBinding({"MouseMoved" ,mouseWheelEvent, callBack});
        
        callBack = std::bind(&IGraphOperations::nodeUnderCursor, applicationUPtr->graphOpsUPtr.get(), _1);
        mouseWheelEvent = MouseEvent(EVENT_ONLY, MouseMoved, NO_MOUSE_BUTTON);
        applicationUPtr->bindings.addBinding({"NodeUnderCursor" ,mouseWheelEvent, callBack});
        
        callBack = std::bind(&IGraphOperations::mouseWheelMoved, applicationUPtr->graphOpsUPtr.get(), _1);
        mouseWheelEvent = MouseEvent(EVENT_ONLY, MouseWheelMoved, NO_MOUSE_BUTTON);
        applicationUPtr->bindings.addBinding({"MouseWheelMoved" ,mouseWheelEvent, callBack});
    }

    void ApplicationBuilder::setMenuCallBacks()
    {
        MenuCallBacks mc;

        mc.numberOfNodesChangedCallBack = std::bind(&Application::handleNumberOfNodesChange, applicationUPtr.get(), _1);
        mc.mouseWheelEventChangedCallBack = std::bind(&Application::mouseWheelEventChanged, applicationUPtr.get(), _1);
        mc.startCallBack = std::bind(&Application::startAlgorithm, applicationUPtr.get());
        mc.randomGraphCallBack = std::bind(&Application::randomGraph, applicationUPtr.get());
        mc.mazeGraphCallBack = std::bind(&Application::generateMaze, applicationUPtr.get());
        mc.resetCallback = std::bind(&Application::reset, applicationUPtr.get());
        mc.stepCallBack = std::bind(&Application::step, applicationUPtr.get());

        applicationUPtr->menuUPtr->addCallbacks(mc);

    }

    void ApplicationBuilder::initAStar()
    {
        applicationUPtr->aStarUPtr->setHeuristic(std::make_unique<DiagonalHeuristic>(diagonalCost, straightCost));
        applicationUPtr->aStarUPtr->setCostFunction(std::make_unique<DefaultCostFunction>(diagonalCost, straightCost));
    }

    void ApplicationBuilder::initDStarLite()
    {
        applicationUPtr->dstarLiteUPtr->addFoundPathCallBack(std::bind(&Application::done, applicationUPtr.get()));
        applicationUPtr->dstarLiteUPtr->addNoPathCallBack(std::bind(&Application::noPath, applicationUPtr.get()));
        applicationUPtr->dstarLiteUPtr->setHeuristic(std::make_unique<DiagonalHeuristic>(diagonalCost, straightCost));
        applicationUPtr->dstarLiteUPtr->setCostFunction(std::make_unique<DefaultCostFunction>(diagonalCost, straightCost));
    }
}
