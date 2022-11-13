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
        if (ImPlot::BeginPlot("##Plot", ImVec2(ImGui::GetContentRegionAvail().x - 64 - ImGui::GetStyle().ItemSpacing.x, plotHeight), ImPlotFlags_NoTitle|ImPlotFlags_Equal))
        {
            static int plotSize = 200;


            if (SettingsMenu::elementArray.size() >= 2)
            {
                std::vector<float> myArray;
                for (int i = 0; i < plotSize; i++)
                {
                    for (int j = 0; j < plotSize; j++)
                    {
                        // The commented line below has a typo in it, but it has some cool effects nonetheless :)
                        //myArray.push_back(sin(j * *SettingsMenu::elementArray[0].getFrequencyPointer() / 100) + *SettingsMenu::elementArray[0].getPhasePointer() + sin(i * *SettingsMenu::elementArray[0].getFrequencyPointer() / 100) + *SettingsMenu::elementArray[0].getPhasePointer());

                        // Sine wave plotted on the X and Y axis
                        myArray.push_back((*SettingsMenu::elementArray[0].getAmplitudePointer() * sin((j * *SettingsMenu::elementArray[0].getFrequencyPointer() / 100) + *SettingsMenu::elementArray[0].getPhasePointer())) + (*SettingsMenu::elementArray[1].getAmplitudePointer() * sin((i * *SettingsMenu::elementArray[1].getFrequencyPointer() / 100) + +*SettingsMenu::elementArray[1].getPhasePointer())));
                    }
                }

                ImPlot::PlotHeatmap("Heatmap", myArray.data(), plotSize, plotSize, colormapMin, colormapMax, NULL);
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
        // TODO: add ImVec2 to element class
        // TODO: center plotimage at 0,0
        

        //ImPlot::ShowDemoWindow();

        ImGui::End();
    }
}
