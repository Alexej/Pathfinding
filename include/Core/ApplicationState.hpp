#ifndef C35910EF_5FC3_4918_8225_6FEE6352FD76
#define C35910EF_5FC3_4918_8225_6FEE6352FD76

#include "Constants.hpp"
#include "GraphDimension.hpp"

namespace Pathfinding::Core
{
    using namespace Pathfinding::Constants;
    
    enum class State{ READY, SEARCHING, DONE};
    class ApplicationState
    {
        public:
            ApplicationState();
            int32_t currentNumberOfNodesI() const;
            bool canShowNodeInfo() const;
            bool showNodeInfo() const;
            void enableNodeInfo();
            void disableNodeInfo();
            void setState(State state);
            void setCurrentNumberOfNodesIndex(int32_t index);
            int32_t currentNodeSideLength() const;
            State currentState() const; 
            int32_t currentNumberOfNodesIndex() const;
        private:
            GraphDimension dim;
            State currentState_;
            bool showNodeInfo_;
            bool stateChanged;
    };
}

#endif /* C35910EF_5FC3_4918_8225_6FEE6352FD76 */
