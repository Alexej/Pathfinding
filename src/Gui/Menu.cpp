#include "Menu.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <format>

#include "Constants.hpp"
#include "ApplicationState.hpp"
#include "GraphDimension.hpp"
#include "Node.hpp"
#include "GuiHelpers.hpp"
#include "PathfinderCache.hpp"

namespace Pathfinding::Gui
{

    using namespace Pathfinding::Constants;
    using Pathfinding::Core::AlgorithmState;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::PathfinderCache;
    using Pathfinding::Helpers::getStateColor;
    using Pathfinding::Helpers::mapNodeStateToText;
    using Pathfinding::Helpers::mapStateToText;
    using Pathfinding::Helpers::printLargeText;
    using Pathfinding::Helpers::showStatistic;
    using Pathfinding::Helpers::getSizesOfSubVectors;

    Menu::Menu(ApplicationState *appStatePtr_,
               PathfinderCache *aCache_,
               PathfinderCache *dCache_)
        : appStatePtr(appStatePtr_),
          offset(static_cast<float>(GRID_FIELD_WIDTH)),
          height(static_cast<float>(GRID_FIELD_HEIGHT)),
          width(static_cast<float>(MENU_WIDTH)),
          aCache(aCache_),
          dCache(dCache_)
    {
        dimensionPtr = &appStatePtr->dimension;
    }

    void Menu::show()
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoTitleBar;

        ImGui::SetNextWindowPos(ImVec2(offset, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);

        ImGui::Begin("Configuration", nullptr, window_flags);

        switch (appStatePtr->currentState)
        {
        case AlgorithmState::READY:
            showReadyStateElements();
            break;
        case AlgorithmState::SEARCHING:
            showSearchingElements();
            break;
        }

        showCommonElements();

        if (appStatePtr->currentState == AlgorithmState::FOUND_PATH)
        {
            showDoneState();
        }
        ImGui::End();
    }

    void Menu::showSearchingElements()
    {
        if (ImGui::Button("STEP", ImVec2(width - 20, 20)))
        {
            callBacks.stepCallBack();
        }
    }

    void Menu::showNodeInfoFlag()
    {
        ImGui::Checkbox("Render Node Info", &appStatePtr->showNodeInfo);
        ImGui::SameLine();
        ImGui::HelpMarker("Upper left corner: G\nUpper right corner: RHS\nLower left corner: K1\nLower right corner: K2\nSmall rectangle: Factor");
    }

    void Menu::showAutoStepFlag()
    {
        ImGui::Checkbox("Auto step", &appStatePtr->autoStep);
        ImGui::SameLine();
        ImGui::HelpMarker("Automates step button");
    }

    void Menu::showAStarPath()
    {
        ImGui::Checkbox("Show A* path", &appStatePtr->showAStarPath);
        ImGui::SameLine();
        ImGui::HelpMarker("A* (for now) can take different\npath(same distance)");
    }

    void Menu::showGraph(std::vector<int32_t> values, std::string name)
    {
        std::vector<float> valuesFloat;
        for(auto value : values)
            valuesFloat.push_back(static_cast<float>(value));

        ImGui::Text(name.c_str());
        ImGui::PlotLines(std::format("last : {}.", std::to_string(values.back())).c_str(),
                         &valuesFloat[0],
                         static_cast<int32_t>(values.size()));
    }


    void Menu::update(sf::RenderWindow & window, sf::Time deltaClock)
    {
        ImGui::SFML::Update(window, deltaClock);
    }

    void Menu::processEvent(const sf::Event & event)
    {
        ImGui::SFML::ProcessEvent(event);
    }

    void Menu::shutDown()
    {
        ImGui::SFML::Shutdown();
    }

    void Menu::init(sf::RenderWindow & window)
    {
        ImGui::SFML::Init(window);
    }

    void Menu::render(sf::RenderWindow & window)
    {
        ImGui::SFML::Render(window);
    }

    void Menu::showStepSpeed()
    {
        ImGui::SliderInt("Speed[MS]", &appStatePtr->stepSpeed, 0, 10000);
        ImGui::SameLine();
        ImGui::HelpMarker("Step Speed for\nAutostep function");
    }

    void Menu::addCallbacks(MenuCallBacks callBacks_)
    {
        callBacks = callBacks_;
    }

    void Menu::showCommonElements()
    {
        if (ImGui::CollapsingHeader("Runtime Options"))
        {
            ImGui::Separator();
            showStepSpeed();
            showAutoStepFlag();
            showPathFlags();
            if (dimensionPtr->canShowNodeInfo())
            {
                showNodeInfoFlag();
            }
            if (appStatePtr->runAStar)
            {
                showAStarPath();
            }
            showMouseWheelEventComboBox();
            ImGui::Separator();
        }
        if (ImGui::CollapsingHeader("Node info"))
        {
            if (appStatePtr->nodeUnderCursor != nullptr)
            {
                ImGui::Separator();
                showNodeInfoInMenu();
                ImGui::Separator();
            }
        }

        auto color = getStateColor(appStatePtr->currentState);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(color[RED], color[GREEN], color[BLUE], 255));
        printLargeText(std::format("State: {}", mapStateToText(appStatePtr->currentState)), 2);
        ImGui::PopStyleColor();

