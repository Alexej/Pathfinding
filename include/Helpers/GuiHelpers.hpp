#ifndef F5A37FC3_5BE4_4424_83EB_BB7A269732B3
#define F5A37FC3_5BE4_4424_83EB_BB7A269732B3

#include <string>
#include <vector>

/*
https://eliasdaler.github.io/using-imgui-with-sfml-pt2/#combobox-listbox
*/
namespace ImGui
{
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


namespace Pathfinding::Core
{
    enum class State;
}

namespace Pathfinding::Datastructures
{
    enum class NodeState;
}


namespace Pathfinding::Helpers
{
    std::string mapNodeStateToText(Pathfinding::Datastructures::NodeState state);

    std::string mapStateToText(Pathfinding::Core::State state);

    void printLargeText(std::string text, double factor);
}

#endif /* F5A37FC3_5BE4_4424_83EB_BB7A269732B3 */
