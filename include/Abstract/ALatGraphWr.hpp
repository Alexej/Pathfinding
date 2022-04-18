#ifndef D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F
#define D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F

#include <memory>
#include <vector>

#include "Vec2.hpp"

namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Datastructures { enum class NodeState; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph;
    class IMazeGenerator;
    class ALatGraphWr
    {
    public:
        explicit ALatGraphWr(std::shared_ptr<ILatticeGraph> latGraphSPtr_)
        : latGraphSPtr(latGraphSPtr_) {}

        virtual void setGoal(Pathfinding::Datastructures::Vec2i location) = 0;

        virtual void setStart(Pathfinding::Datastructures::Vec2i location) = 0;

        virtual const Pathfinding::Datastructures::Node * startNode() const = 0;

        virtual const Pathfinding::Datastructures::Node * goalNode() const = 0;

        virtual Pathfinding::Datastructures::Node *startNode() = 0;

        virtual Pathfinding::Datastructures::Node *goalNode() = 0;

        virtual void resize(int32_t height, int32_t width) = 0;

        virtual void reset() = 0;

        virtual void changeNodeStateWhenNodeFreeOrVisited(Pathfinding::Datastructures::Node *node, 
                                                          Pathfinding::Datastructures::NodeState newState) = 0;

        virtual void removeEndpointsFromGraph() = 0;
        
        virtual void addEndpointsToGraph() = 0;

        virtual ~ALatGraphWr() = default;

    public:
        bool endpointsSet() const { return endpointsSet_; }
        
    public:
        std::shared_ptr<ILatticeGraph> latGraphSPtr = nullptr;
    protected:
        bool endpointsSet_ = true;
    };
}

#endif /* D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F */
