#ifndef A6575B6A_BD50_4D9E_97EF_154E649DEAFC
#define A6575B6A_BD50_4D9E_97EF_154E649DEAFC

#include <SFML/System/Vector2.hpp>
#include <stdint.h>

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
}

namespace Pathfinding::Core
{
    class ApplicationState;
}

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::LatticeGraph;
    using Pathfinding::Core::ApplicationState;
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
        GraphOperations(ApplicationState * state, LatticeGraph *graph, int64_t nodeSideLength);
        void rightMouseButtonPressed(sf::Vector2i pos);
        void leftMouseButtonPressed(sf::Vector2i pos);
        void mouseButtonReleased(sf::Vector2i pos);
        void nodeUnderCursor(sf::Vector2i pos);
        void mouseMoved(sf::Vector2i pos);
        void resize(int64_t nodeSideLength);
        void disableEnpointsEvent();
        void enableEndPointsEvent();

    private:
        MouseAction currentMouseAction = MouseAction::IDLE;
        LatticeGraph *graphPtr;
        ApplicationState * applicationStatePtr;
        bool endPointsEvent = true;
        int64_t nodeSideLength;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
