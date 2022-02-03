#include "Application.hpp"
#include "Constants.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"
#include "Vector2.hpp"
#include <imgui-SFML.h>
#include <imgui.h>
#include "DiagonalHeuristic.hpp"
#include "SFMLHelpers.hpp"

#include <iostream>

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Algorithms::DiagonalHeuristic;
    using Pathfinding::Datastructures::Vector2i;
    using Pathfinding::Helpers::mapMouseToGraphCoordinates;

    void Application::init()
    {
        dimension = &appState.dimension();
        window.create(sf::VideoMode(APPLICATION_WINDOW_WIDTH, GRID_FIELD_HEIGHT), APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close);
        graph = LatticeGraph(dimension->width(), dimension->height());
        eventManager = EventManager(&window);
        menu = Menu(&appState, GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH);
        dstar = DStarLite(&graph);
        graphOps = GraphOperations(&appState, &dstar, &graph, dimension->currentNodeSideLength());

        window.setFramerateLimit(60);
    }

    Application::Application()
    {
        init();

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
        menu.addResetCallBack(std::bind(&Application::reset, this));
        menu.addStepCallBack(std::bind(&DStarLite::moveStart, &dstar));

        dstar.addDoneCallBack(std::bind(&Application::done, this));
        dstar.setHeuristic(std::make_shared<DiagonalHeuristic>());
    }

    void Application::startAlgorithm()
    {
        dstar.initialize();
        dstar.computeShortestPath();
        dstar.computePath();
        dstar.setPathInGraph();
        appState.setState(State::SEARCHING);
        graphOps.disableEndpointsEvent();
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
        ImGui::SFML::Update(window, deltaClock.restart());
        eventManager.processEvents();
    }

    void Application::handleNumberOfNodesChange(int32_t index)
    {
        dimension->setCurrentNumberOfNodesIndex(index);
        reset();
    }

    void Application::draw()
    {
        window.clear();
        ImGui::SFML::Render(window);
        renderer.render(window, graph, appState);
        window.display();
    }

    void Application::reset()
    {
        graph.resize(dimension->height(), dimension->width());
        graphOps.resize(dimension->currentNodeSideLength());
        dstar.reset();
        appState.setState(State::READY);
        graphOps.enableEndPointsEvent();
        graphOps.enableObsticlesEvents();
        appState.setNodeUnderCursor(nullptr);
    }

    void Application::done()
    {
        graphOps.disableObsticlesEvents();
        appState.setState(State::DONE);
    }
}