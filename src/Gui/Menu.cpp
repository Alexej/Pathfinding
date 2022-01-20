#include <imgui-SFML.h>
#include <imgui.h>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"

using namespace Pathfinding::Constants;
using Pathfinding::Core::ApplicationState;
using Pathfinding::Core::AlgorithmState;
using Pathfinding::Core::NumberOfNodes;
using Pathfinding::Core::NUMBER_OF_NODES_CHAR;

namespace Pathfinding::Gui
{
    Menu::Menu(ApplicationState *appStat_, int32_t offset_, int32_t height_, int32_t width_)
        : appStatePtr(appStat_), offset(static_cast<float>(offset_)), 
        height(static_cast<float>(height_)), 
        width(static_cast<float>(width_)) {}

    void Menu::show()
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoTitleBar;

        ImGui::SetNextWindowPos(ImVec2(offset, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);

        ImGui::Begin("Configuration", nullptr, window_flags);

        switch(appStatePtr->algState)
        {
            case AlgorithmState::READY:
                static int32_t item_current = static_cast<int32_t>(appStatePtr->dim.currentNumberOfNodes());
                ImGui::Spacing();
                ImGui::Text("Number of nodes");
                if (ImGui::Combo("", &item_current, NUMBER_OF_NODES_CHAR, IM_ARRAYSIZE(NUMBER_OF_NODES_CHAR)))
                {
                    if (static_cast<int32_t>(appStatePtr->dim.currentNumberOfNodes()) != item_current)
                    {
                        if (appStatePtr->dim.canRenderInfo())
                        {
                            appStatePtr->renderNodeInfo = false;
                        }
                        appStatePtr->numberOfNodesChanged = true;
                        appStatePtr->dim.setCurrentNumberOfNodes(static_cast<NumberOfNodes>(item_current));
                    }
                };

                ImGui::Separator();
                ImGui::Spacing();
                if(ImGui::Button("Start", ImVec2(width-20,20)))
                {
                    appStatePtr->algState = AlgorithmState::SEARCHING;
                }
            break;
            case AlgorithmState::SEARCHING:
                if(ImGui::Button("Step", ImVec2(width-20,20)))
                {
                    appStatePtr->algState = AlgorithmState::SEARCHING;
                }

        }

        //Common Elements
        ImGui::Separator();
        ImGui::Spacing();
        if (appStatePtr->dim.canRenderInfo())
        {
            if (ImGui::Checkbox("Render Node Info", &appStatePtr->renderNodeInfo))
            {
            }
        }
        ImGui::Spacing();
        if(ImGui::Button("RESET", ImVec2(width-20,20)))
        {
            appStatePtr->algState = AlgorithmState::SEARCHING;
        }


        ImGui::End();
    }
}