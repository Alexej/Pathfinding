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

    void HelpMarker(const char* desc);

    auto vector_getter(void *vec, int idx, const char **out_text);

    bool custom_combo(const char *label, int *currIndex, std::vector<std::string> &values);
}


namespace Pathfinding::Core { enum class AlgorithmState; }
namespace Pathfinding::Datastructures { struct PathfinderCache; }
namespace Pathfinding::Datastructures { enum class NodeState; }


namespace Pathfinding::Helpers
{
    std::string mapNodeStateToText(Pathfinding::Datastructures::NodeState state);

    std::string mapStateToText(Pathfinding::Core::AlgorithmState state);

    void printLargeText(std::string text, double factor);

    void showStatistic(Pathfinding::Datastructures::PathfinderCache * cache);

    std::array<uint32_t, 3> getStateColor(Pathfinding::Core::AlgorithmState state);
}

#endif /* F5A37FC3_5BE4_4424_83EB_BB7A269732B3 */
