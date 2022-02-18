#ifndef A6575B6A_BD50_4D9E_97EF_154E649DEAFC
#define A6575B6A_BD50_4D9E_97EF_154E649DEAFC

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <functional>

#include "Vector2.hpp"
#include "IGraphOperations.hpp"

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
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

    class GraphOperations final : public Pathfinding::Abstract::IGraphOperations
    {
    private:
        using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PADStarLite = Pathfinding::Algorithms::DStarLite;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
    public:
        GraphOperations() = default;
        GraphOperations(PCApplicationState *state, PDLatticeGraph *graph);
        void rightMouseButtonPressed(sf::Vector2i pos) override;
        void leftMouseButtonPressed(sf::Vector2i pos) override;
        void mouseButtonReleased(sf::Vector2i pos) override;
        void nodeUnderCursor(sf::Vector2i pos) override;
        void mouseMoved(sf::Vector2i pos) override;
        void resize(int32_t nodeSideLength) override;
        void disableEndpointsEvent() override;
        void enableEndPointsEvent() override;
        void disableObsticlesEvents() override;
        void enableObsticlesEvents() override;
        bool endpointsEvents() const override;
        bool obsticlesEvents() const override;
        void addEdgeChangeCallBack(std::function<void(PDNode * node)> callBack) override;
    private:
        void blockNodeAndNotifyAlgorithm(PDVec2i mappedCoordinates);
        void clearNodeAndNotifyAlgorithm(PDVec2i mappedCoordinates);

    private:
        MouseAction currentMouseAction = MouseAction::IDLE;
        std::function<void(PDNode * node)> edgeChangeCallBack;
        PDLatticeGraph *graphPtr;
        PADStarLite *dstarPtr;
        PCApplicationState *applicationStatePtr;
        bool endPointsEvents_ = true;
        bool obsticlesEvents_ = true;
        int32_t nodeSideLength;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
