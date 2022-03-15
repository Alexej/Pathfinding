#include "GuiHelpers.hpp"

#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

#include "imgui.h"
#include "ApplicationState.hpp"
#include "Node.hpp"
#include "PathfinderCache.hpp"

namespace ImGui
{
    void HelpMarker(const char* desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    auto vector_getter(void *vec, int idx, const char **out_text)
    {
        auto &vector = *static_cast<std::vector<std::string> *>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size()))
        {
            return false;
        }
        *out_text = vector.at(idx).c_str();
        return true;
    };

    bool custom_combo(const char *label, int *currIndex, std::vector<std::string> &values)
    {
        if (values.empty())
        {
            return false;
        }
        return Combo(label, currIndex, vector_getter,
                     static_cast<void *>(&values), static_cast<int32_t>(values.size()));
    }
}

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::PathfinderCache;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Core::AlgorithmState;
    
    std::string mapNodeStateToText(NodeState state)
    {
        std::string str;
        switch (state)
        {
        case NodeState::Blocked:
            str = "Blocked";
            break;
        case NodeState::Free:
            str = "Free";
            break;
        case NodeState::Frontier:
            str = "Frontier";
            break;
        case NodeState::Goal:
            str = "Goal";
            break;
        case NodeState::Start:
            str = "Start";
            break;
        case NodeState::Visited:
            str = "Visited";
            break;
        }
        return str;
    }

    std::string mapStateToText(AlgorithmState state)
    {
        std::string str;
        switch (state)
        {
        case AlgorithmState::READY:
            str = "READY";
            break;
        case AlgorithmState::SEARCHING:
            str = "SEARCHING";
            break;
        case AlgorithmState::FOUND_PATH:
            str = "DONE";
            break;
        case AlgorithmState::NO_PATH:
            str = "NO_PATH";
            break;
        }
        return str;
    }

    std::array<uint32_t, 3> getStateColor(Pathfinding::Core::AlgorithmState state)
    {
        std::array<uint32_t, 3> color;
        switch (state)
        {
        case AlgorithmState::READY:
            color = {255,255,255};
            break;
        case AlgorithmState::SEARCHING:
            color = {90,60,160};
            break;
        case AlgorithmState::FOUND_PATH:
            color = {0,255,0};
            break;
        case AlgorithmState::NO_PATH:
            color = {255,0,0};
            break;
        }
        return color;
    }


    void printLargeText(std::string text, double factor)
    {
        ImGui::SetWindowFontScale(static_cast<float>(factor));
        ImGui::Text(text.c_str());
        ImGui::SetWindowFontScale(1);
    }

    void showStatistic(Pathfinding::Datastructures::PathfinderCache * cache)
    {
        auto nodesExpandedTotal = std::accumulate(cache->nodesExpandedAll.begin(), cache->nodesExpandedAll.end(), 0);
        auto average = nodesExpandedTotal / cache->nodesExpandedAll.size();
        auto maxNodesExpanded = std::max_element(cache->nodesExpandedAll.begin(), cache->nodesExpandedAll.end());
        ImGui::Text(std::format("Nodes expaneded total: {}", std::to_string(nodesExpandedTotal)).c_str());
        ImGui::Text(std::format("Nodex expanded on each step(avg) {}", std::to_string(average)).c_str());
        ImGui::Text(std::format("Max number of nodes expanded: {}", std::to_string(*maxNodesExpanded)).c_str());
    }
}