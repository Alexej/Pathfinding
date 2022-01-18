#ifndef C5296213_C3E3_4DA5_8D55_7E6FB12E90D5
#define C5296213_C3E3_4DA5_8D55_7E6FB12E90D5

#include <tuple>

namespace Pathfinding::Datastructures
{
    struct Key
    {
        Key() = default;
        Key(int32_t k1_, int32_t k2_) : k1(k1_), k2(k2_) {}
        int32_t k1 = 123;
        int32_t k2 = 321;
    };

    [[nodiscard]] bool operator<(const Key & lhs, const Key & rhs);
    [[nodiscard]] bool operator>(const Key & lhs, const Key & rhs);
    [[nodiscard]] bool operator==(const Key & lhs, const Key & rhs);
}

#endif /* C5296213_C3E3_4DA5_8D55_7E6FB12E90D5 */
