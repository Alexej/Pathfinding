#ifndef D3F2A047_29CD_4F32_92D7_3DE8488F07E3
#define D3F2A047_29CD_4F32_92D7_3DE8488F07E3

#include <string>
#include <vector>
#include "Vec2.hpp"
#include "ApplicationState.hpp"

namespace Pathfinding::Test
{
    enum class CommandsKeyWords {BLOCK, STEP};
    struct Scenario
    {
        private:
            using PDVec2i = Pathfinding::Datastructures::Vec2i;
            using PCState = Pathfinding::Core::State;
            using PCApplicationState = Pathfinding::Core::State;
        public:
            std::string name;
            PDVec2i size;
            PDVec2i start;
            PDVec2i goal;
            std::vector<std::pair<CommandsKeyWords, PDVec2i>> commands;
            PCApplicationState result;
    };
}

#endif /* D3F2A047_29CD_4F32_92D7_3DE8488F07E3 */
