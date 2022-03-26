#include "Renderer.hpp"
#include "ApplicationState.hpp"
#include "IFontLoader.hpp"
#include "ALatGraphWr.hpp"
#include "LatticeGraphHelpers.hpp"
#include "Node.hpp"
#include "Constants.hpp"
#include "RenderingHelpers.hpp"

namespace Pathfinding::Rendering
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::AlgorithmState;
    using Pathfinding::Abstract::IFontLoader;
    using Pathfinding::Abstract::ALatGraphWr;
    using Pathfinding::Helpers::ILatticeGraphHelpers;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Helpers::getNodePosition;
    using Pathfinding::Helpers::stateColor;
    using Pathfinding::Helpers::convertToSfmlColor;

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
        drawablePath.init(appStateSPtr);
    }

    void Renderer::resize()
    {
        float straightLineLength = static_cast<float>(currentNodeSideLength);
        float halfNodeSize = straightLineLength / 2;

        float nodePointRadius;

        if (currentNodeSideLength >= 80)
        {
            nodePointRadius = halfNodeSize / 5;
        }
        else
        {
            nodePointRadius = halfNodeSize / 2.5f;
        }

        float halfNodeSizeSquared = static_cast<float>(pow(straightLineLength / 2, 2));

        float lineThickness = nodePointRadius / 2;
        float diagonalLineLength = 2 * sqrt(halfNodeSizeSquared + halfNodeSizeSquared);

        auto straightLineSize = sf::Vector2f(straightLineLength, lineThickness);
        auto diagonalLineSize = sf::Vector2f(diagonalLineLength, lineThickness);

        auto origin = sf::Vector2f(0, lineThickness / 2);

        auto factorRectSize = sf::Vector2f(nodePointRadius * 1.5f ,nodePointRadius * 1.5f);
        auto nodeRectSize = sf::Vector2f(straightLineLength, straightLineLength);

        drawablePath.resize(nodePointRadius, straightLineSize, diagonalLineSize, origin);
        drawableNode.resize(nodeRectSize, factorRectSize);
    }

    void Renderer::render(const std::shared_ptr<ALatGraphWr> latticeGraphWrapperSPtr)
    {
        if(appStateSPtr->algorithmFinished()) { updateColors(); }
        ILatticeGraphHelpers::iterateOverLatticeGraphConst(*latticeGraphWrapperSPtr->latGraphSPtr,
        [this](const Node *node, int32_t h, int32_t w)
        {
            auto coords = getNodePosition(node, currentNodeSideLength);
            auto color = stateColor(node->state);
            if(node->state == NodeState::Blocked) { color = blockedNodeGradient; }
            else if(node->state == NodeState::Start) { color = startNodeGradient; }
            drawableNode.prepare(*node, coords, color, currentNodeSideLength >= 80);
            windowPtr->draw(drawableNode);
        });
    }


    void Renderer::reset()
    {
        startNodeGradient = convertToSfmlColor(START_NODE_COLOR);
        blockedNodeGradient = convertToSfmlColor(BLOCKED_NODE_COLOR);
    }

    void Renderer::updateColors()
    {
        if(appStateSPtr->currentState == AlgorithmState::NO_PATH)
        {
            gradients.gradientBlockedRed(blockedNodeGradient.r, 5);
            gradients.gradientBlockedBlue(blockedNodeGradient.b, 1);
        }
        else if(appStateSPtr->currentState == AlgorithmState::FOUND_PATH)
        {
            gradients.gradientGoalRed(startNodeGradient.r, 5);   
            gradients.gradientGoalGreen(startNodeGradient.g, 1);
        }
    }


    void Renderer::renderPath(const std::vector<Node *> &path, sf::Color color)
    {
        auto halfNodeSide = currentNodeSideLength / 2.f;
        sf::Vector2f pointPositionOffset(halfNodeSide,halfNodeSide);
        drawablePath.prepare(path, pointPositionOffset, color);
        windowPtr->draw(drawablePath);
    }
}
