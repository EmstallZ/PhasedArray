#define _USE_MATH_DEFINES

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
        // Change default colourmap 
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
        ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);

        // Variables to reverse colormap 
        static bool reverseColormap = false;
        static ImPlotColormapScaleFlags colormapFlags = 0;
        static double colormapMinValue = -2, colormapMaxValue = 2;
        double colormapMin = reverseColormap ? colormapMaxValue : colormapMinValue;
        double colormapMax = reverseColormap ? colormapMinValue : colormapMaxValue;

        // Create plot window
        static float plotHeight = ImGui::GetContentRegionAvail().y - 50 - ImGui::GetStyle().ItemSpacing.y;
        if (ImPlot::BeginPlot("##Plot", ImVec2(ImGui::GetContentRegionAvail().x - 64 - ImGui::GetStyle().ItemSpacing.x, plotHeight), ImPlotFlags_NoTitle | ImPlotFlags_Equal | ImPlotFlags_NoLegend))
        {
            static double timeShift;
            int ms = static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
            static int oldms = 0;
            // Add time (phase) shift to make the wave 'move'
            if (ms - oldms >= 10)
            {
                timeShift += 0.05;
                oldms = ms;
            }

            constexpr int plotSize = 200;
            static double plotArray[plotSize * plotSize];
            if (SettingsMenu::elementArray.size() >= 1)
            {
                Element firstElement = SettingsMenu::elementArray[0];
                for (int y = 0; y < plotSize; y++) {
                    for (int x = 0; x < plotSize; x++) {
                        ImVec2 elementPos(0.5, 0.5);

                        // Comment out the line below if you dont want the wave ontop of your mouse
                        elementPos = ImVec2(static_cast<float>(ImPlot::GetPlotMousePos().x), static_cast<float>(1.0 - ImPlot::GetPlotMousePos().y));

                        double elementDistance = std::sqrt(std::pow(y - (plotSize * elementPos.y), 2) + std::pow(x - (plotSize * elementPos.x), 2));
                        plotArray[(y * plotSize) + x] = *firstElement.getAmplitudePointer() * std::sin(2 * M_PI * *firstElement.getFrequencyPointer() * elementDistance / plotSize + *firstElement.getPhasePointer() - timeShift);
                    }
                }
                ImPlot::PlotHeatmap("Heatmap", plotArray, plotSize, plotSize, colormapMin, colormapMax, nullptr);
            }

            ImPlot::EndPlot();
        }

        // Colormap scale
        ImGui::SameLine(); ImPlot::ColormapScale("##HeatScale", colormapMin, colormapMax, ImVec2(0, plotHeight), "%g", colormapFlags);

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
        // TODO: add ImVec2 to element class for its position
        // TODO: center plotimage at 0,0
        // TODO: add multiple selectable plots
        // TODO: add pause checkbox for the time shift
        // TODO: add parallelization when adding multiple arrays, or even better, when calculating the plot itself


        //ImPlot::ShowDemoWindow();

        ImGui::End();
    }
}
