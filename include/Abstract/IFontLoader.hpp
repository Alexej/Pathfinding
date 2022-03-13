#ifndef BB353B6F_065E_473D_B82D_1F169CC2FE7A
#define BB353B6F_065E_473D_B82D_1F169CC2FE7A

#include <SFML/Graphics/Font.hpp>

namespace Pathfinding::Abstract
{
    class IFontLoader
    {
        public:
            virtual void loadFont(std::string fontName) = 0;
            virtual const sf::Font & getFont(std::string fontName) const = 0;

    };
}

#endif /* BB353B6F_065E_473D_B82D_1F169CC2FE7A */
