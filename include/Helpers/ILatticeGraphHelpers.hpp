#ifndef A8F39E2A_B87B_43DF_A67F_993CBD86DC47
#define A8F39E2A_B87B_43DF_A67F_993CBD86DC47

#include <vector>
#include <memory>
#include <functional>

#include "Vec2.hpp"
#include "Node.hpp"
#include "ILatticeGraph.hpp"


namespace Pathfinding::Core { class RandomIntegers; }
namespace Pathfinding::Core { struct ApplicationState; }


namespace Pathfinding::Helpers
{
    class ILatticeGraphHelpers
    {
    private:
        using PAILatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PCRandomIntegers = Pathfinding::Core::RandomIntegers;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
    public:
        static std::vector<PDNode *> neighbors(PAILatticeGraph & iLatticeGraph, const PDNode *node);

        static std::vector<const PDNode *> neighborsConst(PAILatticeGraph & iLatticeGraph, const PDNode *node);
        
        static void initRandomGraph(PAILatticeGraph & iLatticeGraph, PCRandomIntegers & ri);
        
        static void blockNode(PAILatticeGraph & iLatticeGraph, PDVec2i location);
        
        static void clearNode(PAILatticeGraph & iLatticeGraph, PDVec2i location);

    };

    template<typename Function>
    void iterateOverLatticeGraphConst(const Pathfinding::Abstract::ILatticeGraph & ilatticeGraph, Function func)
    {
        for (int32_t h = 0; h < ilatticeGraph.height(); ++h)
        {
            for (int32_t w = 0; w < ilatticeGraph.width(); ++w)
            {
                func(ilatticeGraph.node(Pathfinding::Datastructures::Vec2i(h, w)), h, w);
            }
        }
    }

    template<typename Function>
    void iterateOverLatticeGraph(Pathfinding::Abstract::ILatticeGraph & ilatticeGraph, Function func)
    {
        for (int32_t h = 0; h < ilatticeGraph.height(); ++h)
        {
            for (int32_t w = 0; w < ilatticeGraph.width(); ++w)
            {
                func(ilatticeGraph.node(Pathfinding::Datastructures::Vec2i(h, w)), h, w);
            }
        }
    }                         
}

#endif /* A8F39E2A_B87B_43DF_A67F_993CBD86DC47 */
