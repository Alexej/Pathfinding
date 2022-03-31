#include "DrawableNode.hpp"

#include "RenderingHelpers.hpp"
#include "Constants.hpp"
#include "Node.hpp"
#include "ApplicationState.hpp"
#include "Key.hpp"
#include "NodeStateColors.hpp"

namespace Pathfinding::Rendering
{
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::Vec2i;
    using Pathfinding::Helpers::convertToSfmlColor;
    using Pathfinding::Helpers::dToStr;
    using Pathfinding::Helpers::swapElements;
    using namespace Pathfinding::Constants;


    void DrawableNode::init(const sf::Font &font,
                            NodeStateColors *colors_,
                            ApplicationState *appStatePtr_,
                            Vec2i position_)
    {
        colors = colors_;
        appStatePtr = appStatePtr_;
        position = swapElements(position_);

        gText.setFont(font);
        rhsText.setFont(font);
        keyText.setFont(font);

        gText.setStyle(sf::Text::Bold);
        rhsText.setStyle(sf::Text::Bold);
        keyText.setStyle(sf::Text::Bold);

        gText.setCharacterSize(NODE_INFO_TEXT_SIZE);
        rhsText.setCharacterSize(NODE_INFO_TEXT_SIZE);
        keyText.setCharacterSize(NODE_INFO_TEXT_SIZE);

        gText.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));
        rhsText.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));
        keyText.setFillColor(convertToSfmlColor(NODE_INFO_COLOR));

        nodeRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        nodeRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));

        factorRect.setOutlineThickness(NODE_OUTLINE_THICKNESS);
        factorRect.setOutlineColor(convertToSfmlColor(NODE_OUTLINE_COLOR));

        setRectsSizeAndPosition();
    }

    void DrawableNode::prepareDrawableNode(const Node & node)
    {
        if(renderNodeInfo())
        {
            using std::to_string;
            auto nodeSideLength = nodeRect.getSize().x;
            auto coords = nodeRect.getPosition();
            gText.setString(dToStr(node.g));
            gText.setPosition(sf::Vector2f(coords.x + NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));
            float widthOfGText = gText.getLocalBounds().width;

            rhsText.setString(dToStr(node.rhs));
            float widthOfRHSText = rhsText.getLocalBounds().width;
            float freeSpaceHor = nodeSideLength - widthOfGText - widthOfRHSText;
            rhsText.setPosition(sf::Vector2f(coords.x + freeSpaceHor + widthOfGText - NODE_INFO_OFFSET, coords.y + NODE_INFO_OFFSET));

            std::string keyString = "[" + dToStr(node.key.k1) + ":" + dToStr(node.key.k2) + "]";
            keyText.setString(keyString);
            float halfOfText = keyText.getLocalBounds().width / 2;

            float buttomOfTopRow = keyText.getLocalBounds().height + NODE_INFO_OFFSET;
            float heightKeyOffset = nodeSideLength - buttomOfTopRow - NODE_INFO_OFFSET;

            float halfOfNode = static_cast<float>(nodeSideLength) / 2;
            float diff = halfOfNode - halfOfText;
            keyText.setPosition(sf::Vector2f(coords.x + diff, coords.y + NODE_INFO_OFFSET + heightKeyOffset));

            factorRect.setFillColor(sf::Color(100 + 28 * node.factor, 0, 140 - 28 * node.factor));
        }
        nodeRect.setFillColor(colors->getColor(node.state));
    }

    void DrawableNode::resize()
    {
        setRectsSizeAndPosition();
    }

    void DrawableNode::setRectsSizeAndPosition()
    {
        auto nodeSideLengthF = static_cast<float>(appStatePtr->dimension.currentNodeSideLength());
        auto mainRectPosition = position * appStatePtr->dimension.currentNodeSideLength();
        auto mainRectPositionsfVec2 = static_cast<sf::Vector2f>(mainRectPosition);
        nodeRect.setPosition(mainRectPositionsfVec2);
        nodeRect.setSize({nodeSideLengthF,nodeSideLengthF});

        auto factorRectSize = sf::Vector2f(nodeSideLengthF / 6.f, nodeSideLengthF / 6.f);
        auto factorRectHeight = mainRectPositionsfVec2.y + ((nodeSideLengthF / 2) - (factorRectSize.y / 2));
        auto factorRectPosition = sf::Vector2f(mainRectPositionsfVec2.x, factorRectHeight);
        factorRect.setPosition(factorRectPosition);
        factorRect.setSize(factorRectSize);
    }

    void DrawableNode::drawDrawableNode(sf::RenderTarget &target, bool nodeBlocked) const
    {
        target.draw(nodeRect);
        if (renderNodeInfo())
        {
            target.draw(rhsText);
            target.draw(gText);
            target.draw(keyText);
            if (nodeBlocked)
            {
                target.draw(factorRect);
            }
        }
    }

    bool DrawableNode::renderNodeInfo() const
    {
        return appStatePtr->showNodeInfo;
    }
}



