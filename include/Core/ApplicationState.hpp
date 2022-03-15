#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"
#include "GraphDimension.hpp"

namespace Pathfinding::Datastructures { struct Node; }

namespace Pathfinding::Core
{
    enum class AlgorithmState { READY, SEARCHING, FOUND_PATH, NO_PATH };

    struct ApplicationState
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            ApplicationState() = default;

            ApplicationState(GraphDimension dim);

            bool algorithmFinished() const;

            GraphDimension dimension;
            int32_t stepSpeed = Pathfinding::Constants::DEFAULT_STEP_SPEED;
            AlgorithmState currentState = AlgorithmState::READY;
            bool showNodeInfo = false;
            const PDNode *nodeUnderCursor = nullptr;
            bool autoStep = false;
            bool showPathPoints = true;
            bool showPathLines = true;
            bool runAStar = false;
            bool showAStarPath = false;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
