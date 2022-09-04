#include <imgui.h>
#include <implot.h>
#include <iostream>
#include "plot_window.h"

namespace PlotWindow
{
    // Plot window flags
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

    bool isColormapChanged = false;

    void InitializePlotWindow() {
        ImPlot::GetStyle().Colormap = ImPlotColormap_Hot;
    }

    void RenderPlotWindow()
    {
        // Plot window flags
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

        // Plot window
        ImGui::Begin("Plot", NULL, window_flags);

        // Create plot window
        static float plotHeight = ImGui::GetContentRegionAvail().y - 50 - ImGui::GetStyle().ItemSpacing.y;
        if (ImPlot::BeginPlot("Plot", ImVec2(ImGui::GetContentRegionAvail().x - 64 - ImGui::GetStyle().ItemSpacing.x, plotHeight)))
        {
            ImPlot::EndPlot();
        }


        static bool reverseColormap = false;
        static ImPlotColormapScaleFlags colormapFlags = 0;
        static double colormapMinValue = -10, colormapMaxValue = 10;
        ImGui::SameLine(); ImPlot::ColormapScale("##HeatScale", reverseColormap ? colormapMaxValue : colormapMinValue, reverseColormap ? colormapMinValue : colormapMaxValue, ImVec2(0, plotHeight), "%g", colormapFlags);

        ImGui::Separator();

        ImGui::SetNextItemWidth(128);
        ImPlot::ShowColormapSelector("Select colormap");

        ImGui::SameLine();
        ImGui::Checkbox("Reverse heatmap", &reverseColormap);
        if (reverseColormap)
        {
            colormapFlags |= ImPlotColormapScaleFlags_Invert;
        }
        else
        {
            colormapFlags = 0;
        }

        // TODO: add auto adjust colormap scale value button
        // TODO: add manual colormap scale value slider
        // TODO: add ImVec2 to element class
        // TODO: center plotimage at 0,0
        

        ImPlot::ShowDemoWindow();

        ImGui::End();
    }
}
