#include "Renderer.hpp"

#include <array>

#include "Constants.hpp"
#include "ApplicationState.hpp"
#include "Node.hpp"
#include "LatticeGraph.hpp"
#include "Constants.hpp"

using namespace Pathfinding::Constants;
using Pathfinding::Datastructures::NodeState;

namespace Pathfinding::Core
{
    namespace
    {
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

    Renderer::Renderer(const ApplicationState *appState)
        : appStatePtr(appState)
    {
        loadFont("NugoSansLight.ttf");
        text.setFont(font);
        text.setStyle(sf::Text::Bold);
        resize();
    }


    void Renderer::resize()
    {
        nodeRect.setSize(sf::Vector2f(appStatePtr->currentNodeSideLength, appStatePtr->currentNodeSideLength));
        nodeRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        nodeRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
        text.setCharacterSize(appStatePtr->currentNodeSideLength / NODE_INFO_TEXT_FACTOR);
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

    void Renderer::render(sf::RenderWindow &window, const LatticeGraph & graph)
    {
        for (std::size_t h = 0; h < graph.height(); ++h)
        {
            for (std::size_t w = 0; w < graph.width(); ++w)
            {
                drawNode(window, graph[h][w]);
            }
        }
    }

    void Renderer::drawNode(sf::RenderWindow &window, const Node &node)
    {
        float nodesHor = static_cast<float>(node.location.width);
        float nodesVert = static_cast<float>(node.location.height);
        float sideLength = static_cast<float>(appStatePtr->currentNodeSideLength);
        float positionHor = nodesHor * sideLength;
        float positionVer = nodesVert * sideLength;

        nodeRect.setPosition(sf::Vector2f(positionHor, positionVer));
        nodeRect.setFillColor(stateColor(node.state));
        window.draw(nodeRect);

        auto giveInf = [](int32_t num){
            if(num == std::numeric_limits<int32_t>::max())
            {
                return std::string("inf");
            }
            else
            return std::to_string(num);
        };

        if (appStatePtr->renderNodeInfo)
        {
            text.setString(giveInf(node.g));
            text.setPosition(sf::Vector2f(positionHor + NODE_INFO_OFFSET, positionVer + NODE_INFO_OFFSET));
            window.draw(text);
            float widthOfGText = text.getLocalBounds().width;

            text.setString(giveInf(node.rhs));
            float widthOfRHSText = text.getLocalBounds().width;
            float freeSpaceHor = appStatePtr->currentNodeSideLength - widthOfGText - widthOfRHSText;
            text.setPosition(sf::Vector2f(positionHor + freeSpaceHor + widthOfGText - NODE_INFO_OFFSET, positionVer + NODE_INFO_OFFSET));
            window.draw(text);

            std::string keyString = "[" + giveInf(node.key.k1) +":"+ giveInf(node.key.k2) +"]";
            text.setString(keyString);
            float halfOfText = text.getLocalBounds().width / 2;
            float heightKeyOffset = 2 * text.getLocalBounds().height + NODE_INFO_OFFSET;
            float halfOfNode = static_cast<float>(appStatePtr->currentNodeSideLength) / 2;
            float diff = halfOfNode - halfOfText;
            text.setPosition(sf::Vector2f(positionHor + diff, positionVer + NODE_INFO_OFFSET + heightKeyOffset));
            window.draw(text);
        }
    }
}