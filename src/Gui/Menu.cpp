#include <imgui-SFML.h>
#include <imgui.h>
#include <format>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"
#include "Node.hpp"
#include "GuiHelpers.hpp"
#include "PathfinderCache.hpp"

namespace Pathfinding::Gui
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Core::AlgorithmStepSpeed;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Datastructures::PathfinderCache;
    using Pathfinding::Helpers::getStateColor;
    using Pathfinding::Helpers::mapNodeStateToText;
    using Pathfinding::Helpers::mapStateToText;
    using Pathfinding::Helpers::printLargeText;
    using Pathfinding::Helpers::showStatistic;

    Menu::Menu(ApplicationState *appStatePtr_,
               int32_t offset_,
               int32_t height_,
               int32_t width_,
               PathfinderCache *aCache_,
               PDPathfinderCache *dCache_)
        : appStatePtr(appStatePtr_), offset(static_cast<float>(offset_)),
          height(static_cast<float>(height_)),
          width(static_cast<float>(width_)),
          aCache(aCache_),
          dCache(dCache_)
    {
        dimensionPtr = &appStatePtr->dimension;
        algoStepSpeedPtr = &appStatePtr->stepSpeed;
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
        case State::READY:
            showReadyStateElements();
            break;
        case State::SEARCHING:
            showSearchingElements();
            break;
        }

        ImGui::Spacing();
        ImGui::Separator();
        showCommonElements();
        ImGui::Separator();

        if (appStatePtr->currentState == State::DONE)
        {
            showDoneState();
        }
        ImGui::End();
    }

    void Menu::showSearchingElements()
    {
        ImGui::Spacing();
        if (ImGui::Button("STEP", ImVec2(width - 20, 20)))
        {
            stepCallBack();
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
        std::vector<float> valuesFloat(values.begin(), values.end());
        ImGui::Text(name.c_str());
        ImGui::PlotLines(std::format("last : {}.", std::to_string(values.back())).c_str(),
                         &valuesFloat[0],
                         static_cast<int32_t>(values.size()));
    }

    void Menu::showCommonElements()
    {
        if (ImGui::CollapsingHeader("Runtime Options"))
        {
            showAlgorithmStepSpeedComboBox();
            ImGui::Spacing();
            showAutoStepFlag();
            ImGui::Spacing();
            showPathFlags();
            ImGui::Spacing();
            if (dimensionPtr->canShowNodeInfo())
            {
                showNodeInfoFlag();
            }
            if (appStatePtr->runAStar)
            {
                showAStarPath();
            }
        }
        if (ImGui::CollapsingHeader("Node info"))
        {
            ImGui::Spacing();
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

        ImGui::Spacing();
        if (ImGui::Button("RESET", ImVec2(width - 20, 20)))
        {
            resetCallback();
        }

        if (appStatePtr->currentState != State::READY)
        {
            if (appStatePtr->runAStar)
            {
                showGraph(aCache->nodesExpandedAll, "A* nodes Expanded");
            }
            showGraph(dCache->nodesExpandedAll, "D* nodes Expanded");
        }
    }

    void Menu::showAlgorithmStepSpeedComboBox()
    {
        static int32_t itemCurrentSpeed = algoStepSpeedPtr->getCurrentStepSpeedIndex();
        auto speeds = algoStepSpeedPtr->getStepSpeedVecString();
        if (ImGui::custom_combo("StepSpeed", &itemCurrentSpeed, speeds))
        {
            algoStepSpeedPtr->setCurrentAlgorithmStepSpeedIndex(itemCurrentSpeed);
        }
    }

    void Menu::showNumberOfNodesComboBox()
    {
        static int32_t itemCurrentNumberOfNodes = dimensionPtr->currentNumberOfNodesIndex();
        auto numberOfNodesInRow = dimensionPtr->getNumberOfNodesInRowString();
        if (ImGui::custom_combo("NumberOfNodes", &itemCurrentNumberOfNodes, numberOfNodesInRow))
        {
            numberOfNodesChangedCallBack(itemCurrentNumberOfNodes);
            if (!dimensionPtr->canShowNodeInfo())
            {
                appStatePtr->showNodeInfo = false;
            }
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
            ImGui::Spacing();
            showNumberOfNodesComboBox();
            ImGui::Checkbox("Run A*", &appStatePtr->runAStar);
            ImGui::SameLine();
            ImGui::HelpMarker("A* is run at every step of D* lite,\nat the end statistic is provided");
        }

        ImGui::Spacing();
        if (ImGui::Button("Start", ImVec2(width - 20, 20)))
        {
            startCallBack();
        }

        if (ImGui::Button("RANDOM GRAPH", ImVec2(width - 20, 20)))
        {
            randomGraphCallBack();
        }
    }

    void Menu::addNumberOfNodesChangedCallBack(fPtrVI callBack)
    {
        numberOfNodesChangedCallBack = callBack;
    }

    void Menu::addStartCallBack(fPtrVV callBack)
    {
        startCallBack = callBack;
    }

    void Menu::addResetCallBack(fPtrVV callBack)
    {
        resetCallback = callBack;
    }

    bool Menu::initialized() const
    {
        return numberOfNodesChangedCallBack != nullptr && startCallBack != nullptr;
    }

    void Menu::addStepCallBack(fPtrVV callBack)
    {
        stepCallBack = callBack;
    }

    void Menu::addRandomGraphCallBack(fPtrVV callBack)
    {
        randomGraphCallBack = callBack;
    }

    void Menu::showPathFlags()
    {
        ImGui::Checkbox("Render path", &appStatePtr->showPath);
        if (appStatePtr->showPath)
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
                    ImGui::Text(std::to_string(dCache->nodesExpandedAll[i]).c_str());
                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text(std::to_string(aCache->nodesExpandedAll[i]).c_str());
                    ImGui::TableSetColumnIndex(3);
                    int32_t diff = aCache->nodesExpandedAll[i] - dCache->nodesExpandedAll[i];
                    ImGui::Text(std::to_string(diff).c_str());
                }
                ImGui::EndTable();
            }
        }
    }
}
