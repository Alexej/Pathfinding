#ifndef E2306EB2_637F_405A_9CDF_3B7A3CF42718
#define E2306EB2_637F_405A_9CDF_3B7A3CF42718

#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include "RootPath.hpp"
#include "NoSuchFontException.hpp"
#include "CouldNotLoadFontException.hpp"
#include "IFontLoader.hpp"
#include "OtherHelpers.hpp"

namespace Pathfinding::Helpers
{
    class FontLoader final : public Pathfinding::Abstract::IFontLoader
    {
        public:
            void loadFont(std::string fontName) override
            {
                sf::Font font;
                if (!font.loadFromFile(getRootPath() + "\\dependencies\\fonts\\" + fontName))
                {
                    throw Exceptions::CouldNotLoadFontException("Could not load font");
                }
                auto fontNameWithoutExtension = Pathfinding::Helpers::getSubstrBeforeChar(fontName, '.');
                fonts.insert({fontNameWithoutExtension, font});
            }   

            const sf::Font & getFont(std::string fontName) const override
            {
                const auto it = fonts.find(fontName);
                if(it == fonts.end())
                {
                    throw Exceptions::NoSuchFontException("Font not present in map!");
                }
                return it->second;
            }

        private:
            std::unordered_map<std::string, sf::Font> fonts;
    };
}

#endif /* E2306EB2_637F_405A_9CDF_3B7A3CF42718 */
