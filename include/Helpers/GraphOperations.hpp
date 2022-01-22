#ifndef A6575B6A_BD50_4D9E_97EF_154E649DEAFC
#define A6575B6A_BD50_4D9E_97EF_154E649DEAFC

#include <SFML/System/Vector2.hpp>
#include <stdint.h>

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
}

namespace Pathfinding::Helpers
{
    using Pathfinding::Datastructures::LatticeGraph;
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
        GraphOperations(LatticeGraph *graph, int32_t nodeSideLength);
        void rightMouseButtonPressed(sf::Vector2i pos);
        void leftMouseButtonPressed(sf::Vector2i pos);
        void mouseButtonReleased(sf::Vector2i pos);
        void mouseMoved(sf::Vector2i pos);
        void resize(int32_t nodeSideLength);
        void disableEnpointsEvent();
        void enableEndPointsEvent();

    private:
        MouseAction currentMouseAction = MouseAction::IDLE;
        LatticeGraph *graphPtr;
        bool endPointsEvent = true;
        int32_t nodeSideLength;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
