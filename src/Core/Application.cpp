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
                            graphOps(&graph)
    {
        graphOps.setStart(GraphLocation(0,0));
        graphOps.setGoal(GraphLocation(NUMBER_OF_NODES_VERTICAL-1,NUMBER_OF_NODES_HORIZONTAL-1));
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

    void Application::update()
    {
        while (!events.empty())
        {
            if (events[0].type == sf::Event::EventType::Closed)
            {
                window.close();
            }
            events.pop_front();
        }
    }

    void Application::draw()
    {
        renderer.render(window, graph);
    }

    void Application::handleInput()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            events.push_back(event);
        }
    }
}