#ifndef AB283A7C_08BA_4585_A98A_76E2641DDE71
#define AB283A7C_08BA_4585_A98A_76E2641DDE71

#include <memory>
#include <unordered_set>
#include <functional>

#include "PriorityQueue.hpp"
#include "AIncrementalInformedAlgorithm.hpp"

namespace Pathfinding::Datastructures{ struct Node; }
namespace Pathfinding::Datastructures{ struct Key; }
namespace Pathfinding::Datastructures{ enum class NodeState; }
namespace Pathfinding::Datastructures{ struct PathfinderReturnType; }
namespace Pathfinding::Datastructures{ struct InformedSearchFunctions; }


namespace Pathfinding::Abstract { class IHeuristic; }
namespace Pathfinding::Abstract { class ICostFunction; }

namespace Pathfinding::Algorithms
{
    class DStarLite final : public Pathfinding::Abstract::AIncrementalInformedAlgorithm
    {
    private:
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PDPriorityQueue = Pathfinding::Datastructures::PriorityQueue;
        using PDNode = Pathfinding::Datastructures::Node;
        using PDKey = Pathfinding::Datastructures::Key;
        using PDNodeState = Pathfinding::Datastructures::NodeState;
        using PAIHeuristic = Pathfinding::Abstract::IHeuristic;
        using PAICostFunction = Pathfinding::Abstract::ICostFunction;
        using PDPathfinderReturnType = Pathfinding::Datastructures::PathfinderReturnType;
        using PDInformedSearchFunctions = Pathfinding::Datastructures::InformedSearchFunctions;
    public:
        DStarLite() = default;
        
        DStarLite(std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr, PDInformedSearchFunctions & functions);
        
        void initialize() override;
        
        PDPathfinderReturnType initialRun() override;
        
        PDPathfinderReturnType followingRun() override;
        
        void reset() override;
        
        void addChangedNode(PDNode *node) override;
        
    private:
        PDPathfinderReturnType computePath();
        
        void computeShortestPath();
        
        void UpdateVertex(PDNode *node);
        
        void updateKey(PDNode *node);
        
        std::pair<double, PDNode *> getMinCG(PDNode *u);
        
        PDNode *popFromQueueAndUpdateState();
        
        void insertIntoQueueAndUpdateStateAndKey(PDNode *node);
        
        void removeFromQUeueAndUpdateState(PDNode *node);
        
        void updateNeighbors(PDNode *node);
                
        void moveStartToNextInPath();
        
        bool computeShortestPathExitCondition();
        
        void insertIntoQueueAndUpdateKey(PDNode * node);
        
        double costThisFar(const PDNode * u, const PDNode * neighbor);

        PDKey calculateKey(const PDNode *s) const;
        
    private:
        PDNode *sStart = nullptr;
        PDNode *sLast = nullptr;
        PDPriorityQueue U;
        std::unordered_set<PDNode *> nodesChanged;
        std::vector<const PDNode *> nodexExpanded;
        double kM = 0;
    };
}

#endif /* AB283A7C_08BA_4585_A98A_76E2641DDE71 */
