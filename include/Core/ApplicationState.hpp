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

    struct ApplicationState
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            ApplicationState() = default;
            ApplicationState(GraphDimension dim, AlgorithmStepSpeed speed);
            GraphDimension dimension;
            AlgorithmStepSpeed stepSpeed;
            State currentState;
            bool showNodeInfo;
            bool stateChanged;
            const PDNode *nodeUnderCursor = nullptr;
            bool autoStep;
            bool showPath;
            bool showPathLines;
            bool runAStar;
            bool showAStarPath;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
