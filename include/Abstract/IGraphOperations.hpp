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
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PEMouseData = Pathfinding::Events::MouseData;
        public:
            virtual void rightMouseButtonPressed(PEMouseData mouseData) = 0;
            
            virtual void leftMouseButtonPressed(PEMouseData mouseData) = 0;
            
            virtual void mouseButtonReleased(PEMouseData mouseData) = 0;
            
            virtual void nodeUnderCursor(PEMouseData mouseData) = 0;
            
            virtual void mouseMoved(PEMouseData mouseData) = 0;
            
            virtual void mouseWheelMoved(PEMouseData mouseData) = 0;
            
            virtual void resize(int32_t nodeSideLength) = 0;
            
            virtual void disableEndpointsEvent() = 0;
            
            virtual void enableEndPointsEvent() = 0;
            
            virtual void disableObsticlesAndScrollEvents() = 0;
            
            virtual void enableObsticlesAndScrollEvents() = 0;
            
            virtual bool endpointsEvents() const = 0;
            
            virtual bool obsticlesAndScrollEvents() const = 0;
            
            virtual void addEdgeChangeCallBack(std::function<void(PDNode * node)> callBack) = 0;
            
            virtual ~IGraphOperations() = default;
            
    };
}

#endif /* EB680F2C_50F9_4455_A58D_57056DDD3346 */
