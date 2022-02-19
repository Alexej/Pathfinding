#include <imgui-SFML.h>
#include <imgui.h>
#include <format>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"
#include "GraphDimension.hpp"
#include "AlgorithmStepSpeed.hpp"
#include "Node.hpp"
#include "IApplicationState.hpp"

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
    using Pathfinding::Abstract::IApplicationState;

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
    Menu::Menu(std::shared_ptr<IApplicationState> appStateSPtr_, int32_t offset_, int32_t height_, int32_t width_)
        : appStateSPtr(appStateSPtr_), offset(static_cast<float>(offset_)),
          height(static_cast<float>(height_)),
          width(static_cast<float>(width_))
    {
        dimensionPtr = &appStateSPtr->dimension();
        algoStepSpeedPtr = &appStateSPtr->algorithmStepSpeed();
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

        switch (appStateSPtr->currentState())
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
        nodeInfo = appStateSPtr->showNodeInfo();
        if (ImGui::Checkbox("Render Node Info", &nodeInfo))
        {
            if (nodeInfo)
            {
                appStateSPtr->enableNodeInfo();
            }
            else
            {
                appStateSPtr->disableNodeInfo();
            }
        }
    }

    void Menu::showAutoStepFlag()
    {
        autoStep = appStateSPtr->autoStep();
        if (ImGui::Checkbox("Auto step", &autoStep))
        {
            if (autoStep)
            {
                appStateSPtr->enableAutoStep();
            }
            else
            {
                appStateSPtr->disableAutoStep();
            }
        }
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
        if (appStateSPtr->nodeUnderCursor() != nullptr)
        {
            ImGui::Separator();
            showNodeInfoInMenu();
            ImGui::Separator();
        }
        printLargeText(std::format("State: {}", mapStateToText(appStateSPtr->currentState())), 2);
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
                appStateSPtr->disableNodeInfo();
                nodeInfo = false;
            }
        }
    }

    void Menu::showNodeInfoInMenu()
    {
        ImGui::Text(std::format("Height: {} Width: {}", appStateSPtr->nodeUnderCursor()->location.height,
                                appStateSPtr->nodeUnderCursor()->location.width)
                        .c_str());
        ImGui::Text(std::format("G: {}", appStateSPtr->nodeUnderCursor()->g).c_str());
        ImGui::Text(std::format("RHS: {}", appStateSPtr->nodeUnderCursor()->rhs).c_str());
        ImGui::Text(std::format("K1: {}", appStateSPtr->nodeUnderCursor()->key.k1).c_str());
        ImGui::Text(std::format("K2: {}", appStateSPtr->nodeUnderCursor()->key.k2).c_str());
        ImGui::Text(std::format("State: {}", mapNodeStateToText(appStateSPtr->nodeUnderCursor()->state)).c_str());
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
        showPath = appStateSPtr->showPath();
        if (ImGui::Checkbox("Render path", &showPath))
        {
            if (showPath)
            {
                appStateSPtr->enablePath();
            }
            else
            {
                appStateSPtr->disablePath();
            }
        }

        showPathLines = appStateSPtr->showPathLines();
        if (showPath)
        {
            if (ImGui::Checkbox("Render path lines", &showPathLines))
            {
                if (showPathLines)
                {
                    appStateSPtr->enablePathLines();
                }
                else
                {
                    appStateSPtr->disablePathLines();
                }
            }
        }
    }
}