#ifndef CD610974_FBD6_479E_835B_DBFAA7BF55B2
#define CD610974_FBD6_479E_835B_DBFAA7BF55B2

#include "IRenderer.hpp"

namespace Pathfinding::Rendering
{
    class Renderer final : public Pathfinding::Abstract::IRenderer
    {
        void render(sf::RenderWindow & window, const sf::Drawable & drawable) override
        {
            window.draw(drawable);
        }
    };
}

#endif /* CD610974_FBD6_479E_835B_DBFAA7BF55B2 */
