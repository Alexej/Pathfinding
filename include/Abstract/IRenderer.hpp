#ifndef E0993BE7_1552_4FDD_B2ED_36A6D9591A37
#define E0993BE7_1552_4FDD_B2ED_36A6D9591A37

namespace sf { class RenderWindow; }
namespace sf { class Drawable; }

namespace Pathfinding::Abstract
{
    class IRenderer
    {
        public:
            virtual void render(sf::RenderWindow & window, const sf::Drawable & drawable) = 0;
        
            virtual ~IRenderer() = default;
    };
}

#endif /* E0993BE7_1552_4FDD_B2ED_36A6D9591A37 */
