#ifndef D7417BFD_FC62_4265_AFFB_8561A40A7A6F
#define D7417BFD_FC62_4265_AFFB_8561A40A7A6F


namespace Pathfinding::Core
{
    enum class State;
}

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Core
{
    class AlgorithmStepSpeed;
    class GraphDimension;
}

namespace Pathfinding::Abstract
{
    class IApplicationState
    {
        private:
            using PCState = Pathfinding::Core::State;
            using PDNode = Pathfinding::Datastructures::Node;
            using PDAlgorithmStepSpeed = Pathfinding::Core::AlgorithmStepSpeed;
            using PDGraphDimension = Pathfinding::Core::GraphDimension;
        public: 
            virtual bool showNodeInfo() const = 0;
            virtual void enableNodeInfo() = 0;
            virtual void disableNodeInfo() = 0;
            virtual void setState(PCState state) = 0;
            virtual PCState currentState() const = 0;
            virtual const PDNode *nodeUnderCursor() const = 0;
            virtual void setNodeUnderCursor(const PDNode *node) = 0;
            virtual void enableAutoStep() = 0;
            virtual void disableAutoStep() = 0;
            virtual bool autoStep() const = 0;
            virtual bool showPathLines() const = 0;
            virtual bool showPath() const = 0;
            virtual void enablePath() = 0;
            virtual void disablePath() = 0;
            virtual void enablePathLines() = 0;
            virtual void disablePathLines() = 0;
            virtual PDGraphDimension &dimension() = 0;
            virtual PDAlgorithmStepSpeed & algorithmStepSpeed() = 0;
            virtual ~IApplicationState() = default;

    };
}

#endif /* D7417BFD_FC62_4265_AFFB_8561A40A7A6F */
