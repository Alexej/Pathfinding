#ifndef CA4EA78A_B93E_4F56_B8F5_589374FB83C4
#define CA4EA78A_B93E_4F56_B8F5_589374FB83C4

#include <memory>

#include "ALatGraphWr.hpp"
#include "ILatticeGraph.hpp"
#include "Vec2.hpp"


namespace Pathfinding::Datastructures
{
    struct Node;
    class LatticeGraphWrapper final : public Pathfinding::Abstract::ALatGraphWr
    {
        private:
            using PAILatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        public:
            LatticeGraphWrapper(std::shared_ptr<PAILatticeGraph> latticeGraphUPtr);

            const Node *startNode() const override;

            const Node *goalNode() const override;

            Node *startNode() override;

            Node *goalNode() override;

            void resize(int32_t height, int32_t width);

            void setGoal(Vec2i location) override;

            void setStart(Vec2i location) override;

            void changeNodeState(Node *node, NodeState newState) override;

        private:
            void resetEndpoints();
            
        private:
            Node *goalNodePtr;
            Node *startNodePtr;
    };
}

#endif /* CA4EA78A_B93E_4F56_B8F5_589374FB83C4 */
