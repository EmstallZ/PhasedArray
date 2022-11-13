#pragma once
#include "settings_backend.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <iterator>

namespace SettingsMenu
{
    extern std::vector<Element> elementArray;
    static void HelpMarker(const char* desc);
    void RenderSettingsMenu();
}
