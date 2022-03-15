#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Core
{
    enum class State { READY, SEARCHING, FOUND_PATH, NO_PATH };

    struct ApplicationState
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            ApplicationState() = default;

            ApplicationState(GraphDimension dim, AlgorithmStepSpeed speed);

            bool algorithmFinished() const;

            GraphDimension dimension;
            AlgorithmStepSpeed stepSpeed;
            State currentState = State::READY;
            bool showNodeInfo = false;
            bool stateChanged = false;
            const PDNode *nodeUnderCursor = nullptr;
            bool autoStep = false;
            bool showPathPoints = true;
            bool showPathLines = true;
            bool runAStar = false;
            bool showAStarPath = false;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
