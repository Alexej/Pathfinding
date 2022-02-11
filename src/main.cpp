#include "Application.hpp"
#include <iostream>
#include <filesystem>
#include "ResourcePaths.hpp"

int main()
{
    using Pathfinding::Core::Application;
    Application app;
    app.run();
 
    return 0;
}