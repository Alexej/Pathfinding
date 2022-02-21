#ifndef EB680F2C_50F9_4455_A58D_57056DDD3346
#define EB680F2C_50F9_4455_A58D_57056DDD3346

#include <functional>
#include <SFML/System/Vector2.hpp>

namespace Pathfinding::Datastructures
{
    struct Node;
}

namespace Pathfinding::Abstract
{
    class IGraphOperations
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            virtual void rightMouseButtonPressed(sf::Vector2i pos) = 0;
            virtual void leftMouseButtonPressed(sf::Vector2i pos) = 0;
            virtual void mouseButtonReleased(sf::Vector2i pos) = 0;
            virtual void nodeUnderCursor(sf::Vector2i pos) = 0;
            virtual void mouseMoved(sf::Vector2i pos) = 0;
            virtual void resize(int32_t nodeSideLength) = 0;
            virtual void disableEndpointsEvent() = 0;
            virtual void enableEndPointsEvent() = 0;
            virtual void disableObsticlesEvents() = 0;
            virtual void enableObsticlesEvents() = 0;
            virtual bool endpointsEvents() const = 0;
            virtual bool obsticlesEvents() const = 0;
            virtual void addEdgeChangeCallBack(std::function<void(PDNode * node)> callBack) = 0;
            virtual ~IGraphOperations() = default;
    };
}

#endif /* EB680F2C_50F9_4455_A58D_57056DDD3346 */
