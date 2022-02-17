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

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Algorithms::DiagonalHeuristic;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Events::EventManager;
    using Pathfinding::Gui::Menu;
    using Pathfinding::Helpers::GraphOperations;

    void Application::createObbjects()
    {
        dimensionPtr = &appState.dimension();
        algoStepSpeedPtr = &appState.algorithmStepSpeed();
        window.create(sf::VideoMode(APPLICATION_WINDOW_WIDTH, GRID_FIELD_HEIGHT), APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close);
        graph = LatticeGraph(dimensionPtr->width(), dimensionPtr->height());
        eventManager = EventManager(&window);
        menu = Menu(&appState, GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH);
        dstar = DStarLite(&graph);
        graphOps = GraphOperations(&appState, &dstar, &graph, dimensionPtr->currentNodeSideLength());
        renderer = Renderer(&window, &appState);

        AlgorithmStepSpeed stepSpeed({100,200,400,800,1600,0});
        appState.setAlgorithmStepSpeed(stepSpeed);
    }

    Application::Application()
    {
        accumulator = 0;

        createObbjects();

        using sf::Event::EventType::MouseButtonPressed;
        using sf::Event::EventType::MouseButtonReleased;
        using sf::Event::EventType::MouseMoved;
        using std::placeholders::_1;

        eventManager.addBinding({EVENT_AND_KEY, MouseButtonPressed, sf::Mouse::Left}, std::bind(&GraphOperations::leftMouseButtonPressed, &graphOps, _1));
        eventManager.addBinding({EVENT_AND_KEY, MouseButtonPressed, sf::Mouse::Right}, std::bind(&GraphOperations::rightMouseButtonPressed, &graphOps, _1));
        eventManager.addBinding({EVENT_ONLY, MouseButtonReleased, NO_MOUSE_BUTTON}, std::bind(&GraphOperations::mouseButtonReleased, &graphOps, _1));
        eventManager.addBinding({EVENT_ONLY, MouseMoved, NO_MOUSE_BUTTON}, std::bind(&GraphOperations::mouseMoved, &graphOps, _1));
        eventManager.addBinding({EVENT_ONLY, MouseMoved, NO_MOUSE_BUTTON}, std::bind(&GraphOperations::nodeUnderCursor, &graphOps, _1));

        menu.addNumberOfNodesChangedCallBack(std::bind(&Application::handleNumberOfNodesChange, this, _1));
        menu.addStartCallBack(std::bind(&Application::startAlgorithm, this));
        menu.addRandomGraphCallBack(std::bind(&Application::randomGraph, this));
        menu.addResetCallBack(std::bind(&Application::reset, this));
        menu.addStepCallBack(std::bind(&DStarLite::moveStart, &dstar));

        dstar.addDoneCallBack(std::bind(&Application::done, this));
        dstar.addNoPathCallBack(std::bind(&Application::noPath, this));
        dstar.setHeuristic(std::make_shared<DiagonalHeuristic>());

        window.setFramerateLimit(60);
        renderer.init();
    }

    void Application::startAlgorithm()
    {
        graphOps.disableEndpointsEvent();
        appState.setState(State::SEARCHING);

        dstar.initialize();
        dstar.initialRun();
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
            menu.show();
            draw();
        }
        ImGui::SFML::Shutdown();
    }

    void Application::handleInput(sf::Event event)
    {
        ImGui::SFML::ProcessEvent(event);
        eventManager.pushEvent(event);
    }

    void Application::update(sf::Clock &deltaClock)
    {
        int32_t dt = deltaClock.getElapsedTime().asMilliseconds();
        renderer.update();
        if (appState.currentState() == State::SEARCHING && appState.autoStep())
        {
            accumulator += dt;
            if (accumulator > algoStepSpeedPtr->getCurrentStepSpeed())
            {
                dstar.moveStart();
                accumulator = 0;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        eventManager.processEvents();
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
        renderer.render(graph);

        if (appState.currentState() == State::DONE || appState.currentState() == State::SEARCHING)
        {
            renderer.renderPath(dstar.path());
        }

        window.display();
    }

    void Application::reset()
    {
        graph.resize(dimensionPtr->height(), dimensionPtr->width());
        graphOps.resize(dimensionPtr->currentNodeSideLength());
        dstar.reset();
        appState.setState(State::READY);
        graphOps.enableEndPointsEvent();
        graphOps.enableObsticlesEvents();
        appState.setNodeUnderCursor(nullptr);
        renderer.reset();
    }

    void Application::done()
    {
        graphOps.disableObsticlesEvents();
        appState.setState(State::DONE);
    }

    void Application::noPath()
    {
        graphOps.disableObsticlesEvents();
        appState.setState(State::NO_PATH);
    }

    void Application::randomGraph()
    {
        reset();
        initRandomGraph(graph);
    }
}