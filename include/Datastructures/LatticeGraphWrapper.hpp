#ifndef CA4EA78A_B93E_4F56_B8F5_589374FB83C4
#define CA4EA78A_B93E_4F56_B8F5_589374FB83C4

#include <memory>

#include "ALatGraphWr.hpp"
#include "ILatticeGraph.hpp"
#include "Vec2.hpp"
#include <optional>

namespace Pathfinding::Abstract { class IMazeGenerator; }

namespace Pathfinding::Datastructures
{
    struct Node;
    class LatticeGraphWrapper final : public Pathfinding::Abstract::ALatGraphWr
    {
        private:
            using PAIMazeGenerator = Pathfinding::Abstract::IMazeGenerator;
            using PAILatticeGraph = Pathfinding::Abstract::ILatticeGraph;
        public:
            LatticeGraphWrapper(std::shared_ptr<PAILatticeGraph> latticeGraphUPtr);

            const Node * startNode() const override;

            const Node * goalNode() const override;

            Node *startNode() override;

            Node *goalNode() override;

            void resize(int32_t height, int32_t width);

            void setGoal(Vec2i location) override;

            void setStart(Vec2i location) override;

            void changeNodeStateWhenNodeFreeOrVisited(Node *node, NodeState newState) override;

            void removeEndpointsFromGraph() override;
        
            void addEndpointsToGraph() override;

            void reset() override;

        private:
            void resetEndpoints();

            std::optional<Node *> 
            getFreeNodeFrom3By3(Node * node);

            void setEndpointsToNullPtr();

            bool endpointsInitialized() const;
            
        private:
            Node *goalNodePtr;
            Node *startNodePtr;
    };
}

#endif /* CA4EA78A_B93E_4F56_B8F5_589374FB83C4 */
