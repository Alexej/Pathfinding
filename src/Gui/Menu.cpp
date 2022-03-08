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


namespace Pathfinding::Gui
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Core::AlgorithmStepSpeed;
    using Pathfinding::Helpers::mapNodeStateToText;
    using Pathfinding::Helpers::mapStateToText;
    using Pathfinding::Helpers::printLargeText;

    Menu::Menu(ApplicationState * appStatePtr_, int32_t offset_, int32_t height_, int32_t width_)
    : appStatePtr(appStatePtr_), offset(static_cast<float>(offset_)),
        height(static_cast<float>(height_)),
        width(static_cast<float>(width_))
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
        case State::DONE:
            break;
        }

        ImGui::Separator();
        ImGui::Spacing();
        showCommonElements();
        ImGui::Separator();
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
    }

    void Menu::showAutoStepFlag()
    {
        ImGui::Checkbox("Auto step", &appStatePtr->autoStep);
    }

    void Menu::showCommonElements()
    {
        ImGui::Spacing();
        showAlgorithmStepSpeedComboBox();
        showAutoStepFlag();
        ImGui::Spacing();
        showPathFlags();
        ImGui::Spacing();
        if (dimensionPtr->canShowNodeInfo())
        {
            showNodeInfoFlag();
        }
        ImGui::Spacing();
        if (appStatePtr->nodeUnderCursor != nullptr)
        {
            ImGui::Separator();
            showNodeInfoInMenu();
            ImGui::Separator();
        }
        printLargeText(std::format("State: {}", mapStateToText(appStatePtr->currentState)), 2);
        ImGui::Spacing();
        if (ImGui::Button("RESET", ImVec2(width - 20, 20)))
        {
            resetCallback();
        }
    }

    void Menu::showAlgorithmStepSpeedComboBox()
    {
        static int32_t itemCurrentSpeed = algoStepSpeedPtr->getCurrentStepSpeedIndex();
        auto speeds = algoStepSpeedPtr->getStepSpeedVecString();
        if(ImGui::custom_combo("StepSpeed", &itemCurrentSpeed, speeds))
        {
            algoStepSpeedPtr->setCurrentAlgorithmStepSpeedIndex(itemCurrentSpeed);
        }
    }


    void Menu::showNumberOfNodesComboBox()
    {
        static int32_t itemCurrentNumberOfNodes = dimensionPtr->currentNumberOfNodesIndex();
        auto numberOfNodesInRow = dimensionPtr->getNumberOfNodesInRowString();
        if(ImGui::custom_combo("NumberOfNodes", &itemCurrentNumberOfNodes, numberOfNodesInRow))
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
        ImGui::Text(std::format("State: {}", mapNodeStateToText(appStatePtr->nodeUnderCursor->state)).c_str());
    }

    void Menu::showReadyStateElements()
    {
        ImGui::Spacing();
        showNumberOfNodesComboBox();

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
}