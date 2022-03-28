#include "DrawablePath.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ApplicationState.hpp"
#include "RenderingHelpers.hpp"
#include "Constants.hpp"
#include "Node.hpp"

namespace Pathfinding::Rendering
{
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using namespace Pathfinding::Helpers;
    using namespace Pathfinding::Constants;

    void DrawablePath::init(const PCApplicationState * appStatePtr_)
    {
        nodePoint.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        nodePoint.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        diagonalLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        diagonalLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        straightLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        straightLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        appStatePtr = appStatePtr_;

        resize();
    }

    void DrawablePath::setColor(sf::Color color)
    {
        diagonalLine.setFillColor(color);
        straightLine.setFillColor(color);
    }

                        
    void DrawablePath::prepare(const std::vector<Node *> &path, 
                                sf::Color color)
    {
        setColor(color);
        points.clear();
        lines.clear();

        float halfNodeSideLength = static_cast<float>(appStatePtr->dimension.currentNodeSideLength() / 2);
        sf::Vector2f pointPositionOffset = {halfNodeSideLength,halfNodeSideLength};
        if(appStatePtr->showPathPoints)
        {
            createPathPoints(path, pointPositionOffset);
        }

        if(appStatePtr->showPathLines)
        {
            createPathLines(path, pointPositionOffset);
        }
    }

    void DrawablePath::resize()
    {
        float nodeSideLength = static_cast<float>(appStatePtr->dimension.currentNodeSideLength());

        float halfNodeSize = nodeSideLength / 2;

        float nodePointRadius;

        if (appStatePtr->dimension.canShowNodeInfo())
        {
            nodePointRadius = halfNodeSize / 5;
        }
        else
        {
            nodePointRadius = halfNodeSize / 2.5f;
        }

        float halfNodeSizeSquared = static_cast<float>(pow(nodeSideLength / 2, 2));

        float lineThickness = nodePointRadius / 2;
        float diagonalLineLength = 2 * sqrt(halfNodeSizeSquared + halfNodeSizeSquared);

        auto straightLineSize = sf::Vector2f(nodeSideLength, lineThickness);
        auto diagonalLineSize = sf::Vector2f(diagonalLineLength, lineThickness);

        auto origin = sf::Vector2f(0, lineThickness / 2);

        nodePoint.setRadius(nodePointRadius);
        nodePoint.setOrigin(nodePointRadius, nodePointRadius);

        straightLine.setSize(straightLineSize);
        diagonalLine.setSize(diagonalLineSize);

        straightLine.setOrigin(origin);
        diagonalLine.setOrigin(origin);
    }

    void DrawablePath::createPathPoints(const std::vector<Node *> &path, sf::Vector2f pointPositionOffset)
    {
        for (auto &node : path)
        {
            sf::Vector2f leftCornerOfNodePosition = getNodePosition(node, appStatePtr->dimension.currentNodeSideLength());
            sf::Vector2f nodePointPosition = leftCornerOfNodePosition + pointPositionOffset;
            nodePoint.setFillColor(straightLine.getFillColor());
            nodePoint.setPosition(nodePointPosition);
            if (node->state == NodeState::Blocked)
            {
                nodePoint.setFillColor(sf::Color::Red);
            }
            points.push_back(nodePoint);

        }
    }

    void DrawablePath::createPathLines(const std::vector<Node *> &path, sf::Vector2f pointPositionOffset)
    {
        for (auto currentNodeItr = path.begin(); currentNodeItr != path.end(); ++currentNodeItr)
        {
            if (auto nextNode = std::next(currentNodeItr, 1); nextNode != path.end())
            {
                sf::Vector2f centerOfCurrentNode = getNodePosition(*currentNodeItr, 
                appStatePtr->dimension.currentNodeSideLength()) + pointPositionOffset;
                float angle = static_cast<float>(getAngleBetweenTwoNodes(*currentNodeItr, *nextNode));
                if (diagonal(angle))
                {
                    diagonalLine.setPosition(sf::Vector2f(centerOfCurrentNode));
                    diagonalLine.setRotation(angle);
                    lines.push_back(diagonalLine);
                }
                else
                {
                    straightLine.setPosition(sf::Vector2f(centerOfCurrentNode));
                    straightLine.setRotation(angle);
                    lines.push_back(straightLine);
                }
            }
        }
    }


    void DrawablePath::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if(appStatePtr->showPathLines && appStatePtr->showPathPoints)
        {
            drawArrayOfDrawables(target, lines);
        }
        if(appStatePtr->showPathPoints)
        {
            drawArrayOfDrawables(target, points);
        }
    }
}