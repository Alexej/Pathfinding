#include "Application.hpp"
#include "Constants.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"
#include "Vector2.hpp"
#include <imgui-SFML.h>
#include <imgui.h>
#include "EuclidianHeuristic.hpp"

#include <iostream>

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Datastructures::Vector2i;
    using Pathfinding::Algorithms::EuclidianHeuristic;

    namespace
    {
        Vector2i mapMouseToGraphCoordinates(sf::Vector2i pos, int32_t currentSideLength)
        {
            int32_t faH = pos.y / currentSideLength;
            int32_t faW = pos.x / currentSideLength;
            return {faH, faW};
        }
    }

    void Application::init()
    {
        dimension = &appState.dimension();
        window.create(sf::VideoMode(APPLICATION_WINDOW_WIDTH, GRID_FIELD_HEIGHT), APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close);
        graph = LatticeGraph(dimension->width(), dimension->height());
        eventManager = EventManager(&window);
        menu = Menu(&appState, GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH);
        dstar = DStarLite(&graph);
        graphOps = GraphOperations(&graph, dimension->currentNodeSideLength());
    }

    Application::Application()
    {
        init();

        using sf::Event::EventType::MouseButtonPressed;
        using sf::Event::EventType::MouseButtonReleased;
        using sf::Event::EventType::MouseMoved;
        using std::placeholders::_1;

        eventManager.addBinging({false, MouseButtonPressed, sf::Mouse::Left}, std::bind(&GraphOperations::leftMouseButtonPressed, &graphOps, _1));
        eventManager.addBinging({false, MouseButtonPressed, sf::Mouse::Right}, std::bind(&GraphOperations::rightMouseButtonPressed, &graphOps, _1));
        eventManager.addBinging({true, MouseButtonReleased, sf::Mouse::Left}, std::bind(&GraphOperations::mouseButtonReleased, &graphOps, _1));
        eventManager.addBinging({true, MouseMoved, sf::Mouse::Left}, std::bind(&GraphOperations::mouseMoved, &graphOps, _1));

        menu.addNumberOfNodesChangedCallback(std::bind(&Application::handleNumberOfNodesChange, this, _1));
        dstar.setHeuristic(std::make_shared<EuclidianHeuristic>());
        dstar.initialize();
        dstar.computeShortestPath();
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
        graph.resize(dimension->height(), dimension->width());
        graphOps.resize(dimension->currentNodeSideLength());
    }

    void Application::draw()
    {
        window.clear();
        ImGui::SFML::Render(window);
        renderer.render(window, graph, appState);
        window.display();
    }
}