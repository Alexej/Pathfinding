#include "ResourcePaths.hpp"
#include <exception>
#include <filesystem>

#include "Constants.hpp"

using namespace Pathfinding::Constants;
namespace Pathfinding::Helpers
{
    std::string pathToFont()
    {
        std::string rootDirAsString = std::string(ROOT_DIR_NAME);
        std::string absolutePath = std::filesystem::current_path().string();
        std::string::size_type firstOccurence = absolutePath.find(rootDirAsString);
        if(firstOccurence == std::string::npos)
        {
            throw std::exception("File path unknown, please hardcode path to fonts in Renderer.cpp");
        }
        std::string rootDir = absolutePath.substr(0, firstOccurence + rootDirAsString.size());
        return rootDir + "\\dependencies\\fonts\\";
    }
}