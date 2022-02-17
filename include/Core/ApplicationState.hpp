#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Core
{
    enum class State
    {
        READY,
        SEARCHING,
        DONE,
        NO_PATH
    };
    class ApplicationState
    {
    private:
        using PDNode = Pathfinding::Datastructures::Node;

    public:
        ApplicationState();
        bool showNodeInfo() const;
        void enableNodeInfo();
        void disableNodeInfo();
        void setState(State state);
        State currentState() const;
        GraphDimension &dimension();
        const PDNode *nodeUnderCursor() const;
        void setNodeUnderCursor(const PDNode *node);
        void enableAutoStep();
        void disableAutoStep();
        bool autoStep() const;
        bool showPathLines() const;
        bool showPath() const;
        void enablePath();
        void disablePath();
        void enablePathLines();
        void disablePathLines();
        void setAlgorithmStepSpeed(AlgorithmStepSpeed algoStepSpeed);
        AlgorithmStepSpeed & algorithmStepSpeed();
    private:
        GraphDimension dim;
        AlgorithmStepSpeed stepSpeed;
        State currentState_;
        bool showNodeInfo_;
        bool stateChanged;
        const PDNode *nodeUnderCursor_ = nullptr;
        bool autoStep_;
        bool path_;
        bool pathLines_;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
