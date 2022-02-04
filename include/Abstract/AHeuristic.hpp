#ifndef A2FF12F1_AB2C_4E7B_B494_69F7A2D38BEE
#define A2FF12F1_AB2C_4E7B_B494_69F7A2D38BEE

#include <cstdint>

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    class AHeuristic
    {
    private:
        using PDNode = Pathfinding::Datastructures::Node;

    public:
        virtual double calculate(const PDNode *from, const PDNode *to) = 0;
        virtual ~AHeuristic() = default;
    };
}

#endif /* A2FF12F1_AB2C_4E7B_B494_69F7A2D38BEE */
