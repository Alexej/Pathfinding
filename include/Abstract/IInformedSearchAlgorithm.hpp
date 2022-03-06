#ifndef BA7E9D7D_1EA8_4941_95D3_964B40B50B1F
#define BA7E9D7D_1EA8_4941_95D3_964B40B50B1F

namespace Pathfinding::Abstract
{
    class IHeuristic;
    class ICostFunction;
    class IInformedSearchAlgorithm
    {
        public:
            virtual void setHeuristic(std::unique_ptr<IHeuristic> cost) = 0;
            virtual void setCostFunction(std::unique_ptr<ICostFunction> cost) = 0;
            virtual ~IInformedSearchAlgorithm() = default;
    };
}

#endif /* BA7E9D7D_1EA8_4941_95D3_964B40B50B1F */
