#include "ResourcePaths.hpp"
#include <exception>
#include <filesystem>

#include "Constants.hpp"
#include "CouldNotFindPathToFontException.hpp"

using namespace Pathfinding::Constants;
namespace Pathfinding::Helpers
{
    using Pathfinding::Exceptions::CouldNotFindPathToFontException;
    std::string pathToFont()
    {
        std::string rootDirAsString = std::string(ROOT_DIR_NAME);
        std::string absolutePath = std::filesystem::current_path().string();
        std::string::size_type firstOccurence = absolutePath.find(rootDirAsString);
        if (firstOccurence == std::string::npos)
        {
            throw CouldNotFindPathToFontException("File path unknown", "ResourcePaths.cpp", 17, "std::string pathToFont()");
        }
        std::string rootDir = absolutePath.substr(0, firstOccurence + rootDirAsString.size());
        return rootDir + "\\dependencies\\fonts\\";
    }
}