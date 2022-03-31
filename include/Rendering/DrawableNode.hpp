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
        private:
            using PDNode = Pathfinding::Datastructures::Node;
            using PCApplicationState = Pathfinding::Core::ApplicationState;
            using PDVec2i = Pathfinding::Datastructures::Vec2i;
            using PDKey = Pathfinding::Datastructures::Key;
        public:
            void init(const sf::Font & font, 
                        NodeStateColors * colors, 
                        PCApplicationState * appStatePtr, 
                        PDVec2i position);

            void resize();

        protected:
            void prepareNodeInfo(double g, double rhs, const PDKey & key);

            bool renderNodeInfo() const;

        private:
            void setRectsSizeAndPosition();
            
        protected:
            sf::Text rhsText;
            sf::Text gText;
            sf::Text keyText;
            sf::RectangleShape factorRect;
            sf::RectangleShape nodeRect;
            NodeStateColors * colors;

        private:
            PCApplicationState * appStatePtr;
            PDVec2i position;
    };
}

#endif /* D67C94A0_9775_460D_A680_FF8D757CE4F2 */
