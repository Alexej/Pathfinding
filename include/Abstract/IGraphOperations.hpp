#ifndef EB680F2C_50F9_4455_A58D_57056DDD3346
#define EB680F2C_50F9_4455_A58D_57056DDD3346

#include <functional>
#include <SFML/System/Vector2.hpp>

namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Events { struct MouseData; }

namespace Pathfinding::Abstract
{
    class IGraphOperations
    {
        public:
            virtual void rightMouseButtonPressed(Pathfinding::Events::MouseData mouseData) = 0;
            
            virtual void leftMouseButtonPressed(Pathfinding::Events::MouseData mouseData) = 0;
            
            virtual void mouseButtonReleased(Pathfinding::Events::MouseData mouseData) = 0;
            
            virtual void nodeUnderCursor(Pathfinding::Events::MouseData mouseData) = 0;
            
            virtual void mouseMoved(Pathfinding::Events::MouseData mouseData) = 0;
            
            virtual void mouseWheelMoved(Pathfinding::Events::MouseData mouseData) = 0;
            
            virtual void resize(int32_t nodeSideLength) = 0;
            
            virtual void disableEndpointsEvent() = 0;
            
            virtual void enableEndPointsEvent() = 0;
            
            virtual void disableObsticlesAndScrollEvents() = 0;
            
            virtual void enableObsticlesAndScrollEvents() = 0;
            
            virtual bool endpointsEvents() const = 0;
            
            virtual bool obsticlesAndScrollEvents() const = 0;
            
            virtual void addEdgeChangeCallBack(std::function<void(Pathfinding::Datastructures::Node * node)> callBack) = 0;
            
            virtual ~IGraphOperations() = default;
            
    };
}

#endif /* EB680F2C_50F9_4455_A58D_57056DDD3346 */
