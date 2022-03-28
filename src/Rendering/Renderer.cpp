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

   Renderer::Renderer(ApplicationState *appStateSPtr_, 
                       std::shared_ptr<IFontLoader> fontLoaderSPtr_)
        :       
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
        float nodeSideLength = static_cast<float>(dimensionPtr->currentNodeSideLength());
        drawablePath.resize();
        drawableNode.resize(nodeSideLength);
    }

    void Renderer::render(sf::RenderWindow & window, const std::shared_ptr<ALatGraphWr> latticeGraphWrapperSPtr)
    {
        if(appStateSPtr->algorithmFinished()) { updateColors(); }
        ILatticeGraphHelpers::iterateOverLatticeGraphConst(*latticeGraphWrapperSPtr->latGraphSPtr,
        [this, &window](const Node *node, int32_t h, int32_t w)
        {
            auto coords = getNodePosition(node, dimensionPtr->currentNodeSideLength());
            auto color = stateColor(node->state);
            if(node->state == NodeState::Blocked) { color = blockedNodeGradient; }
            else if(node->state == NodeState::Start) { color = startNodeGradient; }
            drawableNode.prepare(*node, coords, color, appStateSPtr->showNodeInfo);
            window.draw(drawableNode);
        });
    }

    void Renderer::render(sf::RenderWindow & window, const DrawablePath & path)
    {
        window.draw(path);
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
            gradients.gradientGoalGreen(startNodeGradient.g, 5);
        }
    }
}
