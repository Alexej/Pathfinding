#ifndef B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0
#define B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0

#include "IHeuristic.hpp"
#include <cstdint>


namespace Pathfinding::Algorithms
{
    class DiagonalHeuristic final : public Pathfinding::Abstract::IHeuristic
    {
    public:
        DiagonalHeuristic(int32_t diagonalMovementCost, int32_t straightMovementCost);
        
        double calculate(const PDNode *from, const PDNode *to) override;
        
    private:
        int32_t diagonalMovementCost;
        int32_t straightMovementCost;
    };
}

#endif /* B392E8BB_7FF6_4DDD_AF6E_9FFBCEC424F0 */
