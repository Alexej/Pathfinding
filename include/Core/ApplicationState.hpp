#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"
#include "IApplicationState.hpp"

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
    class ApplicationState final : public Pathfinding::Abstract::IApplicationState
    {
    private:
        using PDNode = Pathfinding::Datastructures::Node;
    public:
        ApplicationState() = default;
        ApplicationState(GraphDimension dimension, AlgorithmStepSpeed stepSpeed);
        bool showNodeInfo() const override;
        void enableNodeInfo() override;
        void disableNodeInfo() override;
        void setState(State state) override;
        State currentState() const override;
        const PDNode *nodeUnderCursor() const override;
        void setNodeUnderCursor(const PDNode *node) override;
        void enableAutoStep() override;
        void disableAutoStep() override;
        bool autoStep() const override;
        bool showPathLines() const override;
        bool showPath() const override;
        void enablePath() override;
        void disablePath() override;
        void enablePathLines() override;
        void disablePathLines() override;
        GraphDimension &dimension() override;
        AlgorithmStepSpeed & algorithmStepSpeed() override;
    private:
        GraphDimension dimension_;
        AlgorithmStepSpeed stepSpeed_;
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
