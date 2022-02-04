#ifndef B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0
#define B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0

#include "AHeuristic.hpp"

namespace Pathfinding::Datastrucutres
{
    struct Node;
}

namespace Pathfinding::Algorithms
{
    class DiagonalHeuristic final : public Pathfinding::Abstract::AHeuristic
    {
    private:
        using PDNode = Pathfinding::Datastructures::Node;

    public:
        double calculate(const PDNode *from, const PDNode *to) override;
    };
}

#endif /* B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0 */
