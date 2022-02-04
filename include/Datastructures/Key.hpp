#ifndef C5296213_C3E3_4DA5_8D55_7E6FB12E90D5
#define C5296213_C3E3_4DA5_8D55_7E6FB12E90D5

#include <tuple>

namespace Pathfinding::Datastructures
{
    /**
     * @brief
     * The first component of the keys  k1 corresponds
     * directly to the f-values f(s) := g*(s) + h(s, sGoal) used by A*
     * because both the g-values and rhs values of LPA* correspond to the g values of A*
     *
     * The second component of the keys k2 corresponds to the g values of A*.
     *
     * k1 = min(g(s), rhs(s) + h(s, sGoal)) //  f in A*
     * k2 = min(g(s), rhs(s))  // g in A*
     */
    struct Key
    {
        Key() = default;
        Key(double k1_, double k2_) : k1(k1_), k2(k2_) {}
        double k1 = std::numeric_limits<double>::infinity();
        double k2 = std::numeric_limits<double>::infinity();
    };

    bool operator<(const Key &lhs, const Key &rhs);
    bool operator>(const Key &lhs, const Key &rhs);
    bool operator==(const Key &lhs, const Key &rhs);
}

#endif /* C5296213_C3E3_4DA5_8D55_7E6FB12E90D5 */
