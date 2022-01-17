#include <imgui-SFML.h>
#include <imgui.h>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"

using namespace Pathfinding::Constants;

namespace Pathfinding::Core
{
    Menu::Menu(ApplicationState *appStat_, int32_t offset_, int32_t height_, int32_t width_)
        : appStatePtr(appStat_), offset(offset_), height(height_), width(width_) {}

    void Menu::show()
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;

        ImGui::SetNextWindowPos(ImVec2(offset, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);

        ImGui::Begin("Configuration", nullptr, window_flags);

        const char *  NUMBER_OF_NODES_CHAR[] = {"100", "400", "625", "1600"};
        static int item_current = 0;

        if(ImGui::Combo("Number of nodes", &item_current, NUMBER_OF_NODES_CHAR, IM_ARRAYSIZE(NUMBER_OF_NODES_CHAR)))
        {
            appStatePtr->numberOfNodesChanged = true;
            appStatePtr->currentNumberOfNodeIndex = item_current;
        };

        ImGui::End();
    }
}