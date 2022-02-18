#include "Application.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include "Constants.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"
#include "DiagonalHeuristic.hpp"
#include "SFMLHelpers.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"
#include <iostream>
#include "IDStarLite.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Algorithms::DiagonalHeuristic;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Events::EventManager;
    using Pathfinding::Gui::Menu;
    using Pathfinding::Helpers::GraphOperations;
    using Pathfinding::Abstract::IDStarLite;

    void Application::createObbjects()
    {
        AlgorithmStepSpeed stepSpeed({100,200,400,800,1600,0});
        GraphDimension dimension(GRID_FIELD_WIDTH, {8, 10, 20, 25, 40, 80});
        appState = ApplicationState(dimension, stepSpeed);
        graph = LatticeGraph(dimension.width(), dimension.height());
        window.create(sf::VideoMode(APPLICATION_WINDOW_WIDTH, GRID_FIELD_HEIGHT), APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close);

        eventManagerUPtr = std::make_unique<EventManager>(&window);
        menuUPtr = std::make_unique<Menu>(&appState, GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH);
        dstarLiteUPtr = std::make_unique<DStarLite>(&graph);
        graphOpsUPtr = std::make_unique<GraphOperations>(&appState, &graph);
        rendererUPtr = std::make_unique<Renderer>(&window, &appState);
    }

    Application::Application()
    {
        accumulator = 0;

        createObbjects();

        using sf::Event::EventType::MouseButtonPressed;
        using sf::Event::EventType::MouseButtonReleased;
        using sf::Event::EventType::MouseMoved;
        using std::placeholders::_1;

        eventManagerUPtr->addBinding({EVENT_AND_KEY, MouseButtonPressed, sf::Mouse::Left}, std::bind(&GraphOperations::leftMouseButtonPressed, graphOpsUPtr.get(), _1));
        eventManagerUPtr->addBinding({EVENT_AND_KEY, MouseButtonPressed, sf::Mouse::Right}, std::bind(&GraphOperations::rightMouseButtonPressed, graphOpsUPtr.get(), _1));
        eventManagerUPtr->addBinding({EVENT_ONLY, MouseButtonReleased, NO_MOUSE_BUTTON}, std::bind(&GraphOperations::mouseButtonReleased, graphOpsUPtr.get(), _1));
        eventManagerUPtr->addBinding({EVENT_ONLY, MouseMoved, NO_MOUSE_BUTTON}, std::bind(&GraphOperations::mouseMoved, graphOpsUPtr.get(), _1));
        eventManagerUPtr->addBinding({EVENT_ONLY, MouseMoved, NO_MOUSE_BUTTON}, std::bind(&GraphOperations::nodeUnderCursor, graphOpsUPtr.get(), _1));

        menuUPtr->addNumberOfNodesChangedCallBack(std::bind(&Application::handleNumberOfNodesChange, this, _1));
        menuUPtr->addStartCallBack(std::bind(&Application::startAlgorithm, this));
        menuUPtr->addRandomGraphCallBack(std::bind(&Application::randomGraph, this));
        menuUPtr->addResetCallBack(std::bind(&Application::reset, this));
        menuUPtr->addStepCallBack(std::bind(&Application::step, this));

        dstarLiteUPtr->addDoneCallBack(std::bind(&Application::done, this));
        dstarLiteUPtr->addNoPathCallBack(std::bind(&Application::noPath, this));
        dstarLiteUPtr->setHeuristic(std::make_shared<DiagonalHeuristic>());

        graphOpsUPtr->addEdgeChangeCallBack(std::bind(&IDStarLite::addChangedNode, dstarLiteUPtr.get(), _1));

        window.setFramerateLimit(60);
        dimensionPtr = &appState.dimension();
        algoStepSpeedPtr = &appState.algorithmStepSpeed();
    }

    void Application::startAlgorithm()
    {
        graphOpsUPtr->disableEndpointsEvent();
        appState.setState(State::SEARCHING);

        dstarLiteUPtr->initialize();
        dstarLiteUPtr->initialRun();
    }

    void Application::run()
    {
        ImGui::SFML::Init(window);
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                handleInput(event);
            }
            update(deltaClock);
            menuUPtr->show();
            draw();
        }
        ImGui::SFML::Shutdown();
    }

    void Application::handleInput(sf::Event event)
    {
        ImGui::SFML::ProcessEvent(event);
        eventManagerUPtr->pushEvent(event);
    }

    void Application::update(sf::Clock &deltaClock)
    {
        int32_t dt = deltaClock.getElapsedTime().asMilliseconds();
        rendererUPtr->update();
        if (appState.currentState() == State::SEARCHING && appState.autoStep())
        {
            accumulator += dt;
            if (accumulator > algoStepSpeedPtr->getCurrentStepSpeed())
            {
                dstarLiteUPtr->moveStart();
                accumulator = 0;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        eventManagerUPtr->processEvents();
    }

    void Application::handleNumberOfNodesChange(int32_t index)
    {
        dimensionPtr->setCurrentNumberOfNodesIndex(index);
        reset();
    }

    void Application::draw()
    {
        window.clear();
        ImGui::SFML::Render(window);
        rendererUPtr->render(graph);

        if (appState.currentState() == State::DONE || appState.currentState() == State::SEARCHING)
        {
            rendererUPtr->renderPath(dstarLiteUPtr->path());
        }

        window.display();
    }

    void Application::reset()
    {
        graph.resize(dimensionPtr->height(), dimensionPtr->width());
        graphOpsUPtr->resize(dimensionPtr->currentNodeSideLength());
        dstarLiteUPtr->reset();
        appState.setState(State::READY);
        graphOpsUPtr->enableEndPointsEvent();
        graphOpsUPtr->enableObsticlesEvents();
        appState.setNodeUnderCursor(nullptr);
        rendererUPtr->reset();
    }

    void Application::done()
    {
        graphOpsUPtr->disableObsticlesEvents();
        appState.setState(State::DONE);
    }

    void Application::noPath()
    {
        graphOpsUPtr->disableObsticlesEvents();
        appState.setState(State::NO_PATH);
    }

    void Application::randomGraph()
    {
        reset();
        initRandomGraph(graph);
    }

    void Application::step()
    {
        dstarLiteUPtr->moveStart();
    }
}
