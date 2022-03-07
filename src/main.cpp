#include <iostream>
#include <memory>

#include "Application.hpp"
#include "ApplicationBuilder.hpp"
#include "IApplication.hpp"

#include "CouldNotFindPathToFontException.hpp"
#include "CouldNotLoadFontException.hpp"
#include "WrongNodeNumberForDimensionException.hpp"


#include <cmath>
#include <numbers>


int main()
{   
    using Pathfinding::Abstract::IApplication;
    using Pathfinding::Core::Application;
    using Pathfinding::Exceptions::CouldNotFindPathToFontException;
    using Pathfinding::Exceptions::CouldNotLoadFontException;
    using Pathfinding::Exceptions::WrongNodeNumberForDimensionException;
    using Pathfinding::Helpers::ApplicationBuilder;

    ApplicationBuilder appBuilder;
    std::unique_ptr<IApplication> app = nullptr;

    try
    {
        appBuilder.setStepSpeed({100, 200, 400, 800, 1600, 0});
        appBuilder.setDimension({4,8, 10, 20, 25, 40, 80});
        appBuilder.setCosts(static_cast<int32_t>(std::sqrt(2) * 10), 10 * 1);
        app = appBuilder.make();
    }
    catch (CouldNotFindPathToFontException &exception)
    {
        std::cout << exception.what() << "\n";
        return -1;
    }
    catch (CouldNotLoadFontException &exception)
    {
        std::cout << exception.what() << "\n";
        return -1;
    }
    catch (WrongNodeNumberForDimensionException &exception)
    {
        std::cout << exception.what() << "\n";
        return -1;
    }

    app->run();

    return 0;
}
