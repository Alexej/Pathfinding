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
    private:
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDNodeState = Pathfinding::Datastructures::NodeState;
    public:
        explicit ALatGraphWr(std::shared_ptr<ILatticeGraph> latGraphSPtr_)
        : latGraphSPtr(latGraphSPtr_) {}

        virtual void setGoal(PDVec2i location) = 0;

        virtual void setStart(PDVec2i location) = 0;

        virtual const PDNode * startNode() const = 0;

        virtual const PDNode * goalNode() const = 0;

        virtual PDNode *startNode() = 0;

        virtual PDNode *goalNode() = 0;

        virtual void resize(int32_t height, int32_t width) = 0;

        virtual void reset() = 0;

        virtual void changeNodeStateWhenNodeFreeOrVisited(PDNode *node, PDNodeState newState) = 0;

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
