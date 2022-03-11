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
    using Pathfinding::Core::State;
    
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

    std::string mapStateToText(State state)
    {
        std::string str;
        switch (state)
        {
        case State::READY:
            str = "READY";
            break;
        case State::SEARCHING:
            str = "SEARCHING";
            break;
        case State::DONE:
            str = "DONE";
            break;
        case State::NO_PATH:
            str = "NO_PATH";
            break;
        }
        return str;
    }

    std::array<uint32_t, 3> getStateColor(Pathfinding::Core::State state)
    {
        std::array<uint32_t, 3> color;
        switch (state)
        {
        case State::READY:
            color = {255,255,255};
            break;
        case State::SEARCHING:
            color = {90,60,160};
            break;
        case State::DONE:
            color = {0,255,0};
            break;
        case State::NO_PATH:
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