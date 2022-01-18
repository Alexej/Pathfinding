#include <imgui-SFML.h>
#include <imgui.h>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"

using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    Menu::Menu(ApplicationState *appStat_, int32_t offset_, int32_t height_, int32_t width_)
        : appStatePtr(appStat_), offset(static_cast<float>(offset_)), 
        height(static_cast<float>(height_)), 
        width(static_cast<float>(width_)) {}

    bool Menu::nodeSizeLargeEnoughForInfo()
    {
        return NUMBER_OF_NODES[appStatePtr->currentNumberOfNodeIndex] == NUMBER_OF_NODES[0];
    }

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

        static int item_current = appStatePtr->currentNumberOfNodeIndex;
        ImGui::Spacing();
        ImGui::Text("Number of nodes");
        if (ImGui::Combo("", &item_current, NUMBER_OF_NODES_CHAR, IM_ARRAYSIZE(NUMBER_OF_NODES_CHAR)))
        {
            if (appStatePtr->currentNumberOfNodeIndex != item_current)
            {
                if (nodeSizeLargeEnoughForInfo())
                {
                    appStatePtr->renderNodeInfo = false;
                }
                appStatePtr->numberOfNodesChanged = true;
                appStatePtr->currentNumberOfNodeIndex = item_current;
            }
        };

        ImGui::Separator();
        ImGui::Spacing();
        if (nodeSizeLargeEnoughForInfo())
        {
            if (ImGui::Checkbox("Render Node Info", &appStatePtr->renderNodeInfo))
            {
            }
        }

        ImGui::End();
    }
}