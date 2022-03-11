#ifndef F5A37FC3_5BE4_4424_83EB_BB7A269732B3
#define F5A37FC3_5BE4_4424_83EB_BB7A269732B3

#include <string>
#include <vector>
#include <array>

#include "imgui.h"

/*
https://eliasdaler.github.io/using-imgui-with-sfml-pt2/#combobox-listbox
*/
namespace ImGui
{

    static void HelpMarker(const char* desc)
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

    static auto vector_getter(void *vec, int idx, const char **out_text)
    {
        auto &vector = *static_cast<std::vector<std::string> *>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size()))
        {
            return false;
        }
        *out_text = vector.at(idx).c_str();
        return true;
    };

    bool custom_combo(const char *label, int *currIndex, std::vector<std::string> &values);
}


namespace Pathfinding::Core { enum class State; }
namespace Pathfinding::Datastructures { struct PathfinderCache; }
namespace Pathfinding::Datastructures { enum class NodeState; }


namespace Pathfinding::Helpers
{
    std::string mapNodeStateToText(Pathfinding::Datastructures::NodeState state);

    std::string mapStateToText(Pathfinding::Core::State state);

    void printLargeText(std::string text, double factor);

    void showStatistic(Pathfinding::Datastructures::PathfinderCache * cache);

    std::array<uint32_t, 3> getStateColor(Pathfinding::Core::State state);
}

#endif /* F5A37FC3_5BE4_4424_83EB_BB7A269732B3 */
