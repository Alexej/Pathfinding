#include "EventManager.hpp"
#include "LatticeGraphOperations.hpp"
#include "Constants.hpp"
#include <iostream>

using Pathfinding::Constants::NODE_SIDE_LENGTH;

namespace Pathfinding::Core
{
    EventManager::EventManager(sf::RenderWindow * window, LatticeGraphOperations * graphOps)
    : windowPtr(window), graphOpsPtr(graphOps) {}

    void EventManager::pushEvent(sf::Event event)
    {
        eventQueue.push_back(event);
    }

    GraphLocation EventManager::mapMouseToGraphCoordinates(sf::Vector2i pos)
    {
        int32_t faH = pos.y / NODE_SIDE_LENGTH;
        int32_t faW = pos.x / NODE_SIDE_LENGTH;
        return {faH,faW};
    }

    void EventManager::processEvents()
    {
        while(!eventQueue.empty())
        {
            sf::Vector2i mouseCoordinates = sf::Mouse::getPosition(*windowPtr);
            GraphLocation mappedCoordinates = mapMouseToGraphCoordinates(mouseCoordinates);
            auto & currentEvent = eventQueue[0];
            if(currentEvent.type == sf::Event::EventType::MouseButtonPressed)
            {
                if(currentEvent.key.code == sf::Mouse::Left)
                {
                    if(mappedCoordinates == graphOpsPtr->startLocation())
                    {
                        settingStart = true;
                    }
                    else if(mappedCoordinates == graphOpsPtr->goalLocation())
                    {
                        settingGoal = true;
                    }
                    else
                    {
                        settingWall = true;
                    }
                }
                else if(currentEvent.key.code == sf::Mouse::Right)
                {
                    clearingWall = true;
                }
            }
            else if(currentEvent.type == sf::Event::EventType::MouseMoved)
            {
                if(graphOpsPtr->inBounds(mappedCoordinates))
                {
                    if(settingStart)
                    {
                        graphOpsPtr->setStart(mappedCoordinates);
                    }
                    else if(settingGoal)
                    {
                        graphOpsPtr->setGoal(mappedCoordinates);
                    }
                    else if(settingWall)
                    {
                        graphOpsPtr->blockNode(mappedCoordinates);
                    }
                    else if(clearingWall)
                    {
                        graphOpsPtr->clearNode(mappedCoordinates);
                    }
                }
            }
            else if(currentEvent.type == sf::Event::EventType::MouseButtonReleased)
            {
                settingWall = false;
                clearingWall = false;
                settingStart = false;
                settingGoal = false;
            }
            eventQueue.pop_front();
        }
    }
}
