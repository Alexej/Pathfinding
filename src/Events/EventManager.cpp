#include "EventManager.hpp"

#include <SFML/Window/Event.hpp>

#include "MouseData.hpp"

namespace Pathfinding::Events
{
    EventManager::EventManager(sf::RenderWindow *window)
        : windowPtr(window)
    {
    }

    void EventManager::addBinding(Binding binding)
    {
        bindings.push_back(binding);
    }

    void EventManager::pushEvent(sf::Event event)
    {
        if (event.type == sf::Event::EventType::Closed)
        {
            windowPtr->close();
        }
        eventQueue.push_back(event);
    }

    void EventManager::processEvents()
    {
        while (!eventQueue.empty())
        {
            sf::Event &currentEvent = eventQueue[0];
            sf::Vector2i mousePos = sf::Mouse::getPosition(*windowPtr);
            for (auto &currentBinding : bindings)
            {
                if (currentEvent.type == currentBinding.mouseEvent.event)
                {
                    if (currentBinding.mouseEvent.eventOnly || 
                        currentEvent.key.code == currentBinding.mouseEvent.button)
                    {
                        currentBinding.callback(MouseData(mousePos, currentEvent.mouseWheel.delta));
                    }
                }
            }
            eventQueue.pop_front();
        }
    }
}
