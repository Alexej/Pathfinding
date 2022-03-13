#ifndef A6575B6A_BD50_4D9E_97EF_154E649DEAFC
#define A6575B6A_BD50_4D9E_97EF_154E649DEAFC

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <functional>

#include "Vec2.hpp"
#include "IGraphOperations.hpp"

namespace Pathfinding::Datastructures { class LatticeGraph; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Core { struct ApplicationState; }
namespace Pathfinding::Algorithms { class DStarLite; }
namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Events { struct MouseData; }

namespace Pathfinding::Helpers
{

    enum class MouseAction { SETTING_START, SETTING_GOAL, BLOCKING_NODE, CLEARING_NODE, IDLE };

    class GraphOperations final : public Pathfinding::Abstract::IGraphOperations
    {
    private:
        using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        using PCApplicationState = Pathfinding::Core::ApplicationState;
        using PADStarLite = Pathfinding::Algorithms::DStarLite;
        using PDVec2i = Pathfinding::Datastructures::Vec2i;
        using PDNode = Pathfinding::Datastructures::Node;
        using PEMouseData = Pathfinding::Events::MouseData;
    public:
        GraphOperations() = default;
        
        GraphOperations(PCApplicationState * appStateSPtr, 
                        std::shared_ptr<PAALatGraphWr> latGraphWrapperUPtr);
                        
        void rightMouseButtonPressed(PEMouseData mouseData) override;
        
        void leftMouseButtonPressed(PEMouseData mouseData) override;
        
        void mouseButtonReleased(PEMouseData mouseData) override;
        
        void nodeUnderCursor(PEMouseData mouseData) override;
        
        void mouseMoved(PEMouseData mouseData) override;
        
        void mouseWheelMoved(PEMouseData mouseData) override;
        
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
        std::shared_ptr<PAALatGraphWr> latGraphWrapperUPtr;
        PADStarLite *dstarPtr;
        PCApplicationState * appStateSPtr;
        bool endPointsEvents_ = true;
        bool obsticlesEvents_ = true;
    };
}

#endif /* A6575B6A_BD50_4D9E_97EF_154E649DEAFC */
