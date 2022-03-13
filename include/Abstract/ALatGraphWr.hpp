#ifndef D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F
#define D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F

#include <memory>
#include <vector>

#include "Vec2.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph;
    class ALatGraphWr
    {
    private:
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
    public:
        explicit ALatGraphWr(std::shared_ptr<ILatticeGraph> latGraphSPtr_)
        : latGraphSPtr(latGraphSPtr_) {}

        virtual void setGoal(PDVec2i location) = 0;

        virtual void setStart(PDVec2i location, bool dontSetStarState = false) = 0;

        virtual const PDNode *startNode() const = 0;

        virtual const PDNode *goalNode() const = 0;

        virtual PDNode *startNode() = 0;

        virtual PDNode *goalNode() = 0;

        virtual void resize(int32_t height, int32_t width) = 0;

        virtual ~ALatGraphWr() = default;

    public:
        std::shared_ptr<ILatticeGraph> latGraphSPtr = nullptr;
    };
}

#endif /* D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F */
