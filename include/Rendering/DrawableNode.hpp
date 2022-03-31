#ifndef D67C94A0_9775_460D_A680_FF8D757CE4F2
#define D67C94A0_9775_460D_A680_FF8D757CE4F2

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Vec2.hpp"

namespace Pathfinding::Datastructures {struct Key;}
namespace Pathfinding::Datastructures {struct Node;}
namespace Pathfinding::Core {struct ApplicationState;}


namespace Pathfinding::Rendering
{
    struct NodeStateColors;
    class DrawableNode : public sf::Drawable
    {
        public:
            void init(const sf::Font & font, 
                        NodeStateColors * colors, 
                        Pathfinding::Core::ApplicationState * appStatePtr, 
                        Pathfinding::Datastructures::Vec2i position);

            void resize();

        protected:
            void prepareDrawableNode(const Pathfinding::Datastructures::Node & node);

            bool renderNodeInfo() const;

            void drawDrawableNode(sf::RenderTarget &target, bool nodeBlocked) const;

        private:
            void setRectsSizeAndPosition();
            
        private:
            sf::Text rhsText;
            sf::Text gText;
            sf::Text keyText;
            sf::RectangleShape factorRect;
            sf::RectangleShape nodeRect;
            NodeStateColors * colors;

        private:
            Pathfinding::Core::ApplicationState * appStatePtr;
            Pathfinding::Datastructures::Vec2i position;
    };
}

#endif /* D67C94A0_9775_460D_A680_FF8D757CE4F2 */
