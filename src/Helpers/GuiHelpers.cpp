#include "GuiHelpers.hpp"


#include <vector>
#include <string>
#include "imgui.h"
#include "ApplicationState.hpp"
#include "Node.hpp"

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

    void printLargeText(std::string text, double factor)
    {
        ImGui::SetWindowFontScale(static_cast<float>(factor));
        ImGui::Text(text.c_str());
        ImGui::SetWindowFontScale(1);
    }
}