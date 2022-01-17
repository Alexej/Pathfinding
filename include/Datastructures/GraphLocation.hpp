#ifndef C71A173D_A9A7_4ABC_B640_D4C5497B6103
#define C71A173D_A9A7_4ABC_B640_D4C5497B6103


#include <compare>
#include <stdint.h>

namespace Pathfinding::Datastructures
{
    struct GraphLocation
    {
        GraphLocation() = default;
        GraphLocation(int32_t height_, int32_t width_) : height(height_), width(width_) {}
        int32_t height = 0;
        int32_t width = 0;
        auto operator<=>(const GraphLocation &) const = default;
    };
}

#endif /* C71A173D_A9A7_4ABC_B640_D4C5497B6103 */
