#ifndef A2338B5A_9164_4556_99CB_AA1F92239E7A
#define A2338B5A_9164_4556_99CB_AA1F92239E7A

#include <array>
#include <filesystem>

namespace Pathfinding::Constants
{
    constexpr auto APPLICATION_TITLE = "Pathfinding";

    //Dimension
    constexpr int32_t NUMBER_OF_NODES_VERTICAL = 10;
    constexpr int32_t NUMBER_OF_NODES_HORIZONTAL = 10;
    constexpr int32_t NODE_SIDE_LENGTH = 80;
    constexpr int32_t MINIMUM_NODE_SIDE_LENGHT_FOR_NODE_INFO = 80;

    constexpr int32_t MENU_WIDTH = 400;

    // Colors:
    constexpr std::array<uint8_t, 3> FREE_NODE_COLOR{150, 160, 180};
    constexpr std::array<uint8_t, 3> FRONTIER_NODE_COLOR{0, 255, 0};
    constexpr std::array<uint8_t, 3> BLOCKED_NODE_COLOR{0, 0, 0};
    constexpr std::array<uint8_t, 3> VISITED_NODE_COLOR{255, 0, 255};
    constexpr std::array<uint8_t, 3> START_NODE_COLOR{255, 0, 0};
    constexpr std::array<uint8_t, 3> GOAL_NODE_COLOR{255, 255, 0};

    constexpr std::array<uint8_t, 3> NODE_OUTLINE_COLOR{255, 255, 255};
    constexpr std::array<uint8_t, 3> NODE_INFO_COLOR{0, 0, 0};

    constexpr std::size_t RED = 0;
    constexpr std::size_t GREEN = 1;
    constexpr std::size_t BLUE = 2;

    //Rendering
    constexpr auto NODE_OUTLINE_THICKNESS = 1.0f;
    constexpr auto NODE_INFO_OFFSET = 8.0f;

}

#endif /* A2338B5A_9164_4556_99CB_AA1F92239E7A */
