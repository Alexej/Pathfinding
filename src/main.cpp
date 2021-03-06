#include <iostream>
#include <memory>

#include "Application.hpp"
#include "ApplicationBuilder.hpp"
#include "IApplication.hpp"
#include "IFontLoader.hpp"
#include "FontLoader.hpp"

#include "CouldNotFindPathToFontException.hpp"
#include "CouldNotLoadFontException.hpp"
#include "WrongNodeNumberForDimensionException.hpp"
#include "NoSuchFontException.hpp"

#include <cmath>
#include <numbers>

#include <SFML/Graphics.hpp>

#include "CostFunction.hpp"

int main()
{
    using Pathfinding::Abstract::IApplication;
    using Pathfinding::Abstract::IFontLoader;
    using Pathfinding::Core::Application;
    using Pathfinding::Core::ApplicationBuilder;
    using Pathfinding::Exceptions::CouldNotFindPathToFontException;
    using Pathfinding::Exceptions::CouldNotLoadFontException;
    using Pathfinding::Exceptions::NoSuchFontException;
    using Pathfinding::Exceptions::WrongNodeNumberForDimensionException;
    using Pathfinding::Helpers::FontLoader;

    ApplicationBuilder appBuilder;
    std::unique_ptr<IApplication> app = nullptr;
    std::shared_ptr<IFontLoader> fontLoaderSPtr = std::make_shared<FontLoader>();

    try
    {
        fontLoaderSPtr->loadFont("NugoSansLight.ttf");
        appBuilder.setDimension({5,11,55});
        appBuilder.setCosts(static_cast<int32_t>(std::sqrt(2) * 10), 10 * 1);
        appBuilder.setFontLoader(fontLoaderSPtr);
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
    catch (NoSuchFontException &exception)
    {
        std::cout << exception.what() << "\n";
        return -1;
    }

    app->run();

    return 0;
}