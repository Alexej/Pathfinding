#include "EventManager.hpp"

#include <SFML/Window/Event.hpp>

#include "MouseData.hpp"
#include "BindingsContainer.hpp"

namespace Pathfinding::Events
{
    EventManager::EventManager(sf::RenderWindow *window)
        : windowPtr(window)
    {
    }


    void EventManager::pushEvent(sf::Event event)
    {
        eventQueue.push_back(event);
    }

    void EventManager::processEvents(const BindingsContainer & bindings)
    {
        while (!eventQueue.empty())
        {
            sf::Event &currentEvent = eventQueue[0];
            if (currentEvent.type == sf::Event::EventType::Closed)
            {
                windowPtr->close();
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(*windowPtr);
            for (const auto & currentBinding : bindings)
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
