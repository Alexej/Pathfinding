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
    using namespace Pathfinding::Constants;

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
        : window(sf::VideoMode(GRID_FIELD_WIDTH + MENU_WIDTH, GRID_FIELD_HEIGHT),
                 APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close),
          graph(GRID_FIELD_HEIGHT / appState.dim.currentNodeSideLength(), GRID_FIELD_HEIGHT / appState.dim.currentNodeSideLength()),
          eventManager(&window),
          menu(&appState, GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH),
          dstar(&graph),
          graphOps(&graph, appState.dim.currentNodeSideLength())
    {

        using std::placeholders::_1;
        using sf::Event::EventType::MouseButtonPressed;
        using sf::Event::EventType::MouseButtonReleased;
        using sf::Event::EventType::MouseMoved;
    
        eventManager.addBinging({false, MouseButtonPressed, sf::Mouse::Left}, std::bind(&GraphOperations::leftMouseButtonPressed, &graphOps, _1));
        eventManager.addBinging({false, MouseButtonPressed, sf::Mouse::Right}, std::bind(&GraphOperations::rightMouseButtonPressed, &graphOps, _1));
        eventManager.addBinging({true, MouseButtonReleased, sf::Mouse::Left}, std::bind(&GraphOperations::mouseButtonReleased, &graphOps, _1));
        eventManager.addBinging({true, MouseMoved, sf::Mouse::Left}, std::bind(&GraphOperations::mouseMoved, &graphOps, _1));
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
        graph.resize(GRID_FIELD_HEIGHT / appState.dim.currentNodeSideLength(), GRID_FIELD_HEIGHT / appState.dim.currentNodeSideLength());
        graphOps.resize(appState.dim.currentNodeSideLength());
    }

    void Application::draw()
    {
        window.clear();
        renderer.render(window, graph, appState);
        ImGui::SFML::Render(window);
        window.display();
    }
}