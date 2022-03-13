#ifndef E0993BE7_1552_4FDD_B2ED_36A6D9591A37
#define E0993BE7_1552_4FDD_B2ED_36A6D9591A37

#include <vector>
#include <SFML/Graphics/Color.hpp>

namespace Pathfinding::Datastructures { class LatticeGraph; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Abstract { class ALatGraphWr; }

namespace Pathfinding::Abstract
{
    class IRenderer
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
            using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
        public:
            virtual void render(const std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr) = 0;
            
            virtual void renderPath(const std::vector<PDNode *> & path, sf::Color color) = 0;
            
            virtual void update() = 0;
            
            virtual void reset() = 0;
            
            virtual void resize() = 0;
            
            virtual ~IRenderer() = default;
            
    };
}

#endif /* E0993BE7_1552_4FDD_B2ED_36A6D9591A37 */
