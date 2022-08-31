#include "settings_window.h"
#include "settings_backend.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <iterator>

namespace SettingsMenu
{
    // Settings window flags
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = true;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = true;
    static bool no_close = true;
    static bool no_nav = true;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool no_docking = false;
    static bool unsaved_document = false;
    static bool defaultWindowPosition = false;

    std::vector<Element> elementArray;
    char elementsCounterBuffer[50] = "Elements: 0";
    int selectedElement = 0;
    bool disable = false;
    int uniqueIdCounter = 0;
    bool isDeletedElementLast = false;

    void RenderSettingsMenu()
    {
        // Dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // Setting window start position
        if (defaultWindowPosition)
        {
            const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_Once);
            ImGui::SetNextWindowSize(ImVec2(300, 680), ImGuiCond_Once);
        }
        // Settings window flags
        ImGuiWindowFlags window_flags = 0;
        if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
        if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
        if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
        if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
        if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
        if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
        if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
        if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
        if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
        if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

        // Start menu
        ImGui::Begin("Settings", NULL, window_flags);

        if (ImGui::Button("Add element"))
        {
            // Call element constructor with unique name
            elementArray.push_back(Element::Element("Placeholder", uniqueIdCounter++));
            // Needed in order to make the delete button available again
            isDeletedElementLast = false;
            
        }
        sprintf(elementsCounterBuffer, "Elements: %d", (int)elementArray.size());
        ImGui::SameLine();
        // Display element counter
        ImGui::Text(elementsCounterBuffer);

        // Element box
        if (ImGui::BeginListBox("##Element box", ImVec2(-FLT_MIN, 8 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int n = 0; n < elementArray.size(); n++)
            {
                // Set which element is selected
                const bool isSelected = (selectedElement == n);
                char selectableBuffer[50];
                sprintf(selectableBuffer, "UID: %d, Name: %s, Phase: , Amplitude: ", elementArray[n].getUniqueID(), elementArray[n].getName().c_str());
                if (ImGui::Selectable(selectableBuffer, isSelected)) {
                    selectedElement = n;
                    // Needed in order to make the delete button available again
                    isDeletedElementLast = false;
                }
                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndListBox();
        }
 
        ImGui::BeginDisabled(!elementArray.size() || isDeletedElementLast);

        if (ImGui::Button("Delete element"))
        {
            // Check if deleted element is last in array
            isDeletedElementLast = elementArray[selectedElement].getUniqueID() == elementArray.back().getUniqueID();
            elementArray.erase(elementArray.begin() + selectedElement);
        }

        ImGui::EndDisabled();
        

        ImGui::End();

        ImGui::ShowDemoWindow();
    }
}
