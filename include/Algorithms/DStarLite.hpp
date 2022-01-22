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
    class ACost;
    class AHeuristic;
}

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::PriorityQueue;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::Key;
    using Pathfinding::Abstract::ACost;
    using Pathfinding::Abstract::AHeuristic;

    class DStarLite
    {
        public:
            DStarLite() = default;
            explicit DStarLite(LatticeGraph * graph);
            void initialize();
            void UpdateVertex(Node * node);
            void computeShortestPath();
            void setCost(std::shared_ptr<ACost> heuristicPtr);
            void setHeuristic(std::shared_ptr<AHeuristic> cost);
        private:
            Key calculateKey(Node * node);
            std::vector<Node *> succ(Node * node);
            int32_t getMinCG(Node * s);
        private:    
            LatticeGraph * graphPtr;
            Node * sLast;
            PriorityQueue U;
            int32_t kM;
            std::shared_ptr<AHeuristic> heuristicPtr;
            std::shared_ptr<ACost> costPtr;
    };
}

#endif /* AB283A7C_08BA_4585_A98A_76E2641DDE71 */
