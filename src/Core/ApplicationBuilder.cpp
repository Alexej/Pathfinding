#include "ApplicationBuilder.hpp"

#include <SFML/Window/Event.hpp>

#include "IApplication.hpp"
#include "Constants.hpp"
#include "Application.hpp"
#include "ILatticeGraph.hpp"
#include "LatticeGraph.hpp"
#include "LatticeGraphWrapper.hpp"
#include "ApplicationState.hpp"
#include "EventManager.hpp"
#include "Menu.hpp"
#include "DStarLite.hpp"
#include "AIncrementalInformedAlgorithm.hpp"
#include "Renderer.hpp"
#include "DiagonalHeuristic.hpp"
#include "DefaultCostFunction.hpp"
#include "IGraphOperations.hpp"
#include "ApplicationState.hpp"
#include "AStar.hpp"
#include "PathfinderReturnType.hpp"
#include "GraphOperations.hpp"
#include "MouseEvent.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Abstract::AIncrementalInformedAlgorithm;
    using Pathfinding::Abstract::IApplication;
    using Pathfinding::Abstract::IGraphOperations;
    using Pathfinding::Abstract::ILatticeGraph;
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
    using Pathfinding::Rendering::Renderer;
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

    void ApplicationBuilder::setFontLoader(std::shared_ptr<PAIFontLoader> fontLoaderSPtr_)
    {
        fontLoaderSPtr = fontLoaderSPtr_;
    }

    std::unique_ptr<IApplication> ApplicationBuilder::make()
    {
        applicationUPtr->accumulator = 0;
        instantiateObjects();
        initializeObjects();

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
        applicationUPtr->rendererUPtr = std::make_unique<Renderer>(&applicationUPtr->window, &applicationUPtr->appState, fontLoaderSPtr);
        applicationUPtr->aStarUPtr = std::make_unique<AStar>();
        applicationUPtr->drawablePath.init(&applicationUPtr->appState);

    }

    void ApplicationBuilder::initializeObjects()
    {
        createEventManagerBindings();
        setMenuCallBacks();
        initDStarLite();
        initAStar();

        applicationUPtr->graphOpsUPtr->addEdgeChangeCallBack(std::bind(&AIncrementalInformedAlgorithm::addChangedNode,
                                                                       applicationUPtr->dstarLiteUPtr.get(), _1));
        applicationUPtr->window.setFramerateLimit(APP_FPS);
        applicationUPtr->dimensionPtr = &applicationUPtr->appState.dimension;
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

        auto callBackApp = std::bind(&Application::mouseWheelMoved, applicationUPtr.get(), _1);
        mouseWheelEvent = MouseEvent(EVENT_ONLY, MouseWheelMoved, NO_MOUSE_BUTTON);
        applicationUPtr->bindings.addBinding({"MouseWheelMovedZoom" ,mouseWheelEvent, callBackApp});
    }

    void ApplicationBuilder::setMenuCallBacks()
    {
        applicationUPtr->menuUPtr->addNumberOfNodesChangedCallBack(std::bind(&Application::handleNumberOfNodesChange, applicationUPtr.get(), _1));
        applicationUPtr->menuUPtr->addMouseWheelEventChangedCallBack(std::bind(&Application::mouseWheelEventChanged, applicationUPtr.get(), _1));
        applicationUPtr->menuUPtr->addStartCallBack(std::bind(&Application::startAlgorithm, applicationUPtr.get()));
        applicationUPtr->menuUPtr->addRandomGraphCallBack(std::bind(&Application::randomGraph, applicationUPtr.get()));
        applicationUPtr->menuUPtr->addMazeGraphCallBack(std::bind(&Application::generateMaze, applicationUPtr.get()));
        applicationUPtr->menuUPtr->addResetCallBack(std::bind(&Application::reset, applicationUPtr.get()));
        applicationUPtr->menuUPtr->addStepCallBack(std::bind(&Application::step, applicationUPtr.get()));
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
