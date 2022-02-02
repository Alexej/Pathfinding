#ifndef AB283A7C_08BA_4585_A98A_76E2641DDE71
#define AB283A7C_08BA_4585_A98A_76E2641DDE71

#include "PriorityQueue.hpp"
#include <memory>
#include <unordered_set>

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
    struct Key;
    enum class NodeState;
}

namespace Pathfinding::Abstract
{
    class AHeuristic;
}

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::PriorityQueue;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::Key;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Abstract::AHeuristic;

    class DStarLite
    {
        public:
            DStarLite() = default;
            explicit DStarLite(LatticeGraph * graph);
            void initialize();
            void computeShortestPath();
            void setHeuristic(std::shared_ptr<AHeuristic> cost);
            void setPathInGraph();
            void computePath();
            void reset();
            void moveAgent();
            void clearPathInGraph();
            void addChangedNode(Node * node);
        private:
            void UpdateVertex(Node * node);
            Key calculateKey(Node * node);
            std::vector<Node *> neighbors(Node * node);
            std::pair<double, Node *> getMinCG(Node * u);
            Node * popFromQueueAndUpdateState();
            void insertIntoQueueAndUpdateState(Node * node);
            void removeFromQUeueAndUpdateState(Node * node);
            void updateNeighbors(Node * node);
            void changeState(Node * node, NodeState state);
            void moveStartToNextInPath();
        private:    
            LatticeGraph * graphPtr = nullptr;
            Node * sStart = nullptr;
            Node * sLast = nullptr;
            PriorityQueue U;
            double kM = 0;
            std::shared_ptr<AHeuristic> heuristicPtr = nullptr;
            std::vector<Node *> currentPath;
            std::unordered_set<Node *> nodesChanged;
    };
}

#endif /* AB283A7C_08BA_4585_A98A_76E2641DDE71 */
