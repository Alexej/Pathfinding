#include "Application.hpp"
#include "Constants.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

using namespace Pathfinding::Datastructures;
using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    
    Application::Application()
    : window(sf::VideoMode( NUMBER_OF_NODES_HORIZONTAL * NODE_SIDE_LENGTH + MENU_WIDTH, 
                            NUMBER_OF_NODES_VERTICAL * NODE_SIDE_LENGTH),
                            APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close
                            ),
    graph(NUMBER_OF_NODES_VERTICAL, NUMBER_OF_NODES_HORIZONTAL),
    renderer(&appState),
    graphOps(&graph),
    eventManager(&window, &graphOps),
    menu(&appState,NUMBER_OF_NODES_HORIZONTAL * NODE_SIDE_LENGTH, NUMBER_OF_NODES_VERTICAL * NODE_SIDE_LENGTH, MENU_WIDTH)
    {
        appState.renderNodeInfo = true;
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
        eventManager.processEvents();
    }

    void Application::draw()
    {
        renderer.render(window, graph);
    }
}