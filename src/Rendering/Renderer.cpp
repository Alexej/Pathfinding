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
#include "ALatticeGraphWrapper.hpp"
#include "ALatGrWrHelpers.hpp"
#include "CouldNotLoadFontException.hpp"
#include "ApplicationState.hpp"
#include "RenderingHelpers.hpp"

namespace Pathfinding::Rendering
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Abstract::ALatticeGraphWrapper;
    using Pathfinding::Abstract::IApplicationState;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Exceptions::CouldNotLoadFontException;
    using Pathfinding::Helpers::ALatGrWrHelpers;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Helpers::getRootPath;
    using Pathfinding::Helpers::convertToSfmlColor;

    namespace
    {
        sf::Vector2f getNodePosition(const Node *node, int32_t sideLength)
        {
            float nodesHorF = static_cast<float>(node->location.width);
            float nodesVertF = static_cast<float>(node->location.height);
            float sideLengthF = static_cast<float>(sideLength);
            float positionHor = nodesHorF * sideLengthF;
            float positionVer = nodesVertF * sideLengthF;
            return {positionHor, positionVer};
        }


        /**
         * @brief converts double to string and removes zeros and dot.
         * under the assumption  rhs, g and key values are always integers.
         * @param d
         * @return std::string
         */
        std::string dToStr(double d)
        {
            std::string dStr = std::to_string(d);
            return dStr.substr(0, dStr.find("."));
        }

        double getAngleBetweenTwoNodes(Node *n1, Node *n2)
        {
            float y1 = static_cast<float>(n1->location.height);
            float x1 = static_cast<float>(n1->location.width);
            float y2 = static_cast<float>(n2->location.height);
            float x2 = static_cast<float>(n2->location.width);
            return std::atan2(y2 - y1, x2 - x1) * (180.0 / std::numbers::pi);
        }

        bool diagonal(double angle)
        {
            return std::abs(angle) == 45 || std::abs(angle) == 135;
        }
    }

    Renderer::Renderer(sf::RenderWindow *window, ApplicationState *appStateSPtr_)
        : windowPtr(window), appStateSPtr(appStateSPtr_), dimensionPtr(&appStateSPtr->dimension)
    {
        init();
    }

    void Renderer::init()
    {
        loadFont("NugoSansLight.ttf");

        text.setFont(font);
        text.setStyle(sf::Text::Bold);

        nodeRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        nodeRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));

        factorRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        factorRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));

        text.setCharacterSize(NODE_INFO_TEXT_SIZE);
        text.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));

        nodePoint.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        nodePoint.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        diagonalLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        diagonalLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        straightLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        straightLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        resize();
        reset();
    }

    void Renderer::setPathColor(sf::Color color)
    {
        diagonalLine.setFillColor(color);
        straightLine.setFillColor(color);
    }

    void Renderer::loadFont(std::string fontName)
    {
        if (!font.loadFromFile(getRootPath() + "\\dependencies\\fonts\\" + fontName))
        {
            throw CouldNotLoadFontException("Could not load font");
        }
    }

    sf::Color Renderer::stateColor(NodeState state)
    {
        sf::Color color;
        switch (state)
        {
        case NodeState::Free:
            color = convertToSfmlColor(FREE_NODE_COLOR);
            break;
        case NodeState::Blocked:
            color = convertToSfmlColor(BLOCKED_NODE_COLOR);
            break;
        case NodeState::Frontier:
            color = convertToSfmlColor(FRONTIER_NODE_COLOR);
            break;
        case NodeState::Visited:
            color = visitedColor;
            break;
        case NodeState::Start:
            color = convertToSfmlColor(START_NODE_COLOR);
            break;
        case NodeState::Goal:
            color = goalColor;
            break;
        case NodeState::Recalculated:
            color = convertToSfmlColor(RECALCULATED_NODE_COLOR);
            break;
        }
        return color;
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

        factorRect.setSize(sf::Vector2f(nodePointRadius * 1.5f ,nodePointRadius * 1.5f));
        nodeRect.setSize(sf::Vector2f(straightLineLength, straightLineLength));
    }

    void Renderer::render(const std::shared_ptr<ALatticeGraphWrapper> latticeGraphWrapperSPtr)
    {
        ALatGrWrHelpers::iterateOverALatticeGraphWrapperConst(latticeGraphWrapperSPtr,
        [this](const Node *node, int32_t h, int32_t w)
        {
            auto coords = getNodePosition(node, dimensionPtr->currentNodeSideLength());
            drawNode(*node, coords);
            if (appStateSPtr->showNodeInfo)
            {
                renderNodeInfo(*node, coords);
            }
        });
    }

    void Renderer::renderNodeInfo(const Node &node, sf::Vector2f coords)
    {

        using std::to_string;
        text.setString(dToStr(node.g));
        text.setPosition(sf::Vector2f(coords.x + NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));
        windowPtr->draw(text);
        float widthOfGText = text.getLocalBounds().width;

        text.setString(dToStr(node.rhs));
        float widthOfRHSText = text.getLocalBounds().width;
        float freeSpaceHor = dimensionPtr->currentNodeSideLength() - widthOfGText - widthOfRHSText;
        text.setPosition(sf::Vector2f(coords.x + freeSpaceHor + widthOfGText - NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));
        windowPtr->draw(text);

        std::string keyString = "[" + dToStr(node.key.k1) + ":" + dToStr(node.key.k2) + "]";
        text.setString(keyString);
        float halfOfText = text.getLocalBounds().width / 2;

        float buttomOfTopRow = text.getLocalBounds().height + NODE_INFO_OFFSET;
        float heightKeyOffset = dimensionPtr->currentNodeSideLength() - buttomOfTopRow - NODE_INFO_OFFSET;

        float halfOfNode = static_cast<float>(dimensionPtr->currentNodeSideLength()) / 2;
        float diff = halfOfNode - halfOfText;
        text.setPosition(sf::Vector2f(coords.x + diff, coords.y + NODE_INFO_OFFSET + heightKeyOffset));
        windowPtr->draw(text);

        factorRect.setPosition(sf::Vector2f(coords.x, coords.y + (halfOfNode - factorRect.getSize().y/2)));
        factorRect.setFillColor(sf::Color(100 + 14 * node.factor,0,140 - 14 * node.factor));
        windowPtr->draw(factorRect);
    }

    void Renderer::drawNode(const Node &node, sf::Vector2f coords)
    {
        nodeRect.setPosition(sf::Vector2f(coords.x, coords.y));
        nodeRect.setFillColor(stateColor(node.state));
        windowPtr->draw(nodeRect);
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

    void Renderer::updateColor()
    {

        sf::Color *color = nullptr;
        if (appStateSPtr->currentState == State::DONE)
        {
            color = &goalColor;
        }
        else if (appStateSPtr->currentState == State::NO_PATH)
        {
            color = &visitedColor;
        }
        if (colorUp)
        {
            if (color->r == 255)
            {
                colorUp = false;
            }
            else
            {
                color->r += COLOR_CHANGE_DIFF;
            }
        }
        else if (!colorUp)
        {
            if (color->r == 0)
            {
                colorUp = true;
            }
            else
            {
                color->r -= COLOR_CHANGE_DIFF;
            }
        }
    }

    void Renderer::update()
    {
        updateColor();
    }

    void Renderer::reset()
    {
        goalColor = convertToSfmlColor(GOAL_NODE_COLOR);
        visitedColor = convertToSfmlColor(VISITED_NODE_COLOR);
    }
}
