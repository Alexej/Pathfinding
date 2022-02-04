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
    private:
        using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PADStarLite = Pathfinding::Algorithms::DStarLite;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;

    public:
        GraphOperations() = default;
        GraphOperations(PCApplicationState *state, PADStarLite *dstar, PDLatticeGraph *graph, int32_t nodeSideLength);
        void rightMouseButtonPressed(sf::Vector2i pos);
        void leftMouseButtonPressed(sf::Vector2i pos);
        void mouseButtonReleased(sf::Vector2i pos);
        void nodeUnderCursor(sf::Vector2i pos);
        void mouseMoved(sf::Vector2i pos);
        void resize(int32_t nodeSideLength);
        void disableEndpointsEvent();
        void enableEndPointsEvent();
        void disableObsticlesEvents();
        void enableObsticlesEvents();
        bool endpointsEvents() const;
        bool obsticlesEvents() const;
        void blockNodeAndNotifyDstarLiteIfRunning(PDVec2i mappedCoordinates);
        void clearNodeAndNotifyDstarLiteIfRunning(PDVec2i mappedCoordinates);

    private:
        MouseAction currentMouseAction = MouseAction::IDLE;
        PDLatticeGraph *graphPtr;
        PADStarLite *dstarPtr;
        PCApplicationState *applicationStatePtr;
        bool endPointsEvents_ = true;
        bool obsticlesEvents_ = true;
        int32_t nodeSideLength;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
