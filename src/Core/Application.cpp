#include "Application.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Window/Event.hpp>
#include "PathfinderReturnType.hpp"
#include "RenderingHelpers.hpp"
#include "ILatticeGraphHelpers.hpp"
#include "MouseData.hpp"
#include "Node.hpp"
#include "ILatticeGraph.hpp"

namespace Pathfinding::Core
{
    using namespace Constants;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Helpers::convertToSfmlColor;
    using Pathfinding::Helpers::ILatticeGraphHelpers;
    using Pathfinding::Algorithms::DFSMazeGenerator;
    using Pathfinding::Events::MouseData;
    using Pathfinding::Rendering::DrawablePath;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Abstract::ILatticeGraph;

    void Application::startAlgorithm()
    {
        graphOpsUPtr->disableEndpointsEvent();
        appState.currentState = AlgorithmState::SEARCHING;

        dstarLiteUPtr->initialize();
        dStarCache.cache(dstarLiteUPtr->initialRun());
        runAStar();
    }

    void Application::run()
    {
        menuUPtr->init(window);
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                handleInput(event);
            }
            update(deltaClock);
            draw();
        }
        menuUPtr->shutDown();
    }

    void Application::handleInput(sf::Event event)
    {
        menuUPtr->processEvent(event);
        eventManagerUPtr->pushEvent(event);
    }

    void Application::update(sf::Clock &deltaClock)
    {
        latGraphWrapUPtr->latGraphSPtr->update();
        if(appState.algorithmFinished())
        {
            gradChager.updateColors(appState.currentState);
        }
        sf::Time dt = deltaClock.getElapsedTime();
        if (appState.currentState == AlgorithmState::SEARCHING && appState.autoStep)
        {
            accumulator += dt.asMilliseconds();
            if (accumulator > appState.stepSpeed)
            {
                step();
                accumulator = 0;
            }
        }
        eventManagerUPtr->processEvents(bindings);
        menuUPtr->update(window, dt);
        deltaClock.restart();
    }

    void Application::handleNumberOfNodesChange(int32_t index)
    {
        dimensionPtr->setCurrentNumberOfNodesIndex(index);
        graphOpsUPtr->resize(dimensionPtr->currentNodeSideLength());
        drawablePath.resize();
        latGraphWrapUPtr->resize(dimensionPtr->height(), dimensionPtr->width());
        appState.nodeUnderCursor = nullptr;
        ILatticeGraphHelpers::initRendering(*latGraphWrapUPtr->latGraphSPtr,
                                            fontLoaderSPtr->getFont("NugoSansLight"),
                                            &colors,
                                            &appState);
    }

    void Application::draw()
    {
        menuUPtr->show();
        window.clear();
        menuUPtr->render(window);
        rendererUPtr->render(window, *latGraphWrapUPtr->latGraphSPtr);
        if (appState.currentState == AlgorithmState::FOUND_PATH || appState.currentState == AlgorithmState::SEARCHING)
        {
            if(appState.showAStarPath)
            {
                drawPath(aStarCache.currentPath, convertToSfmlColor(PATH_NODE_COLOR_2));
            }
            drawPath(dStarCache.currentPath, convertToSfmlColor(PATH_NODE_COLOR));
        }
        window.display();
    }

    void Application::reset()
    {
        dstarLiteUPtr->reset();
        latGraphWrapUPtr->reset();
        appState.currentState = AlgorithmState::READY;
        graphOpsUPtr->enableEndPointsEvent();
        graphOpsUPtr->enableObsticlesAndScrollEvents();
        appState.nodeUnderCursor = nullptr;
        aStarCache.reset();
        dStarCache.reset();
        colors.reset();
    }

    void Application::done()
    {
        graphOpsUPtr->disableObsticlesAndScrollEvents();
        appState.currentState = AlgorithmState::FOUND_PATH;
    }

    void Application::noPath()
    {
        graphOpsUPtr->disableObsticlesAndScrollEvents();
        appState.currentState = AlgorithmState::NO_PATH;
    }
 
    void Application::randomGraph()
    {
        appState.nodeUnderCursor = nullptr;
        do
        {
            latGraphWrapUPtr->reset();
            ILatticeGraphHelpers::initRandomGraph(*latGraphWrapUPtr->latGraphSPtr, ri);
        } while(!aStarUPtr->calculatePath(*latGraphWrapUPtr).pathFound);
    }

    void Application::step()
    {
        dStarCache.cache(dstarLiteUPtr->followingRun());
        if(dStarCache.nodesExpandedLastIteration())
        {
            runAStar();
        }
        else
        {
            aStarCache.cache({true, aStarCache.currentPath, {}});
        }
    }

    void Application::runAStar()
    {
        if(appState.runAStar)
        {
            aStarCache.cache(aStarUPtr->calculatePath(*latGraphWrapUPtr));
        }
    }

    void Application::mouseWheelEventChanged(int32_t index)
    {
        appState.currentMouseWheelEvent = static_cast<MouseWheelEvent>(index);
    }

    void Application::generateMaze()
    {
        latGraphWrapUPtr->reset();
        latGraphWrapUPtr->removeEndpointsFromGraph();
        dfsmg.reset();
        dfsmg(*latGraphWrapUPtr->latGraphSPtr, ri);
        latGraphWrapUPtr->addEndpointsToGraph();
    }

    void Application::drawPath(const std::vector<const Node *> & path, sf::Color color)
    {
        drawablePath.prepare(path, color);
        rendererUPtr->render(window, drawablePath);
    }
}


