#ifndef A575C67C_CEFC_444F_B4F0_7B7D6E5C2508
#define A575C67C_CEFC_444F_B4F0_7B7D6E5C2508

#include <functional>

namespace Pathfinding::Gui
{
    struct MenuCallBacks
    {
        std::function<void(int32_t)> numberOfNodesChangedCallBack = nullptr;
        std::function<void(void)> startCallBack = nullptr;
        std::function<void(void)> resetCallback = nullptr;
        std::function<void(void)> stepCallBack = nullptr;
        std::function<void(void)> randomGraphCallBack = nullptr;
        std::function<void(void)> mazeGraphCallBack = nullptr;
    };
}

#endif /* A575C67C_CEFC_444F_B4F0_7B7D6E5C2508 */
