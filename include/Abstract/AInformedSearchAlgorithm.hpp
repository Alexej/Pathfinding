#ifndef BA7E9D7D_1EA8_4941_95D3_964B40B50B1F
#define BA7E9D7D_1EA8_4941_95D3_964B40B50B1F

#include <memory>

#include "IHeuristic.hpp"
#include "ICostFunction.hpp"

namespace Pathfinding::Abstract
{
    class AInformedSearchAlgorithm
    {
        public:
            void setHeuristic(std::unique_ptr<IHeuristic> heuristic_)
            {
                heuristicUPtr = std::move(heuristic_);
            };
            
            void setCostFunction(std::unique_ptr<ICostFunction> cost_)
            {
                costUPtr = std::move(cost_);
            };
            
            virtual ~AInformedSearchAlgorithm() = default;
            
        protected:
            std::unique_ptr<IHeuristic> heuristicUPtr;
            std::unique_ptr<ICostFunction> costUPtr;
    };
}

#endif /* BA7E9D7D_1EA8_4941_95D3_964B40B50B1F */
