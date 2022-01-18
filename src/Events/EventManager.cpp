#include "EventManager.hpp"
#include <SFML/Window/Event.hpp>

namespace Pathfinding::Events
{
    EventManager::EventManager(sf::RenderWindow * window)
    : windowPtr(window)
    {}

    void EventManager::addBinging(MouseEvent event, std::function< void(sf::Vector2i)> callback)
    {
        callBacks.push_back({event, callback});
    }

    void EventManager::pushEvent(sf::Event event)
    {
        if(event.type == sf::Event::EventType::Closed)
        {
            windowPtr->close();
        }
        eventQueue.push_back(event);
    }

    void EventManager::processEvents()
    {
        while(!eventQueue.empty())
        {
            sf::Event & currentEvent = eventQueue[0];
            sf::Vector2i mousePos = sf::Mouse::getPosition(*windowPtr);
            for(auto & callBack : callBacks)
            {
                if(currentEvent.type == callBack.first.event)
                {
                    if(callBack.first.eventOnly || currentEvent.key.code == callBack.first.button)
                    {
                        callBack.second(mousePos);
                    }
                }
            }
            eventQueue.pop_front();
        }
    }
}
