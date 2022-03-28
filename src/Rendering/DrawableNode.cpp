#include "DrawableNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "RenderingHelpers.hpp"
#include "Constants.hpp"
#include "Node.hpp"

namespace Pathfinding::Rendering
{
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Helpers::convertToSfmlColor;
    using Pathfinding::Helpers::dToStr;
    using namespace Pathfinding::Constants;

    void DrawableNode::init(const sf::Font &font)
    {
        g.setFont(font);
        rhs.setFont(font);
        key.setFont(font);

        g.setStyle(sf::Text::Bold);
        rhs.setStyle(sf::Text::Bold);
        key.setStyle(sf::Text::Bold);

        g.setCharacterSize(NODE_INFO_TEXT_SIZE);
        rhs.setCharacterSize(NODE_INFO_TEXT_SIZE);
        key.setCharacterSize(NODE_INFO_TEXT_SIZE);

        g.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));
        rhs.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));
        key.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));

        nodeRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        nodeRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));

        factorRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        factorRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));
    }

    void DrawableNode::prepare(const Node &node, sf::Vector2f coords, sf::Color color, bool renderInfo)
    {
        nodeRect.setPosition(coords);
        nodeRect.setFillColor(color);
        
        nodeBlocked = node.state == NodeState::Blocked ? true : false;

        if (renderInfo)
        {
            using std::to_string;

            auto nodeSideLength = nodeRect.getSize().x;
            g.setString(dToStr(node.g));
            g.setPosition(sf::Vector2f(coords.x + NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));
            float widthOfGText = g.getLocalBounds().width;

            rhs.setString(dToStr(node.rhs));
            float widthOfRHSText = rhs.getLocalBounds().width;
            float freeSpaceHor = nodeSideLength - widthOfGText - widthOfRHSText;
            rhs.setPosition(sf::Vector2f(coords.x + freeSpaceHor + widthOfGText - NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));

            std::string keyString = "[" + dToStr(node.key.k1) + ":" + dToStr(node.key.k2) + "]";
            key.setString(keyString);
            float halfOfText = key.getLocalBounds().width / 2;

            float buttomOfTopRow = key.getLocalBounds().height + NODE_INFO_OFFSET;
            float heightKeyOffset = nodeSideLength - buttomOfTopRow - NODE_INFO_OFFSET;

            float halfOfNode = static_cast<float>(nodeSideLength) / 2;
            float diff = halfOfNode - halfOfText;
            key.setPosition(sf::Vector2f(coords.x + diff, coords.y + NODE_INFO_OFFSET + heightKeyOffset));

            factorRect.setPosition(sf::Vector2f(coords.x, coords.y + (halfOfNode - factorRect.getSize().y / 2)));
            factorRect.setFillColor(sf::Color(100 + 28 * node.factor, 0, 140 - 28 * node.factor));
        }
        renderInfoInNode = renderInfo;
    }

    void DrawableNode::resize(float nodeSideLength)
    {
        auto factorRectSize = sf::Vector2f(nodeSideLength / 6.f ,nodeSideLength / 6.f);
        auto nodeRectSize = sf::Vector2f(nodeSideLength, nodeSideLength);

        nodeRect.setSize(nodeRectSize);
        factorRect.setSize(factorRectSize);
    }

    void DrawableNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(nodeRect);
        if (renderInfoInNode)
        {
            target.draw(rhs);
            target.draw(g);
            target.draw(key);
            if(!nodeBlocked)
            {
                target.draw(factorRect);
            }
        }
    }
}