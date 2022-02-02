#include <imgui-SFML.h>
#include <imgui.h>

#include "Constants.hpp"
#include "Menu.hpp"
#include "ApplicationState.hpp"
#include "GraphDimension.hpp"
#include "Node.hpp"
#include <format>

using namespace Pathfinding::Constants;
using Pathfinding::Core::ApplicationState;
using Pathfinding::Core::State;
using Pathfinding::Core::NumberOfNodes;
using Pathfinding::Core::NUMBER_OF_NODES_CHAR;
using Pathfinding::Datastructures::Node;
using Pathfinding::Datastructures::NodeState;

namespace Pathfinding::Gui
{
    namespace
    {
        std::string mapNodeStateToText(NodeState state)
        {
            std::string str;
            switch(state)
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
                case NodeState::Path:
                    str = "Path";
                    break;
                case NodeState::Recalculated:
                    str = "Recalculated";
                    break;
            }
            return str;
        }
    }
    Menu::Menu(ApplicationState *appState_, int32_t offset_, int32_t height_, int32_t width_)
        : appStatePtr(appState_), offset(static_cast<float>(offset_)), 
        height(static_cast<float>(height_)), 
        width(static_cast<float>(width_)) 
        {
            dimensionPtr = &appStatePtr->dimension();
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

        switch(appStatePtr->currentState())
        {
            case State::READY:
                showReadyStateElements();
            break;
            case State::SEARCHING:
                showSearchingElements();
            break;

        }

        ImGui::Separator();
        ImGui::Spacing();
        showCommonElements();
        ImGui::End();
    }

    void Menu::showSearchingElements()
    {
        ImGui::Spacing();
        if(ImGui::Button("STEP", ImVec2(width-20,20)))
        {
            stepCallBack();
        }
    }

    void Menu::showNodeInfoFlag()
    {
        nodeInfo = appStatePtr->showNodeInfo();
        if (ImGui::Checkbox("Render Node Info", &nodeInfo))
        {
            if(nodeInfo)
            {
                appStatePtr->enableNodeInfo();
            }
            else
            {
                appStatePtr->disableNodeInfo();
            }
        }
    }

    void Menu::showCommonElements()
    {
        if (dimensionPtr->canShowNodeInfo())
        {
            showNodeInfoFlag();
        }
        ImGui::Spacing();
        if(ImGui::Button("RESET", ImVec2(width-20,20)))
        {
            resetCallback();
        }
        ImGui::Spacing();
        if(appStatePtr->nodeUnderCursor() != nullptr)
        {
            showNodeInfoInMenu();
        }
    }

    void Menu::showNodeInfoInMenu()
    {
        ImGui::Separator();
        ImGui::Text(std::format("Height: {} Width: {}", appStatePtr->nodeUnderCursor()->location.height, 
                                                      appStatePtr->nodeUnderCursor()->location.width).c_str());
        ImGui::Text(std::format("G: {}", appStatePtr->nodeUnderCursor()->g).c_str());
        ImGui::Text(std::format("RHS: {}", appStatePtr->nodeUnderCursor()->rhs).c_str());
        ImGui::Text(std::format("K1: {}", appStatePtr->nodeUnderCursor()->key.k1).c_str());
        ImGui::Text(std::format("K2: {}", appStatePtr->nodeUnderCursor()->key.k2).c_str());
        ImGui::Text(std::format("State: {}", mapNodeStateToText(appStatePtr->nodeUnderCursor()->state)).c_str());
        ImGui::Separator();
    }

    void Menu::showReadyStateElements()
    {
        static int32_t itemCurrent = dimensionPtr->currentNumberOfNodesIndex();
        ImGui::Spacing();
        ImGui::Text("Number of nodes");
        if (ImGui::Combo("", &itemCurrent, NUMBER_OF_NODES_CHAR, IM_ARRAYSIZE(NUMBER_OF_NODES_CHAR)))
        {
            if (dimensionPtr->currentNumberOfNodesIndex() != itemCurrent)
            {
                if (dimensionPtr->canShowNodeInfo())
                {
                    appStatePtr->disableNodeInfo();
                    nodeInfo = false;
                }
                numberOfNodesChangedCallBack(itemCurrent);
            }
        };

        ImGui::Spacing();
        if(ImGui::Button("Start", ImVec2(width-20,20)))
        {
            startCallBack();
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
}