#ifndef C1A65457_7BA0_4FCE_A7F7_46AD88CE53F6
#define C1A65457_7BA0_4FCE_A7F7_46AD88CE53F6

#include <memory>

#include "IHeuristic.hpp"
#include "ICostFunction.hpp"

namespace Pathfinding::Datastructures
{
    struct InformedSearchFunctions
    {
        std::unique_ptr<Pathfinding::Abstract::IHeuristic> heuristicUPtr = nullptr;
        std::unique_ptr<Pathfinding::Abstract::ICostFunction> costUPtr = nullptr;
    };
}

#endif /* C1A65457_7BA0_4FCE_A7F7_46AD88CE53F6 */
