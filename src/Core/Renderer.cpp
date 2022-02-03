#include "Renderer.hpp"

#include <array>

#include "Constants.hpp"
#include "ApplicationState.hpp"
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Constants.hpp"
#include "GraphDimension.hpp"
#include <SFML/Graphics/CircleShape.hpp>

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Datastructures::Vector2i;
    using Pathfinding::Datastructures::NodeState;
    namespace
    {
        sf::Vector2f getNodePosition(Vector2i location, int32_t sideLength)
        {
            float nodesHorF = static_cast<float>(location.width);
            float nodesVertF = static_cast<float>(location.height);
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
         * should be certain that cost, rhs, g and key values are always whole numbers
         * @param d 
         * @return std::string 
         */
        std::string dToStr(double d)
        {
            std::string dStr = std::to_string(d);
            return dStr.substr(0, dStr.find("."));
        }

        sf::Color stateColor(NodeState state)
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
                color = convertToSfmlColor(VISITED_NODE_COLOR);
                break;
            case NodeState::Start:
                color = convertToSfmlColor(START_NODE_COLOR);
                break;
            case NodeState::Goal:
                color = convertToSfmlColor(GOAL_NODE_COLOR);
                break;
            case NodeState::Recalculated:
                color = convertToSfmlColor(RECALCULATED_NODE_COLOR);
                break;
            }
            return color;
        }
    }


    Renderer::Renderer(sf::RenderWindow * window, ApplicationState * state)
    : windowPtr(window), appStatePtr(state), dimensionPtr(&state->dimension())
    {}

    void Renderer::init()
    {
        loadFont("NugoSansLight.ttf");
        text.setFont(font);
        text.setStyle(sf::Text::Bold);
        nodeRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        nodeRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        text.setCharacterSize(NODE_INFO_TEXT_SIZE);
        text.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));
    }

    /**
     * @brief
     * !fix path!
     * @param fontName
     * @return sf::Font
     */
    void Renderer::loadFont(std::string fontName)
    {
        if (!font.loadFromFile(fontPath + fontName))
        {
            throw std::exception("Couldn't find font");
        }
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
                auto coords = getNodePosition(currentNode.location, dimensionPtr->currentNodeSideLength());
                drawNode(currentNode, coords);
                if (appStatePtr->showNodeInfo())
                {
                    renderNodeInfo(currentNode, coords);
                }
            }
        }
    }

    void Renderer::renderNodeInfo( const Node &node, sf::Vector2f coords)
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
        float heightKeyOffset = 2.5 * text.getLocalBounds().height + NODE_INFO_OFFSET;
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
        float halfNodeSize = static_cast<float>(dimensionPtr->currentNodeSideLength()) / 2;
        float halfNodeSizeSquared = static_cast<float>(pow(halfNodeSize, 2));
        float diagonalLength = 2 * sqrt(halfNodeSizeSquared + halfNodeSizeSquared);
        sf::Vector2f pointPositionOffset(halfNodeSize,halfNodeSize);

        sf::CircleShape nodePoint;
        sf::RectangleShape diagonal;
        sf::RectangleShape straight;

        float nodePointRadius;
        if(dimensionPtr->canShowNodeInfo())
        {
            nodePointRadius = halfNodeSize / 5;
        }
        else
        {
            nodePointRadius = halfNodeSize / 2.5;
        }
        nodePoint.setRadius(nodePointRadius);
        nodePoint.setFillColor(convertToSfmlColor(PATH_NODE_COLOR));
        nodePoint.setOrigin(nodePointRadius, nodePointRadius);
        nodePoint.setOutlineColor(sf::Color::White);
        nodePoint.setOutlineThickness(1);

        for(auto & node : path)
        {
            if(node->state != NodeState::Blocked)
            {
                sf::Vector2f leftCornerOfNodePosition = getNodePosition(node->location, dimensionPtr->currentNodeSideLength());
                sf::Vector2f nodePointPosition = leftCornerOfNodePosition + pointPositionOffset;
                nodePoint.setPosition(nodePointPosition);
                windowPtr->draw(nodePoint);
            }
        }
    }
}