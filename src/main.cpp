
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
        appBuilder.setDimension({8, 10, 20, 25, 40, 80});
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


/*
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}


*/