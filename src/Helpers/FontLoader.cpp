#include "FontLoader.hpp"

#include "RootPath.hpp"
#include "NoSuchFontException.hpp"
#include "CouldNotLoadFontException.hpp"
#include "CppHelpers.hpp"

namespace Pathfinding::Helpers
{
    void FontLoader::loadFont(std::string fontName)
    {
        sf::Font font;
        if (!font.loadFromFile(getRootPath() + "\\dependencies\\fonts\\" + fontName))
        {
            throw Exceptions::CouldNotLoadFontException("Could not load font");
        }
        auto fontNameWithoutExtension = Pathfinding::Helpers::getSubstrBeforeChar(fontName, '.');
        fonts.insert({fontNameWithoutExtension, font});
    }   

    const sf::Font & FontLoader::getFont(std::string fontName) const
    {
        const auto it = fonts.find(fontName);
        if(it == fonts.end())
        {
            throw Exceptions::NoSuchFontException("Font not present in map!");
        }
        return it->second;
    }
}