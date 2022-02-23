#include <imgui-SFML.h>
#include <imgui.h>
#include <format>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"
#include "Node.hpp"

/*
https://eliasdaler.github.io/using-imgui-with-sfml-pt2/#combobox-listbox
*/
namespace ImGui
{
    static auto vector_getter = [](void* vec, int idx, const char** out_text)
    {
        auto& vector = *static_cast<std::vector<std::string>*>(vec);
        if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
        *out_text = vector.at(idx).c_str();
        return true;
    };

    bool custom_combo(const char* label, int* currIndex, std::vector<std::string>& values)
    {
        if (values.empty()) { return false; }
        return Combo(label, currIndex, vector_getter,
            static_cast<void*>(&values), static_cast<int32_t>(values.size()));
    }
}


namespace Pathfinding::Gui
{
    using namespace Pathfinding::Constants;
    using Pathfinding::Core::ApplicationState;
    using Pathfinding::Core::State;
    using Pathfinding::Datastructures::Node;
    using Pathfinding::Datastructures::NodeState;
    using Pathfinding::Core::AlgorithmStepSpeed;

    namespace
    {
        std::string mapNodeStateToText(NodeState state)
        {
            std::string str;
            switch (state)
            {
            case NodeState::Blocked:
                str = "Blocked";
                break;
            case NodeState::Free:
                str = "Free";
                break;
            case NodeState::Frontier:
                str = "Frontier";
                break;
            case NodeState::Goal:
                str = "Goal";
                break;
            case NodeState::Start:
                str = "Start";
                break;
            case NodeState::Visited:
                str = "Visited";
                break;
            }
            return str;
        }

        std::string mapStateToText(State state)
        {
            std::string str;
            switch (state)
            {
            case State::READY:
                str = "READY";
                break;
            case State::SEARCHING:
                str = "SEARCHING";
                break;
            case State::DONE:
                str = "DONE";
                break;
            case State::NO_PATH:
                str = "NO_PATH";
                break;
            }
            return str;
        }
    }
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
                nodeInfo = false;
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

    void Menu::printLargeText(std::string text, double factor)
    {
        ImGui::SetWindowFontScale(static_cast<float>(factor));
        ImGui::Text(text.c_str());
        ImGui::SetWindowFontScale(1);
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