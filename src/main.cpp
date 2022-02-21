#include "Application.hpp"
#include "ApplicationBuilder.hpp"
#include "IApplication.hpp"

#include <iostream>
#include <filesystem>
#include <memory>


int main()
{
    using Pathfinding::Core::Application;
    using Pathfinding::Abstract::IApplication;
    using Pathfinding::Helpers::ApplicationBuilder;

    ApplicationBuilder appBuilder;

    appBuilder.setStepSpeed({100, 200, 400, 800, 1600, 0});

    appBuilder.setDimension({8, 10, 20, 25, 40});

    appBuilder.setCosts(static_cast<int32_t>(sqrt(2)* 10), 10 * 1);

    std::unique_ptr<IApplication> app = appBuilder.make();
    app->run();
    return 0;
}
