#ifndef AB283A7C_08BA_4585_A98A_76E2641DDE71
#define AB283A7C_08BA_4585_A98A_76E2641DDE71

#include "PriorityQueue.hpp"
#include <memory>

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
    struct Key;
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
        private:
            void UpdateVertex(Node * node);
            Key calculateKey(Node * node);
            std::vector<Node *> succ(Node * node);
            std::pair<int64_t, Node *> getMinCG(Node * u);
            void clearPathInGraph();
        private:    
            LatticeGraph * graphPtr;
            Node * sLast;
            PriorityQueue U;
            int64_t kM;
            std::shared_ptr<AHeuristic> heuristicPtr = nullptr;
            std::vector<Node *> currentPath;
    };
}

#endif /* AB283A7C_08BA_4585_A98A_76E2641DDE71 */
