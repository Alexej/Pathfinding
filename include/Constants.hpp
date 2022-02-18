#ifndef A2338B5A_9164_4556_99CB_AA1F92239E7A
#define A2338B5A_9164_4556_99CB_AA1F92239E7A

#include <array>
#include <filesystem>
#include <SFML/Window/Event.hpp>

namespace Pathfinding::Constants
{

    // System
    constexpr auto ROOT_DIR_NAME = "Pathfinding";
    // Strings
    constexpr auto APPLICATION_TITLE = "Pathfinding";

    // Dimension
    constexpr int32_t GRID_FIELD_WIDTH = 800;
    constexpr int32_t GRID_FIELD_HEIGHT = 800;
    constexpr int32_t MENU_WIDTH = 300;
    constexpr int32_t NUMBER_OF_NODES_FOR_RENDER_INFO = 100;
    constexpr int32_t APPLICATION_WINDOW_WIDTH = GRID_FIELD_WIDTH + MENU_WIDTH;

    // Colors:
    constexpr std::array<uint8_t, 3> FREE_NODE_COLOR{150, 160, 180};
    constexpr std::array<uint8_t, 3> FRONTIER_NODE_COLOR{148, 0, 104};
    constexpr std::array<uint8_t, 3> VISITED_NODE_COLOR{100, 100, 150};
    constexpr std::array<uint8_t, 3> BLOCKED_NODE_COLOR{0, 0, 0};
    constexpr std::array<uint8_t, 3> START_NODE_COLOR{255, 0, 0};
    constexpr std::array<uint8_t, 3> GOAL_NODE_COLOR{255, 255, 0};
    constexpr std::array<uint8_t, 3> PATH_NODE_COLOR{0, 255, 0};
    constexpr std::array<uint8_t, 3> RECALCULATED_NODE_COLOR{255, 54, 124};

    constexpr std::array<uint8_t, 3> NODE_OUTLINE_COLOR{255, 255, 255};
    constexpr std::array<uint8_t, 3> NODE_INFO_COLOR{0, 0, 0};

    constexpr std::size_t RED = 0;
    constexpr std::size_t GREEN = 1;
    constexpr std::size_t BLUE = 2;

    constexpr uint8_t COLOR_CHANGE_DIFF = 5;

    // Rendering
    constexpr auto NODE_OUTLINE_THICKNESS = 1.0f;
    constexpr auto NODE_INFO_OFFSET = 8.0f;
    constexpr auto NODE_INFO_TEXT_SIZE = 13;

    // Events
    // ! change to enums and move to Events class
    constexpr auto EVENT_ONLY = true;
    constexpr auto EVENT_AND_KEY = false;
    constexpr sf::Mouse::Button NO_MOUSE_BUTTON = sf::Mouse::Left;
}

#endif /* A2338B5A_9164_4556_99CB_AA1F92239E7A */
