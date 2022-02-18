#ifndef AB283A7C_08BA_4585_A98A_76E2641DDE71
#define AB283A7C_08BA_4585_A98A_76E2641DDE71

#include <memory>
#include <unordered_set>
#include <functional>
#include "PriorityQueue.hpp"
#include "IDStarLite.hpp"

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
    class DStarLite final : public Pathfinding::Abstract::IDStarLite
    {
    private:
        using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PDPriorityQueue = Pathfinding::Datastructures::PriorityQueue;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDKey = Pathfinding::Datastructures::Key;
        using PDNodeState = Pathfinding::Datastructures::NodeState;
        using PAAHeuristic = Pathfinding::Abstract::AHeuristic;
    public:
        DStarLite() = default;
        explicit DStarLite(PDLatticeGraph *graph);
        void addDoneCallBack(std::function<void(void)> callBack) override;
        void addNoPathCallBack(std::function<void(void)> callBack) override;
        void initialize() override;
        void setHeuristic(std::shared_ptr<PAAHeuristic> cost) override;
        void computePath() override;
        void reset() override;
        void moveStart() override;
        void addChangedNode(PDNode *node) override;
        std::vector<PDNode *> path() const override;
        void initialRun() override;
    private:
        void computeShortestPath();
        void UpdateVertex(PDNode *node);
        PDKey calculateKey(PDNode *node);
        std::pair<double, PDNode *> getMinCG(PDNode *u);
        PDNode *popFromQueueAndUpdateState();
        void insertIntoQueueAndUpdateState(PDNode *node);
        void removeFromQUeueAndUpdateState(PDNode *node);
        void updateNeighbors(PDNode *node);
        void changeNodeState(PDNode *node, PDNodeState state);
        void moveStartToNextInPath();
        bool computeShortestPathExitCondition();
        void insertIntoQueueAndUpdateKey(PDNode * node);
    private:
        PDLatticeGraph *graphPtr = nullptr;
        PDNode *sStart = nullptr;
        PDNode *sLast = nullptr;
        PDPriorityQueue U;
        std::shared_ptr<PAAHeuristic> heuristicPtr = nullptr;
        std::vector<PDNode *> currentPath;
        std::unordered_set<PDNode *> nodesChanged;
        std::function<void(void)> doneCallBack_;
        std::function<void(void)> noPathCallBack_;
        double kM = 0;
    };
}

#endif /* AB283A7C_08BA_4585_A98A_76E2641DDE71 */
