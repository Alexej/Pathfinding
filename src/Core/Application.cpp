#include "Application.hpp"
#include "Constants.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include "Constants.hpp"
#include "Node.hpp"

using namespace Pathfinding::Datastructures;
using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    
    Application::Application()
    : window(sf::VideoMode( NUMBER_OF_NODES_HORIZONTAL * NODE_SIDE_LENGTH, 
                            NUMBER_OF_NODES_VERTICAL * NODE_SIDE_LENGTH),
                            APPLICATION_TITLE, sf::Style::Titlebar | sf::Style::Close
                            ),
    graph(NUMBER_OF_NODES_VERTICAL, NUMBER_OF_NODES_HORIZONTAL),
    renderer(&appState),
    graphOps(&graph),
    eventManager(&window, &graphOps)
    {
        appState.renderNodeInfo = true;
    }

    void Application::run()
    {
        while (window.isOpen())
        {
            handleInput();
            update();
            draw();
        }
    }

    void Application::handleInput()
    {
        eventManager.pushEvent();
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