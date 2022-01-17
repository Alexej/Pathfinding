#include "Menu.hpp"
#include "ApplicationState.hpp"
#include <imgui-SFML.h>
#include <imgui.h>

namespace Pathfinding::Core
{
    Menu::Menu(ApplicationState * appStat_, int32_t offset_, int32_t height_, int32_t width_)
    : appStatePtr(appStat_), offset(offset_), height(height_), width(width_) {}

    void Menu::show()
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;

        ImGui::SetNextWindowPos(ImVec2(offset, 0), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);

        ImGui::Begin("Configuration",nullptr, window_flags);    

        ImGui::BulletText("CTRL+Z,CTRL+Y to undo/redo.");
        ImGui::BulletText("ESCAPE to revert.");
        ImGui::BulletText("You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.");
        ImGui::Unindent();
        ImGui::BulletText("With keyboard navigation enabled:");


        ImGui::End();

    }
}