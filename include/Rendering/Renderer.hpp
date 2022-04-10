#ifndef CD610974_FBD6_479E_835B_DBFAA7BF55B2
#define CD610974_FBD6_479E_835B_DBFAA7BF55B2

#include "IRenderer.hpp"
#include "IDrawNodeStrategy.hpp"
#include "ILatticeGraph.hpp"

namespace Pathfinding::Rendering
{
    class Renderer final : public Pathfinding::Abstract::IRenderer
    {
        void render(sf::RenderWindow &window, const sf::Drawable &drawable) override
        {
            window.draw(drawable);
        }

        void render(const Pathfinding::Abstract::ILatticeGraph & graph, 
                          Pathfinding::Abstract::IDrawNodeStrategy & strategy) const override
        {
            graph.draw(strategy);
        }
    };
}

#endif /* CD610974_FBD6_479E_835B_DBFAA7BF55B2 */
