#include "trle_style.h"
#include "imgui_internal.h" // ImMin

namespace trle {

void ApplyStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // 1. Sharp, zero-rounding 90s geometry
    style.WindowRounding    = 0.0f;
    style.ChildRounding     = 0.0f;
    style.FrameRounding     = 0.0f;
    style.PopupRounding     = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding      = 0.0f;
    style.TabRounding       = 0.0f;

    // 2. Crisp 1px borders everywhere
    style.WindowBorderSize  = 1.0f;
    style.ChildBorderSize   = 1.0f;
    style.PopupBorderSize   = 1.0f;
    style.FrameBorderSize   = 1.0f;

    // 3. Compact, dense tool layout
    style.WindowPadding     = ImVec2(4.0f, 4.0f);
    style.FramePadding      = ImVec2(4.0f, 2.0f);
    style.ItemSpacing       = ImVec2(2.0f, 2.0f);
    style.ItemInnerSpacing  = ImVec2(3.0f, 3.0f);
    style.ScrollbarSize     = 14.0f;
    style.GrabMinSize       = 12.0f;
    style.ButtonTextAlign   = ImVec2(0.5f, 0.5f);

    // 4. Core Design / NGLE colour palette
    const ImVec4 bgMain     = ImVec4(0.51f, 0.51f, 0.51f, 1.00f); // #828282 Panel gray
    const ImVec4 bgFrame    = ImVec4(0.60f, 0.60f, 0.60f, 1.00f); // #999999 Button face
    const ImVec4 bgHover    = ImVec4(0.67f, 0.67f, 0.67f, 1.00f); // #ABABAB Hover highlight
    const ImVec4 bgActive   = ImVec4(0.42f, 0.42f, 0.42f, 1.00f); // #6B6B6B Pressed state
    const ImVec4 bgInput    = ImVec4(0.68f, 0.68f, 0.68f, 1.00f); // #ADADAD Text/value box
    const ImVec4 borderDark = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // #1F1F1F Hard 1px outline
    const ImVec4 textBlack  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // #000000 Crisp black text

    colors[ImGuiCol_Text]                 = textBlack;
    colors[ImGuiCol_TextDisabled]         = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    colors[ImGuiCol_WindowBg]             = bgMain;
    colors[ImGuiCol_ChildBg]              = bgMain;
    colors[ImGuiCol_PopupBg]              = bgFrame;
    colors[ImGuiCol_Border]               = borderDark;
    colors[ImGuiCol_BorderShadow]         = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);

    colors[ImGuiCol_FrameBg]              = bgInput;
    colors[ImGuiCol_FrameBgHovered]       = bgHover;
    colors[ImGuiCol_FrameBgActive]        = bgActive;

    colors[ImGuiCol_TitleBg]              = Red;
    colors[ImGuiCol_TitleBgActive]        = Red;
    colors[ImGuiCol_TitleBgCollapsed]     = bgMain;
    colors[ImGuiCol_MenuBarBg]            = bgFrame;

    colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]        = bgFrame;
    colors[ImGuiCol_ScrollbarGrabHovered] = bgHover;
    colors[ImGuiCol_ScrollbarGrabActive]  = bgActive;

    colors[ImGuiCol_CheckMark]            = textBlack;
    colors[ImGuiCol_SliderGrab]           = bgFrame;
    colors[ImGuiCol_SliderGrabActive]     = Gold;

    colors[ImGuiCol_Button]               = bgFrame;
    colors[ImGuiCol_ButtonHovered]        = bgHover;
    colors[ImGuiCol_ButtonActive]         = bgActive;

    colors[ImGuiCol_Header]               = bgFrame;
    colors[ImGuiCol_HeaderHovered]        = bgHover;
    colors[ImGuiCol_HeaderActive]         = Gold;

    colors[ImGuiCol_Separator]            = borderDark;
    colors[ImGuiCol_ResizeGrip]           = bgFrame;
    colors[ImGuiCol_ResizeGripHovered]    = bgHover;
    colors[ImGuiCol_ResizeGripActive]     = bgActive;
}

void DrawBevel(bool sunken) {
    ImDrawList* draw = ImGui::GetWindowDrawList();
    const ImVec2 pMin = ImGui::GetItemRectMin();
    const ImVec2 pMax = ImGui::GetItemRectMax();

    const ImU32 light = IM_COL32(215, 215, 215, 255);
    const ImU32 dark  = IM_COL32(30, 30, 30, 255);

    const ImU32 topLeft     = sunken ? dark : light;
    const ImU32 bottomRight = sunken ? light : dark;

    // 1px strips as filled rects so they land exactly on pixel rows/columns
    // (AddLine on integer coordinates straddles two pixels and looks blurry).
    // Top and left edges
    draw->AddRectFilled(pMin, ImVec2(pMax.x, pMin.y + 1), topLeft);
    draw->AddRectFilled(pMin, ImVec2(pMin.x + 1, pMax.y), topLeft);

    // Bottom and right edges
    draw->AddRectFilled(ImVec2(pMin.x, pMax.y - 1), pMax, bottomRight);
    draw->AddRectFilled(ImVec2(pMax.x - 1, pMin.y), pMax, bottomRight);
}

bool Button(const char* label, const ImVec2& size, const ImVec4* customColor) {
    if (customColor) {
        const ImVec4& c = *customColor;
        ImGui::PushStyleColor(ImGuiCol_Button, c);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(
            ImMin(c.x + 0.08f, 1.0f),
            ImMin(c.y + 0.08f, 1.0f),
            ImMin(c.z + 0.08f, 1.0f), 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(
            c.x * 0.80f, c.y * 0.80f, c.z * 0.80f, 1.0f));
    }

    // No frame border (and its light 1px shadow): the bevel is the only edge,
    // so neighbouring buttons sit flush against each other.
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    const bool pressed = ImGui::Button(label, size);
    ImGui::PopStyleVar();
    DrawBevel(ImGui::IsItemActive());

    if (customColor) {
        ImGui::PopStyleColor(3);
    }
    return pressed;
}

void SystemRequestModal(const char* id, const char* message) {
    ImGui::SetNextWindowSize(ImVec2(240, 115), ImGuiCond_Always);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White title text
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.0f, 4.0f));

    if (ImGui::BeginPopupModal(id, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(); // Restore black body text

        ImGui::Spacing();
        ImGui::TextUnformatted(message);

        // Cancel button in the bottom-right corner
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 78.0f,
                                   ImGui::GetWindowHeight() - 32.0f));
        if (Button("Cancel", ImVec2(70.0f, 24.0f))) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    } else {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
}

} // namespace trle
