#include "Application.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Window/Event.hpp>
#include "PathfinderReturnType.hpp"
#include "RenderingHelpers.hpp"
#include "LatticeGraphHelpers.hpp"
#include "DFSMazeGenerator.hpp"
#include "MouseData.hpp"

namespace Pathfinding::Core
{
    using namespace Constants;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Helpers::convertToSfmlColor;
    using Pathfinding::Helpers::ILatticeGraphHelpers;
    using Pathfinding::Algorithms::DFSMazeGenerator;
    using Pathfinding::Events::MouseData;

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
        ImGui::SFML::Init(window);
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
        ImGui::SFML::Shutdown();
    }

    void Application::handleInput(sf::Event event)
    {
        ImGui::SFML::ProcessEvent(event);
        eventManagerUPtr->pushEvent(event);
    }

    void Application::update(sf::Clock &deltaClock)
    {
        int32_t dt = deltaClock.getElapsedTime().asMilliseconds();
        if (appState.currentState == AlgorithmState::SEARCHING && appState.autoStep)
        {
            accumulator += dt;
            if (accumulator > appState.stepSpeed)
            {
                step();
                accumulator = 0;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        eventManagerUPtr->processEvents();
    }

    void Application::handleNumberOfNodesChange(int32_t index)
    {
        dimensionPtr->setCurrentNumberOfNodesIndex(index);
        rendererUPtr->resize();
        graphOpsUPtr->resize(dimensionPtr->currentNodeSideLength());
        reset();
    }

    void Application::draw()
    {
        menuUPtr->show();
        window.clear();
        ImGui::SFML::Render(window);
        rendererUPtr->render(latGraphWrapUPtr);
        if (appState.currentState == AlgorithmState::FOUND_PATH || appState.currentState == AlgorithmState::SEARCHING)
        {
            if(appState.showAStarPath)
            {
                rendererUPtr->renderPath(aStarCache.currentPath, convertToSfmlColor(PATH_NODE_COLOR_2));
            }
            rendererUPtr->renderPath(dStarCache.currentPath, convertToSfmlColor(PATH_NODE_COLOR));
        }
        window.display();
    }

    void Application::reset()
    {
        dstarLiteUPtr->reset();
        latGraphWrapUPtr->resize(dimensionPtr->height(), dimensionPtr->width());
        appState.currentState = AlgorithmState::READY;
        graphOpsUPtr->enableEndPointsEvent();
        graphOpsUPtr->enableObsticlesEvents();
        appState.nodeUnderCursor = nullptr;
        rendererUPtr->reset();
        aStarCache.reset();
        dStarCache.reset();
    }

    void Application::done()
    {
        graphOpsUPtr->disableObsticlesEvents();
        appState.currentState = AlgorithmState::FOUND_PATH;
    }

    void Application::noPath()
    {
        graphOpsUPtr->disableObsticlesEvents();
        appState.currentState = AlgorithmState::NO_PATH;
    }
 
    void Application::randomGraph()
    {
        appState.nodeUnderCursor = nullptr;
        do
        {
            latGraphWrapUPtr->resize(dimensionPtr->height(), dimensionPtr->width());
            ILatticeGraphHelpers::initRandomGraph(*latGraphWrapUPtr->latGraphSPtr, ri);
        } while(!aStarUPtr->calculatePath(latGraphWrapUPtr).pathFound);
    }

    void Application::step()
    {
        dStarCache.cache(dstarLiteUPtr->followingRun());
        if(dStarCache.nodesExpandedAll.back().size() != 0)
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
            aStarCache.cache(aStarUPtr->calculatePath(latGraphWrapUPtr));
        }
    }

    void Application::mouseWheelEventChanged(int32_t index)
    {
        appState.currentMouseWheelEvent = static_cast<MouseWheelEvent>(index);
    }

    void Application::mouseWheelMoved(MouseData mouseData)
    {
        if(appState.currentMouseWheelEvent != MouseWheelEvent::Zoom)
        {
            return;
        }
        printf("%i\n", mouseData.wheelDelta);
    }

    void Application::generateMaze()
    {
        DFSMazeGenerator dfsmg;
        latGraphWrapUPtr->resize(dimensionPtr->height(), dimensionPtr->width());
        latGraphWrapUPtr->removeEndpointsFromGraph();
        dfsmg.generate(*latGraphWrapUPtr->latGraphSPtr, ri);
        latGraphWrapUPtr->addEndpointsToGraph();
    }
}


