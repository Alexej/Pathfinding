#ifndef D67C94A0_9775_460D_A680_FF8D757CE4F2
#define D67C94A0_9775_460D_A680_FF8D757CE4F2

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Pathfinding::Datastructures {struct Node;}

namespace Pathfinding::Rendering
{
    class DrawableNode final : public sf::Drawable
    {
        private:
            using PDNode = Pathfinding::Datastructures::Node;
        public:
            void init(const sf::Font & font);
            void prepare(const PDNode & node ,sf::Vector2f coords, sf::Color color, bool renderInfo);
            void resize(sf::Vector2f nodeSize, sf::Vector2f factorSize);
        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        private:
            sf::Text rhs;
            sf::Text g;
            sf::Text key;
            sf::RectangleShape factorRect;
            sf::RectangleShape nodeRect;
            bool renderInfoInNode = false;
    };
}

#endif /* D67C94A0_9775_460D_A680_FF8D757CE4F2 */
