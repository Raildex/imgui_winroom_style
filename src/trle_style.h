#pragma once

#include "imgui.h"

// Tomb Raider Level Editor (Core Design / NGLE) inspired Dear ImGui theme.
namespace trle {

// Signature NGLE accent colours
inline constexpr ImVec4 Gold   = ImVec4(0.84f, 0.69f, 0.16f, 1.00f); // "Play"
inline constexpr ImVec4 Cyan   = ImVec4(0.28f, 0.72f, 0.72f, 1.00f); // "New Up" / "New Down"
inline constexpr ImVec4 Green  = ImVec4(0.22f, 0.72f, 0.22f, 1.00f); // "Backup Project"
inline constexpr ImVec4 Purple = ImVec4(0.62f, 0.24f, 0.62f, 1.00f); // "Refresh"
inline constexpr ImVec4 Red    = ImVec4(0.85f, 0.00f, 0.00f, 1.00f); // "SYSTEM REQUEST" banner

// Applies the sharp, grey, 1px-bordered 90s tool look to the current context.
void ApplyStyle();

// Draws a raised (or sunken) 1px bevel around the last submitted item.
void DrawBevel(bool sunken = false);

// Beveled button with an optional accent tint (e.g. &trle::Gold).
bool Button(const char* label, const ImVec2& size = ImVec2(0, 0),
            const ImVec4* customColor = nullptr);

// Red-titled modal with a message and a Cancel button.
// Call every frame; open it with ImGui::OpenPopup(id).
void SystemRequestModal(const char* id, const char* message);

} // namespace trle