        if (ImGui::Button("RESET", ImVec2(width - 20, 20)))
        {
            callBacks.resetCallback();
        }

        if (appStatePtr->currentState != AlgorithmState::READY)
        {
            if (appStatePtr->runAStar)
            {
                showGraph(getSizesOfSubVectors(aCache->nodesExpandedAll), "A* nodes Expanded");
            }
            showGraph(getSizesOfSubVectors(dCache->nodesExpandedAll), "D* nodes Expanded");
        }
    }

    void Menu::showNumberOfNodesComboBox()
    {
        static int32_t itemCurrentNumberOfNodes = dimensionPtr->currentNumberOfNodesIndex();
        auto numberOfNodesInRow = dimensionPtr->getNumberOfNodesInRowString();
        if (ImGui::custom_combo("# Of Nodes", &itemCurrentNumberOfNodes, numberOfNodesInRow))
        {
            callBacks.numberOfNodesChangedCallBack(itemCurrentNumberOfNodes);
            if (!dimensionPtr->canShowNodeInfo())
            {
                appStatePtr->showNodeInfo = false;
            }
        }
    }

    void Menu::showMouseWheelEventComboBox()
    {
        static int32_t currentMouseWheelEventInt = static_cast<int32_t>(appStatePtr->currentMouseWheelEvent);
        if (ImGui::custom_combo("# Of Nodes", &currentMouseWheelEventInt, mouseWheelEventStrings))
        {
            callBacks.mouseWheelEventChangedCallBack(currentMouseWheelEventInt);
        }
    }

    void Menu::showNodeInfoInMenu()
    {
        ImGui::Text(std::format("Height: {} Width: {}", appStatePtr->nodeUnderCursor->location.height,
                                appStatePtr->nodeUnderCursor->location.width)
                        .c_str());
        ImGui::Text(std::format("G: {}", appStatePtr->nodeUnderCursor->g).c_str());
        ImGui::Text(std::format("RHS: {}", appStatePtr->nodeUnderCursor->rhs).c_str());
        ImGui::Text(std::format("K1: {}", appStatePtr->nodeUnderCursor->key.k1).c_str());
        ImGui::Text(std::format("K2: {}", appStatePtr->nodeUnderCursor->key.k2).c_str());
        ImGui::Text(std::format("Cost factor: {}", appStatePtr->nodeUnderCursor->factor).c_str());
        ImGui::SameLine();
        ImGui::HelpMarker("Cost is multiplied by this value");
        ImGui::Text(std::format("State: {}", mapNodeStateToText(appStatePtr->nodeUnderCursor->state)).c_str());
    }

    void Menu::showReadyStateElements()
    {
        if (ImGui::CollapsingHeader("Start Options"))
        {
            ImGui::Separator();
            showNumberOfNodesComboBox();
            ImGui::Checkbox("Run A*", &appStatePtr->runAStar);
            ImGui::SameLine();
            ImGui::HelpMarker("A* is run at every step of D* lite,\nat the end statistic is provided");
            ImGui::Separator();
        }

        if (ImGui::Button("Start", ImVec2(width - 20, 20)))
        {
            callBacks.startCallBack();
        }

        if (ImGui::Button("RANDOM GRAPH", ImVec2(width - 20, 20)))
        {
            callBacks.randomGraphCallBack();
        }

        if (ImGui::Button("Maze", ImVec2(width - 20, 20)))
        {
            callBacks.mazeGraphCallBack();
        }
    }

    void Menu::showPathFlags()
    {
        ImGui::Checkbox("Render path", &appStatePtr->showPathPoints);
        if (appStatePtr->showPathPoints)
        {
            ImGui::Checkbox("Render path lines", &appStatePtr->showPathLines);
        }
    }

    void Menu::showDoneState()
    {
        if (appStatePtr->runAStar)
        {
            showSearchResults();
            ImGui::Separator();
            ImGui::Text("A* statistic");
            showStatistic(aCache);
        }
        ImGui::Separator();
        ImGui::Text("D* lite statistic");
        showStatistic(dCache);
    }

    void Menu::showSearchResults()
    {
        const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
        if (ImGui::CollapsingHeader("Step results"))
        {
            static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
            ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 14);
            if (ImGui::BeginTable("table_scrolly", 4, flags, outer_size))
            {
                ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
                ImGui::TableSetupColumn("Step #", ImGuiTableColumnFlags_None);
                ImGui::TableSetupColumn("D* lite", ImGuiTableColumnFlags_None);
                ImGui::TableSetupColumn("A*", ImGuiTableColumnFlags_None);
                ImGui::TableSetupColumn("Diff", ImGuiTableColumnFlags_None);
                ImGui::TableHeadersRow();
                for (std::size_t i = 0; i < aCache->nodesExpandedAll.size(); ++i)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(std::to_string(i).c_str());
                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text(std::to_string(dCache->nodesExpandedAll[i].size()).c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text(std::to_string(aCache->nodesExpandedAll[i].size()).c_str());
                    ImGui::TableSetColumnIndex(3);
                    int32_t diff = static_cast<int32_t>(aCache->nodesExpandedAll[i].size() -
                                                        dCache->nodesExpandedAll[i].size());
                    ImGui::Text(std::to_string(diff).c_str());
                }
                ImGui::EndTable();
            }
        }
    }
}
