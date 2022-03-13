#ifndef BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4
#define BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4

namespace Pathfinding::Helpers
{
    inline std::string getSubstrBeforeChar(std::string string, char character)
    {
        return string.substr(0, string.find(character, 0));
    }
}

#endif /* BA02AD0F_18BA_4B01_8B1E_B33E40EAF7C4 */
