#ifndef D67C94A0_9775_460D_A680_FF8D757CE4F2
#define D67C94A0_9775_460D_A680_FF8D757CE4F2

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Vec2.hpp"
#include "IDrawNodeStrategy.hpp"


namespace Pathfinding::Datastructures {struct Key;}
namespace Pathfinding::Datastructures {struct Node;}
namespace Pathfinding::Core {struct ApplicationState;}


namespace Pathfinding::Rendering
{
    struct NodeStateColors;
    class SFMLNodeStrategy final : public Pathfinding::Abstract::IDrawNodeStrategy
    {
        public:
            SFMLNodeStrategy(const sf::Font & font, 
                        NodeStateColors & colorsRef, 
                        Pathfinding::Core::ApplicationState & appStateRef,
                        sf::RenderWindow & windowRef);

            void draw(const Pathfinding::Datastructures::Node * node) override;

            void resize();
        private:
            void prepareDrawableNode(const Pathfinding::Datastructures::Node & node);

            bool renderNodeInfo() const;

            void drawNode(bool nodeBlocked) const;

            void setRectsSize();

            void setRectsPosition(Pathfinding::Datastructures::Vec2i location);
            
        private:
            sf::Text rhsText;
            sf::Text gText;
            sf::Text keyText;
            sf::RectangleShape factorRect;
            sf::RectangleShape nodeRect;
            NodeStateColors & colorsRef;
            Pathfinding::Core::ApplicationState & appStateRef;
            sf::RenderWindow & windowRef;
    };
}

#endif /* D67C94A0_9775_460D_A680_FF8D757CE4F2 */
