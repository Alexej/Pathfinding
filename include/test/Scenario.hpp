#ifndef D3F2A047_29CD_4F32_92D7_3DE8488F07E3
#define D3F2A047_29CD_4F32_92D7_3DE8488F07E3

#include <string>
#include <vector>

#include "Vec2.hpp"
#include "ApplicationState.hpp"

namespace Pathfinding::Test
{
    enum class CommandsKeyWords {BLOCK, STEP, CLEAR};
    struct Scenario
    {
        public:
            std::string name;
            Pathfinding::Datastructures::Vec2i size;
            Pathfinding::Datastructures::Vec2i start;
            Pathfinding::Datastructures::Vec2i goal;
            std::vector<std::pair<CommandsKeyWords, Pathfinding::Datastructures::Vec2i>> commands;
            Pathfinding::Core::AlgorithmState result;
    };
}

#endif /* D3F2A047_29CD_4F32_92D7_3DE8488F07E3 */
