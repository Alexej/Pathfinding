#include "Renderer.hpp"

#include <array>

#include "Constants.hpp"
#include "ApplicationState.hpp"
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Constants.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Datastructures::GraphLocation;
    using Pathfinding::Datastructures::NodeState;

    namespace
    {
        sf::Vector2f getNodePosition(GraphLocation location, int32_t sideLength)
        {
            float nodesHorF = static_cast<float>(location.width);
            float nodesVertF = static_cast<float>(location.height);
            float sideLengthF = static_cast<float>(sideLength);
            float positionHor = nodesHorF * sideLengthF;
            float positionVer = nodesVertF * sideLengthF;
            return {positionHor, positionVer};
        }

        std::string convertIntToStringWithInf(int32_t num)
        {
            if (num == std::numeric_limits<int32_t>::max())
            {
                return std::string("inf");
            }
            return std::to_string(num);
        };

        sf::Color convertToSfmlColor(std::array<uint8_t, 3> color)
        {
            return {color[RED], color[GREEN], color[BLUE]};
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
            }
            return color;
        }
    }

    Renderer::Renderer()
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
        if (!font.loadFromFile("C:\\Users\\alexe\\Desktop\\project\\Pathfinding\\dependencies\\fonts\\" + fontName))
        {
            throw std::exception("Couldn't find font");
        }
    }

    void Renderer::render(sf::RenderWindow &window, const LatticeGraph &graph, ApplicationState & state)
    {
        nodeRect.setSize(sf::Vector2f(state.dim.currentNodeSideLength(), state.dim.currentNodeSideLength()));
        for (std::size_t h = 0; h < graph.height(); ++h)
        {
            for (std::size_t w = 0; w < graph.width(); ++w)
            {
                auto currentNode = graph[h][w];
                auto coords = getNodePosition(currentNode.location, state.dim.currentNodeSideLength());
                drawNode(window, currentNode, coords);
                if (state.renderNodeInfo)
                {
                    renderNodeInfo(window, currentNode, coords, state.dim.currentNodeSideLength());
                }
            }
        }
    }

    void Renderer::renderNodeInfo(sf::RenderWindow &window, const Node &node, sf::Vector2f coords, int32_t nodeSideLength)
    {
        text.setString(convertIntToStringWithInf(node.g));
        text.setPosition(sf::Vector2f(coords.x + NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));
        window.draw(text);
        float widthOfGText = text.getLocalBounds().width;

        text.setString(convertIntToStringWithInf(node.rhs));
        float widthOfRHSText = text.getLocalBounds().width;
        float freeSpaceHor = nodeSideLength - widthOfGText - widthOfRHSText;
        text.setPosition(sf::Vector2f(coords.x + freeSpaceHor + widthOfGText - NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));
        window.draw(text);

        std::string keyString = "[" + convertIntToStringWithInf(node.key.k1) + ":" + convertIntToStringWithInf(node.key.k2) + "]";
        text.setString(keyString);
        float halfOfText = text.getLocalBounds().width / 2;
        float heightKeyOffset = 2 * text.getLocalBounds().height + NODE_INFO_OFFSET;
        float halfOfNode = static_cast<float>(nodeSideLength) / 2;
        float diff = halfOfNode - halfOfText;
        text.setPosition(sf::Vector2f(coords.x + diff, coords.y + NODE_INFO_OFFSET + heightKeyOffset));
        window.draw(text);
    }

    void Renderer::drawNode(sf::RenderWindow &window, const Node &node, sf::Vector2f coords)
    {
        nodeRect.setPosition(sf::Vector2f(coords.x, coords.y));
        nodeRect.setFillColor(stateColor(node.state));
        window.draw(nodeRect);
    }
}