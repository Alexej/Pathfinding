#ifndef E2306EB2_637F_405A_9CDF_3B7A3CF42718
#define E2306EB2_637F_405A_9CDF_3B7A3CF42718

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include "IFontLoader.hpp"

namespace Pathfinding::Helpers
{
    class FontLoader final : public Pathfinding::Abstract::IFontLoader
    {
        public:
            void loadFont(std::string fontName) override;

            const sf::Font & getFont(std::string fontName) const override;

        private:
            std::unordered_map<std::string, sf::Font> fonts;
    };
}

#endif /* E2306EB2_637F_405A_9CDF_3B7A3CF42718 */
