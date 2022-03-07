#include "Application.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>

#include "ALatGrWrHelpers.hpp"
#include "LatticeGraphWrapper.hpp"

namespace Pathfinding::Core
{
    using Pathfinding::Helpers::ALatGrWrHelpers;
    using Pathfinding::Datastructures::LatticeGraphWrapper;

    void Application::startAlgorithm()
    {
        graphOpsUPtr->disableEndpointsEvent();
        appState.currentState = State::SEARCHING;

        dstarLiteUPtr->initialize();
        dstarLiteUPtr->initialRun();
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
                dstarLiteUPtr->moveStart();
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
            rendererUPtr->renderPath(dstarLiteUPtr->path());
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
        ALatGrWrHelpers::initRandomGraph(latGraphWrapUPtr);
    }

    void Application::step()
    {
        dstarLiteUPtr->moveStart();
    }
}
