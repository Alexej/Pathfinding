#include "Renderer.hpp"

#include <array>
#include <SFML/Graphics/CircleShape.hpp>

#include "Constants.hpp"
#include "ApplicationState.hpp"
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Constants.hpp"
#include "GraphDimension.hpp"
#include "ResourcePaths.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::pathToFont;

    namespace
    {
        sf::Vector2f getNodePosition(Node *node, int32_t sideLength)
        {
            float nodesHorF = static_cast<float>(node->location.width);
            float nodesVertF = static_cast<float>(node->location.height);
            float sideLengthF = static_cast<float>(sideLength);
            float positionHor = nodesHorF * sideLengthF;
            float positionVer = nodesVertF * sideLengthF;
            return {positionHor, positionVer};
        }

        sf::Color convertToSfmlColor(std::array<uint8_t, 3> color)
        {
            return {color[RED], color[GREEN], color[BLUE]};
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
            double angle;
            Vec2i diff = n2->location - n1->location;
            if (diff == Vec2i(1, 1))
            {
                angle = 45;
            }
            else if (diff == Vec2i(1, 0))
            {
                angle = 90;
            }
            else if (diff == Vec2i(1, -1))
            {
                angle = 135;
            }
            else if (diff == Vec2i(0, -1))
            {
                angle = 180;
            }
            else if (diff == Vec2i(-1, -1))
            {
                angle = 225;
            }
            else if (diff == Vec2i(-1, 0))
            {
                angle = 270;
            }
            else if (diff == Vec2i(-1, 1))
            {
                angle = 315;
            }
            else if (diff == Vec2i(0, 1))
            {
                angle = 0;
            }
            return angle;
        }

        bool diagonal(double angle)
        {
            return angle == 45 || angle == 135 || angle == 225 || angle == 315;
        }
    }

    Renderer::Renderer(sf::RenderWindow *window, ApplicationState *state)
        : windowPtr(window), appStatePtr(state), dimensionPtr(&state->dimension())
    {
    }

    void Renderer::init()
    {
        loadFont("NugoSansLight.ttf");

        text.setFont(font);
        text.setStyle(sf::Text::Bold);

        nodeRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        nodeRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));

        text.setCharacterSize(NODE_INFO_TEXT_SIZE);
        text.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));

        nodePoint.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        nodePoint.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        diagonalLine.setFillColor(convertToSfmlColor(PATH_NODE_COLOR));
        diagonalLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        diagonalLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        straightLine.setFillColor(convertToSfmlColor(PATH_NODE_COLOR));
        straightLine.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        straightLine.setOutlineThickness(NODE_OUTLINE_THICKNESS);

        reset();
    }

    /**
     * @brief
     * !fix path!
     * @param fontName
     * @return sf::Font
     */
    void Renderer::loadFont(std::string fontName)
    {

        if (!font.loadFromFile(pathToFont() + fontName))
        {
            throw std::exception("Couldn't find font");
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

    void Renderer::render(const LatticeGraph &graph)
    {
        float sideLength = static_cast<float>(dimensionPtr->currentNodeSideLength());
        nodeRect.setSize(sf::Vector2f(sideLength, sideLength));
        for (std::size_t h = 0; h < graph.height(); ++h)
        {
            for (std::size_t w = 0; w < graph.width(); ++w)
            {
                auto currentNode = graph[h][w];
                auto coords = getNodePosition(&currentNode, dimensionPtr->currentNodeSideLength());
                drawNode(currentNode, coords);
                if (appStatePtr->showNodeInfo())
                {
                    renderNodeInfo(currentNode, coords);
                }
            }
        }
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
    }

    void Renderer::drawNode(const Node &node, sf::Vector2f coords)
    {
        nodeRect.setPosition(sf::Vector2f(coords.x, coords.y));
        nodeRect.setFillColor(stateColor(node.state));
        windowPtr->draw(nodeRect);
    }

    void Renderer::renderPath(std::vector<Node *> path)
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

        sf::Vector2f pointPositionOffset(halfNodeSize, halfNodeSize);

        if (appStatePtr->showPathLines() && appStatePtr->showPath())
        {
            renderPathLines(path, pointPositionOffset);
        }
        if (appStatePtr->showPath())
        {
            renderPathLineEndPoints(path, pointPositionOffset);
        }
    }

    void Renderer::renderPathLineEndPoints(std::vector<Node *> path, sf::Vector2f pointPositionOffset)
    {
        for (auto &node : path)
        {
            sf::Vector2f leftCornerOfNodePosition = getNodePosition(node, dimensionPtr->currentNodeSideLength());
            sf::Vector2f nodePointPosition = leftCornerOfNodePosition + pointPositionOffset;
            nodePoint.setFillColor(convertToSfmlColor(PATH_NODE_COLOR));
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

    void Renderer::renderPathLines(std::vector<Node *> path, sf::Vector2f pointPositionOffset)
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
        switch (appStatePtr->currentState())
        {
        case State::DONE:
            if (colorUp)
            {
                if (goalColor.r == 255)
                {
                    colorUp = false;
                }
                else
                {
                    goalColor.r += 5;
                }
            }
            else if (!colorUp)
            {
                if (goalColor.r == 0)
                {
                    colorUp = true;
                }
                else
                {
                    goalColor.r -= 5;
                }
            }
            break;
        case State::NO_PATH:
            if (colorUp)
            {
                if (visitedColor.g == 255)
                {
                    colorUp = false;
                }
                else
                {
                    visitedColor.g += 5;
                }
            }
            else if (!colorUp)
            {
                if (visitedColor.g == 0)
                {
                    colorUp = true;
                }
                else
                {
                    visitedColor.g -= 5;
                }
            }
            break;
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
