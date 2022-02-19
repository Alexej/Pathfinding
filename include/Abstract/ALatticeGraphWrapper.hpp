#ifndef D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F
#define D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F

#include <memory>
#include <vector>
#include "Vector2.hpp"

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    class ILatticeGraph;
    class ALatticeGraphWrapper
    {
    private:
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;

    public:
        explicit ALatticeGraphWrapper(std::unique_ptr<ILatticeGraph> latGraphUPtr_)
            : latGraphUPtr(std::move(latGraphUPtr_))
        {
        }

        virtual void resize(int32_t height, int32_t width) = 0;
        virtual std::vector<PDNode *> neighbors(PDNode *node) = 0;
        virtual const PDNode *startNode() const = 0;
        virtual const PDNode *goalNode() const = 0;
        virtual PDNode *startNode() = 0;
        virtual PDNode *goalNode() = 0;
        virtual void setGoal(PDVec2i location) = 0;
        virtual void setStart(PDVec2i location) = 0;
        virtual void blockNode(PDVec2i location) = 0;
        virtual void clearNode(PDVec2i location) = 0;
        virtual void resetEndpoints() = 0;
        virtual bool inBounds(PDVec2i location) const = 0;
        virtual PDNode *node(PDVec2i location) = 0;
        virtual const PDNode *node(PDVec2i location) const = 0;
        virtual void initRandomGraph() = 0;
        virtual std::size_t width() const = 0;
        virtual std::size_t height() const = 0;
        virtual ~ALatticeGraphWrapper() = default;

    protected:
        std::unique_ptr<ILatticeGraph> latGraphUPtr = nullptr;
    };
}

#endif /* D1C74DCC_EBAD_4301_B93F_C5E9BBD07D2F */
