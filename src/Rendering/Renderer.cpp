#include "Renderer.hpp"

#include <cmath>
#include <numbers>
#include <array>
#include <SFML/Graphics/CircleShape.hpp>

#include "Constants.hpp"
#include "ApplicationState.hpp"
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Constants.hpp"
#include "GraphDimension.hpp"
#include "RootPath.hpp"
#include "ALatGraphWr.hpp"
#include "LatticeGraphHelpers.hpp"
#include "CouldNotLoadFontException.hpp"
#include "ApplicationState.hpp"
#include "RenderingHelpers.hpp"
#include "IFontLoader.hpp"

namespace Pathfinding::Rendering
{
    using namespace Pathfinding::Constants;
    using namespace Pathfinding::Helpers;
    using namespace Pathfinding::Datastructures;
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Abstract::IApplicationState;
    using Pathfinding::Exceptions::CouldNotLoadFontException;
    using Pathfinding::Helpers::LatticeGraphHelpers;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Abstract::IFontLoader;

    Renderer::Renderer(sf::RenderWindow *window, 
                       ApplicationState *appStateSPtr_, 
                       std::shared_ptr<IFontLoader> fontLoaderSPtr_)
        : windowPtr(window), 
        appStateSPtr(appStateSPtr_), 
        dimensionPtr(&appStateSPtr->dimension), 
        fontLoaderSPtr(fontLoaderSPtr_)
    {
        init();
        resize();
        reset();
    }

    void Renderer::init()
    {
        drawableNode.init(fontLoaderSPtr->getFont("NugoSansLight"));

        nodePoint.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        nodePoint.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        diagonalLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        diagonalLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        straightLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        straightLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);
    }

    void Renderer::setPathColor(sf::Color color)
    {
        diagonalLine.setFillColor(color);
        straightLine.setFillColor(color);
    }

    void Renderer::resize()
    {
        float straightLineLength = static_cast<float>(dimensionPtr->currentNodeSideLength());
        float halfNodeSize = straightLineLength / 2;

        float nodePointRadius;

        if (dimensionPtr->canShowNodeInfo())
        {
            nodePointRadius = halfNodeSize / 5;
        }
        else
        {
            nodePointRadius = halfNodeSize / 2.5f;
        }

        nodePoint.setRadius(nodePointRadius);
        nodePoint.setOrigin(nodePointRadius, nodePointRadius);

        float halfNodeSizeSquared = static_cast<float>(pow(straightLineLength / 2, 2));

        float lineThickness = nodePointRadius / 2;
        float diagonalLineLength = 2 * sqrt(halfNodeSizeSquared + halfNodeSizeSquared);

        straightLine.setSize(sf::Vector2f(straightLineLength, lineThickness));
        diagonalLine.setSize(sf::Vector2f(diagonalLineLength, lineThickness));

        straightLine.setOrigin(sf::Vector2f(0, lineThickness / 2));
        diagonalLine.setOrigin(sf::Vector2f(0, lineThickness / 2));

        auto factorRectSize = sf::Vector2f(nodePointRadius * 1.5f ,nodePointRadius * 1.5f);
        auto nodeRectSize = sf::Vector2f(straightLineLength, straightLineLength);

        drawableNode.resize(nodeRectSize, factorRectSize);
    }

    void Renderer::render(const std::shared_ptr<ALatGraphWr> latticeGraphWrapperSPtr)
    {
        if(appStateSPtr->algorithmFinished()) { updateColors(); }
        LatticeGraphHelpers::iterateOverLatticeGraphConst(latticeGraphWrapperSPtr->latGraphSPtr,
        [this](const Node *node, int32_t h, int32_t w)
        {
            auto coords = getNodePosition(node, dimensionPtr->currentNodeSideLength());
            auto color = stateColor(node->state);
            if(node->state == NodeState::Blocked) { color = blockedNodeColorDiff; }
            else if(node->state == NodeState::Goal) { color = goalNodeColorDiff; }
            drawableNode.prepare(*node, coords, color, appStateSPtr->showNodeInfo);
            windowPtr->draw(drawableNode);
        });
    }


    void Renderer::reset()
    {
        goalNodeColorDiff = convertToSfmlColor(GOAL_NODE_COLOR);
        blockedNodeColorDiff = convertToSfmlColor(BLOCKED_NODE_COLOR);
    }

    void Renderer::updateColors()
    {
        if(appStateSPtr->currentState == State::NO_PATH)
        {
            gradients.gradientBlockedRed(blockedNodeColorDiff.r, 5);
            gradients.gradientBlockedBlue(blockedNodeColorDiff.b, 1);
        }
        else if(appStateSPtr->currentState == State::FOUND_PATH)
        {
            gradients.gradientGoalRed(goalNodeColorDiff.r, 5);   
            gradients.gradientGoalGreen(goalNodeColorDiff.g, 1);
        }
    }


    void Renderer::renderPath(const std::vector<Node *> &path, sf::Color color)
    {
        setPathColor(color);

        sf::Vector2f pointPositionOffset(dimensionPtr->currentNodeSideLength() / 2.f, dimensionPtr->currentNodeSideLength() / 2.f);

        if (appStateSPtr->showPathLines && appStateSPtr->showPath)
        {
            renderPathLines(path, pointPositionOffset);
        }
        if (appStateSPtr->showPath)
        {
            renderPathLineEndPoints(path, pointPositionOffset, color);
        }
    }

    void Renderer::renderPathLineEndPoints(const std::vector<Node *> &path, sf::Vector2f pointPositionOffset, sf::Color color)
    {
        for (auto &node : path)
        {
            sf::Vector2f leftCornerOfNodePosition = getNodePosition(node, dimensionPtr->currentNodeSideLength());
            sf::Vector2f nodePointPosition = leftCornerOfNodePosition + pointPositionOffset;
            nodePoint.setFillColor(color);
            nodePoint.setPosition(nodePointPosition);
            if (node->state != NodeState::Blocked)
            {
                windowPtr->draw(nodePoint);
            }
            else
            {
                nodePoint.setFillColor(sf::Color::Red);
                windowPtr->draw(nodePoint);
            }
        }
    }

    void Renderer::renderPathLines(const std::vector<Node *> &path, sf::Vector2f pointPositionOffset)
    {
        for (auto currentNodeItr = path.begin(); currentNodeItr != path.end(); ++currentNodeItr)
        {
            if (auto nextNode = std::next(currentNodeItr, 1); nextNode != path.end())
            {
                sf::Vector2f centerOfCurrentNode = getNodePosition(*currentNodeItr, dimensionPtr->currentNodeSideLength()) + pointPositionOffset;
                float angle = static_cast<float>(getAngleBetweenTwoNodes(*currentNodeItr, *nextNode));
                if (diagonal(angle))
                {
                    diagonalLine.setPosition(sf::Vector2f(centerOfCurrentNode));
                    diagonalLine.setRotation(angle);
                    windowPtr->draw(diagonalLine);
                }
                else
                {
                    straightLine.setPosition(sf::Vector2f(centerOfCurrentNode));
                    straightLine.setRotation(angle);
                    windowPtr->draw(straightLine);
                }
            }
        }
    }
}
