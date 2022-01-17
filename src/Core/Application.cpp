#include "Application.hpp"
#include "Constants.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
using namespace std;

using namespace Pathfinding::Datastructures;
using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    
    Application::Application()
    : window(sf::VideoMode( GRID_FIELD_WIDTH + MENU_WIDTH, 
                            GRID_FIELD_HEIGHT),
                            APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close
                            ),
    renderer(&appState),
    graph(GRID_FIELD_HEIGHT / appState.currentNodeSideLength, GRID_FIELD_HEIGHT / appState.currentNodeSideLength),
    graphOps(&graph),
    eventManager(&appState, &window, &graphOps),
    menu(&appState,GRID_FIELD_WIDTH, GRID_FIELD_HEIGHT, MENU_WIDTH)
    {
    }

    void Application::run()
    {
        ImGui::SFML::Init(window);
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event;
            while(window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);
                handleInput(event);
            }
            update();
            ImGui::SFML::Update(window, deltaClock.restart());
            menu.show();
            window.clear();
            draw();
            ImGui::SFML::Render(window);
            window.display();
        }
        ImGui::SFML::Shutdown();
    }

    void Application::handleInput(sf::Event event)
    {
        if(event.type == sf::Event::EventType::Closed)
        {
            window.close();
        }
        else
        {
            eventManager.pushEvent(event);
        }
    }

    void Application::update()
    {
        if(appState.numberOfNodesChanged)
        {
            handleNumberOfNodesChange();
        }
        eventManager.processEvents();
    }

    void Application::handleNumberOfNodesChange()
    {
        appState.numberOfNodesChanged = false;
        appState.currentNodeSideLength = NUMBER_OF_NODES_IN_ROW[appState.currentNumberOfNodeIndex];
        graph.resize(GRID_FIELD_HEIGHT / appState.currentNodeSideLength, GRID_FIELD_HEIGHT / appState.currentNodeSideLength);
        graphOps.resize();
    }

    void Application::draw()
    {
        renderer.render(window, &graph);
    }
}