#ifndef CA4EA78A_B93E_4F56_B8F5_589374FB83C4
#define CA4EA78A_B93E_4F56_B8F5_589374FB83C4

#include <memory>

#include "ALatticeGraphWrapper.hpp"
#include "ILatticeGraph.hpp"
#include "Vec2.hpp"


namespace Pathfinding::Datastructures
{
    struct Node;
    class LatticeGraphWrapper final : public Pathfinding::Abstract::ALatticeGraphWrapper
    {
        private:
            using PAILatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        public:
            LatticeGraphWrapper(std::unique_ptr<PAILatticeGraph> latticeGraphUPtr);

            const Node *startNode() const override;

            const Node *goalNode() const override;

            Node *startNode() override;

            Node *goalNode() override;

            Node *node(Vec2i location) override { return &latGraphUPtr->operator[](location.height)[location.width]; }

            const Node *node(Vec2i location) const override { return &latGraphUPtr->operator[](location.height)[location.width]; }

            bool inBounds(Vec2i location) const override;

            std::size_t width() const override;

            std::size_t height() const override;

            void resize(int32_t height, int32_t width) override;

            void setGoal(Vec2i location) override;

            void setStart(Vec2i location, bool dontSetStarState = false) override;

        private:
            void resetEndpoints();
            
        private:
            Node *goalNodePtr;
            Node *startNodePtr;
    };
}

#endif /* CA4EA78A_B93E_4F56_B8F5_589374FB83C4 */
