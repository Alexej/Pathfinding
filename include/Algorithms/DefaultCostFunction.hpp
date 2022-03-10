#ifndef BA5C9269_941E_4EEA_9444_1C27FCEAE694
#define BA5C9269_941E_4EEA_9444_1C27FCEAE694

#include "ICostFunction.hpp"
#include <cstdint>

namespace Pathfinding::Algorithms
{
    class DefaultCostFunction final : public Pathfinding::Abstract::ICostFunction
    {
        public:
            DefaultCostFunction(int32_t diagonalMovementCost, int32_t straightMovementCost);
            
            double calculate(const PDNode *from, const PDNode *to) override;
            
        private:
            int32_t diagonalMovementCost;
            int32_t straightMovementCost;
    };
}

#endif /* BA5C9269_941E_4EEA_9444_1C27FCEAE694 */
