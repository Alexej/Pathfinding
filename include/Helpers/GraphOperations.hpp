#ifndef A6575B6A_BD50_4D9E_97EF_154E649DEAFC
#define A6575B6A_BD50_4D9E_97EF_154E649DEAFC

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <functional>

#include "Vec2.hpp"
#include "IGraphOperations.hpp"

namespace Pathfinding::Datastructures
{
    class LatticeGraph;
    struct Node;
}

namespace Pathfinding::Core
{
    struct ApplicationState;
}

namespace Pathfinding::Algorithms
{
    class DStarLite;
}

namespace Pathfinding::Abstract
{
    class ALatticeGraphWrapper;
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
        using PAALatticeGraphWrapper = Pathfinding::Abstract::ALatticeGraphWrapper;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PADStarLite = Pathfinding::Algorithms::DStarLite;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
    public:
        GraphOperations() = default;
        GraphOperations(PCApplicationState * appStateSPtr, 
                        std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapperUPtr);
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
        std::function<void(PDNode * node)> edgeChangeCallBack;
        int32_t nodeSideLength;
        MouseAction currentMouseAction = MouseAction::IDLE;
        std::shared_ptr<PAALatticeGraphWrapper> latGraphWrapperUPtr;
        PADStarLite *dstarPtr;
        PCApplicationState * appStateSPtr;
        bool endPointsEvents_ = true;
        bool obsticlesEvents_ = true;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
