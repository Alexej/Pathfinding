#include "Application.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

#include "LatticeGraphHelpers.hpp"
#include "LatticeGraphWrapper.hpp"
#include "PathfinderReturnType.hpp"
#include "Constants.hpp"
#include "RenderingHelpers.hpp"

namespace Pathfinding::Core
{
    using namespace Constants;
    using Pathfinding::Helpers::LatticeGraphHelpers;
    using Pathfinding::Datastructures::LatticeGraphWrapper;
    using Pathfinding::Datastructures::PathfinderReturnType;
    using Pathfinding::Helpers::convertToSfmlColor;

    void Application::startAlgorithm()
    {
        graphOpsUPtr->disableEndpointsEvent();
        appState.currentState = State::SEARCHING;

        dstarLiteUPtr->initialize();
        dStarCache.cache(dstarLiteUPtr->initialRun());
        if(appState.runAStar)
        {
            aStarCache.cache(aStarUPtr->calculatePath(latGraphWrapUPtr));
        }
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
        if(appState.currentState == State::DONE || appState.currentState == State::NO_PATH)
        {
            rendererUPtr->update();
        }
        if (appState.currentState == State::SEARCHING && appState.autoStep)
        {
            accumulator += dt;
            if (accumulator > algoStepSpeedPtr->getCurrentStepSpeed())
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
        if (appState.currentState == State::DONE || appState.currentState == State::SEARCHING)
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
        appState.currentState = State::READY;
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
        appState.currentState = State::DONE;
    }

    void Application::noPath()
    {
        graphOpsUPtr->disableObsticlesEvents();
        appState.currentState = State::NO_PATH;
    }

    void Application::randomGraph()
    {
        reset();
        LatticeGraphHelpers::initRandomGraph(latGraphWrapUPtr->latGraphSPtr);
    }

    void Application::step()
    {
        dStarCache.cache(dstarLiteUPtr->moveStart());
        if(appState.runAStar)
        {
            aStarCache.cache(aStarUPtr->calculatePath(latGraphWrapUPtr));
        }
    }
}
