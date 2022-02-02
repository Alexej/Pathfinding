#ifndef A6575B6A_BD50_4D9E_97EF_154E649DEAFC
#define A6575B6A_BD50_4D9E_97EF_154E649DEAFC

#include <SFML/System/Vector2.hpp>
#include <stdint.h>
#include "Vector2.hpp"

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
}

namespace Pathfinding::Core
{
    class ApplicationState;
}

namespace Pathfinding::Algorithms
{
    class DStarLite;
}

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Algorithms::DStarLite;
    using Pathfinding::Datastructures::Vector2i;

    enum class MouseAction
    {
        SETTING_START,
        SETTING_GOAL,
        BLOCKING_NODE,
        CLEARING_NODE,
        IDLE
    };

    class GraphOperations
    {
    public:
        GraphOperations() = default;
        GraphOperations(ApplicationState * state, DStarLite* dstar, LatticeGraph *graph, int32_t nodeSideLength);
        void rightMouseButtonPressed(sf::Vector2i pos);
        void leftMouseButtonPressed(sf::Vector2i pos);
        void mouseButtonReleased(sf::Vector2i pos);
        void nodeUnderCursor(sf::Vector2i pos);
        void mouseMoved(sf::Vector2i pos);
        void resize(int32_t nodeSideLength);
        void disableEnpointsEvent();
        void enableEndPointsEvent();
        void blockNodeAndNotifyDstarLiteIfRunning(Vector2i mappedCoordinates);
        void clearNodeAndNotifyDstarLiteIfRunning(Vector2i mappedCoordinates);
    private:
        MouseAction currentMouseAction = MouseAction::IDLE;
        LatticeGraph *graphPtr;
        DStarLite * dstarPtr;
        ApplicationState * applicationStatePtr;
        bool endPointsEvent = true;
        int32_t nodeSideLength;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
