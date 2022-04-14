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
    std::vector<Pathfinding::Datastructures::Node *> 
    neighbors(Pathfinding::Abstract::ILatticeGraph & iLatticeGraph, const Pathfinding::Datastructures::Node *node);

    std::vector<const Pathfinding::Datastructures::Node *> 
    neighborsConst(Pathfinding::Abstract::ILatticeGraph & iLatticeGraph, const Pathfinding::Datastructures::Node *node);
    
    void  initRandomGraph(Pathfinding::Abstract::ILatticeGraph & iLatticeGraph, Pathfinding::Core::RandomIntegers & ri);
    
    void  blockNode(Pathfinding::Abstract::ILatticeGraph & iLatticeGraph, Pathfinding::Datastructures::Vec2i location);
    
    void  clearNode(Pathfinding::Abstract::ILatticeGraph & iLatticeGraph, Pathfinding::Datastructures::Vec2i location);


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
