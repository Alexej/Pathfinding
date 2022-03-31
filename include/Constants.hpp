#ifndef A2338B5A_9164_4556_99CB_AA1F92239E7A
#define A2338B5A_9164_4556_99CB_AA1F92239E7A

#include <array>
#include <filesystem>

namespace Pathfinding::Constants
{

    // System
    constexpr auto ROOT_DIR_NAME = "Pathfinding";
    // Strings
    constexpr auto APPLICATION_TITLE = "Pathfinding";

    //Gui
    constexpr int32_t MAX_COST_FACTOR = 5;
    constexpr int32_t MIN_COST_FACTOR = 1;

    // Dimension
    constexpr int32_t GRID_FIELD_WIDTH = 880;
    constexpr int32_t GRID_FIELD_HEIGHT = 880;
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
    constexpr std::array<uint8_t, 3> PATH_NODE_COLOR_2{0, 0, 255};
    constexpr std::array<uint8_t, 3> NODE_OUTLINE_COLOR{255, 255, 255};
    constexpr std::array<uint8_t, 3> NODE_INFO_COLOR{0, 0, 0};
    constexpr std::array<uint8_t, 3> PATH_OUTLINE_COLOR{0, 0, 0};

    constexpr std::size_t RED = 0;
    constexpr std::size_t GREEN = 1;
    constexpr std::size_t BLUE = 2;

    constexpr uint8_t MAX_COLOR_CHANNEL = 255;
    constexpr uint8_t MIN_COLOR_CHANNEL = 0;

    constexpr uint8_t COLOR_CHANGE_DIFF = 5;

    // Rendering
    constexpr auto NODE_OUTLINE_THICKNESS = 1.0f;
    constexpr auto NODE_INFO_OFFSET = 8.0f;
    constexpr auto NODE_INFO_TEXT_SIZE = 13;
    constexpr auto APP_FPS = 60;

    // Events
    // ! change to enums and move to Events class
    constexpr auto EVENT_ONLY = true;
    constexpr auto EVENT_AND_KEY = false;

    // DStar flags
    constexpr auto DONT_SET_START_STATE = true;
    constexpr int32_t DEFAULT_STEP_SPEED = 1000;

    // Random
    constexpr int32_t LOWER_DEFAULT_RANDOM_NUMBER = 0;
    constexpr int32_t UPPER_DEFAULT_RANDOM_NUMBER = 100;


    //Fix later
    static std::vector<std::string> mouseWheelEventStrings = {"Zoom", "EdgeCostFactor"};
}

#endif /* A2338B5A_9164_4556_99CB_AA1F92239E7A */
