#ifndef AB283A7C_08BA_4585_A98A_76E2641DDE71
#define AB283A7C_08BA_4585_A98A_76E2641DDE71

#include "PriorityQueue.hpp"

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
    struct Key;
}

namespace Pathfinding::Algorithms
{
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Datastructures::PriorityQueue;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::Key;
    class DStarLite
    {
        public:
            explicit DStarLite(LatticeGraph * graph);
            void initialize();
            void UpdateVertex(Node * node);
            void computeShortestPath();
        private:
            Key calculateKey(Node * node);
            std::vector<Node *> succ(Node * node);
            int32_t getMinCG(Node * s);
        private:    
            LatticeGraph * graphPtr;
            Node * sLast;
            PriorityQueue U;
            int32_t kM;
    };
}

#endif /* AB283A7C_08BA_4585_A98A_76E2641DDE71 */
