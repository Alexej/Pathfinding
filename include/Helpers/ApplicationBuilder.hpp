#ifndef FB23F09D_BB6A_4446_8683_4BBE6E4646E5
#define FB23F09D_BB6A_4446_8683_4BBE6E4646E5

#include <memory>
#include <initializer_list>
#include "AlgorithmStepSpeed.hpp"
#include "GraphDimension.hpp"

namespace Pathfinding::Core { class Application; }
namespace Pathfinding::Abstract { class IApplication; }

namespace Pathfinding::Helpers
{
    class ApplicationBuilder
    {
        private:
            using PDAlgorithmStepSpeed = Pathfinding::Core::AlgorithmStepSpeed;
            using PDGraphDimension = Pathfinding::Core::GraphDimension;
            using PCApplication = Pathfinding::Core::Application;
            using PAIApplication = Pathfinding::Abstract::IApplication;
        public:
            ApplicationBuilder();
            
            void setStepSpeed(std::initializer_list<int32_t> speeds);
            
            void setDimension(std::initializer_list<int32_t> numberOfNodesInRow);
            
            void setCosts(int32_t diagonalCost, int32_t straightCost);
            
            std::unique_ptr<PAIApplication> make();
            
        private:
            void instantiateObjects();
            
            void initializeObjects();
            
            void createEventManagerBindings();
            
            void setMenuCallBacks();
            
            void initDStarLite();
            
            void initAStar();
            
        private:
            std::unique_ptr<PCApplication> applicationUPtr = nullptr;
            PDAlgorithmStepSpeed stepSpeed;
            PDGraphDimension dimension;
            int32_t diagonalCost;
            int32_t straightCost;
    };
}

#endif /* FB23F09D_BB6A_4446_8683_4BBE6E4646E5 */
