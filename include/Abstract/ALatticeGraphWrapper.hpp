#ifndef D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F
#define D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F

#include <memory>
#include <vector>

#include "Vec2.hpp"
#include "Resizable2DArray.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Abstract
{
    class ILatticeGraph;
    class ALatticeGraphWrapper : public Resizable2DArray
    {
    private:
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
    public:
        explicit ALatticeGraphWrapper(std::unique_ptr<ILatticeGraph> latGraphUPtr_)
            : latGraphUPtr(std::move(latGraphUPtr_)) {}

        virtual void setGoal(PDVec2i location) = 0;

        virtual void setStart(PDVec2i location, bool dontSetStarState = false) = 0;

        virtual const PDNode *startNode() const = 0;

        virtual const PDNode *goalNode() const = 0;

        virtual PDNode *startNode() = 0;

        virtual PDNode *goalNode() = 0;

        virtual PDNode *node(PDVec2i location) = 0;

        virtual const PDNode *node(PDVec2i location) const = 0;

        virtual bool inBounds(PDVec2i location) const = 0;

        virtual ~ALatticeGraphWrapper() = default;

    protected:
        std::unique_ptr<ILatticeGraph> latGraphUPtr = nullptr;
    };
}

#endif /* D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F */
