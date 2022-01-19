#include "Application.hpp"
#include "Constants.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>



namespace Pathfinding::Core
{
    using namespace Pathfinding::Datastructures;
    using namespace Pathfinding::Constants;
    using std::placeholders::_1;
    namespace
    {
        GraphLocation mapMouseToGraphCoordinates(sf::Vector2i pos, int32_t currentSideLength)
        {
            int32_t faH = pos.y / currentSideLength;
            int32_t faW = pos.x / currentSideLength;
            return {faH, faW};
        }
    }

    Application::Application()
        : appState(N_100),
          window(sf::VideoMode(GRID_FIELD_WIDTH + MENU_WIDTH,
                               GRID_FIELD_HEIGHT),
                 APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close),
          graph(GRID_FIELD_HEIGHT / appState.nodeSideLength, GRID_FIELD_HEIGHT / appState.nodeSideLength),
          eventManager(&window),
          menu(&appState, GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH)
    {
        eventManager.addBinging({false, sf::Event::EventType::MouseButtonPressed, sf::Mouse::Left}, 
        std::bind(&Application::leftMouseButtonPressed, this, std::placeholders::_1));

        eventManager.addBinging({false, sf::Event::EventType::MouseButtonPressed, sf::Mouse::Right},
        std::bind(&Application::rightMouseButtonPressed, this, std::placeholders::_1));

        eventManager.addBinging({true, sf::Event::EventType::MouseButtonReleased, sf::Mouse::Left},
        std::bind(&Application::mouseButtonReleased, this, std::placeholders::_1));

        eventManager.addBinging({true, sf::Event::EventType::MouseMoved, sf::Mouse::Left},
        std::bind(&Application::mouseMoved, this, std::placeholders::_1));

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
        if (appState.numberOfNodesChanged)
        {
            handleNumberOfNodesChange();
        }
        eventManager.processEvents();
    }

    void Application::handleNumberOfNodesChange()
    {
        appState.numberOfNodesChanged = false;
        appState.nodeSideLength = NUMBER_OF_NODES_IN_ROW[appState.numberOfNodeIndex];
        graph.resize(GRID_FIELD_HEIGHT / appState.nodeSideLength, GRID_FIELD_HEIGHT / appState.nodeSideLength);
    }

    void Application::draw()
    {
        window.clear();
        renderer.render(window, graph, appState.nodeSideLength, appState.renderNodeInfo);
        ImGui::SFML::Render(window);
        window.display();
    }

    void Application::leftMouseButtonPressed(sf::Vector2i pos)
    {
        GraphLocation mappedCoordinates = mapMouseToGraphCoordinates(pos, appState.nodeSideLength);
        if (mappedCoordinates == graph.startNode()->location)
        {
            currentMouseAction = MouseAction::SETTING_START;
        }
        else if (mappedCoordinates == graph.goalNode()->location)
        {
            currentMouseAction = MouseAction::SETTING_GOAL;
        }
        else
        {
            currentMouseAction = MouseAction::BLOCKING_NODE;
        }
    }

    void Application::rightMouseButtonPressed(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::CLEARING_NODE;
    }

    void Application::mouseMoved(sf::Vector2i pos)
    {
        GraphLocation mappedCoordinates = mapMouseToGraphCoordinates(pos, appState.nodeSideLength);
        if (!graph.inBounds(mappedCoordinates))
        {
            return;
        }
        switch (currentMouseAction)
        {
        case MouseAction::SETTING_START:
            graph.setStart(mappedCoordinates);
            break;
        case MouseAction::SETTING_GOAL:
            graph.setGoal(mappedCoordinates);
            break;
        case MouseAction::BLOCKING_NODE:
            graph.blockNode(mappedCoordinates);
            break;
        case MouseAction::CLEARING_NODE:
            graph.clearNode(mappedCoordinates);
            break;
        }
    }

    void Application::mouseButtonReleased(sf::Vector2i pos)
    {
        currentMouseAction = MouseAction::IDLE;
    }
}