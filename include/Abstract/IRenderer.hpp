#ifndef E0993BE7_1552_4FDD_B2ED_36A6D9591A37
#define E0993BE7_1552_4FDD_B2ED_36A6D9591A37

#include <vector>
#include <SFML/Graphics/Color.hpp>

namespace Pathfinding::Datastructures { class LatticeGraph; }
namespace Pathfinding::Datastructures { struct Node; }
namespace Pathfinding::Abstract { class ALatGraphWr; }
namespace Pathfinding::Rendering { class DrawablePath; }    
namespace sf { class RenderWindow; }

namespace Pathfinding::Abstract
{
    class IRenderer
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PDLatticeGraph = Pathfinding::Datastructures::LatticeGraph;
            using PAALatGraphWr = Pathfinding::Abstract::ALatGraphWr;
            using SFRenderWindow = sf::RenderWindow;
            using PRDrawablePath = Pathfinding::Rendering::DrawablePath;
        public:
            virtual void render(sf::RenderWindow & window, const std::shared_ptr<PAALatGraphWr> latticeGraphWrapperSPtr) = 0;
            
            virtual void render(SFRenderWindow & window, const PRDrawablePath & path) = 0;

            virtual void reset() = 0;
            
            virtual void resize() = 0;
            
            virtual ~IRenderer() = default;
            
    };
}

#endif /* E0993BE7_1552_4FDD_B2ED_36A6D9591A37 */
