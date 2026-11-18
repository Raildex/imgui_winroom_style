// TRLE-style Dear ImGui demo (GLFW + OpenGL3)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "trle_style.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>

static void GlfwErrorCallback(int error, const char* description) {
    std::fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

// A mock of the TRLE right-hand command panel
static void DrawEditorPanel() {
    ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(250, 360), ImGuiCond_FirstUseEver);

    // White text on the red title bar, black text in the body
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    const bool open = ImGui::Begin("Room Editor");
    ImGui::PopStyleColor();

    if (open) {
        const ImVec2 btn(110, 20);

        ImGui::TextUnformatted("Project");
        ImGui::Separator();
        if (trle::Button("Play", btn, &trle::Gold)) {
            ImGui::OpenPopup("SYSTEM REQUEST");
        }
        ImGui::SameLine();
        trle::Button("Backup Project", btn, &trle::Green);
        trle::Button("Refresh", btn, &trle::Purple);
        ImGui::SameLine();
        trle::Button("Load Project", btn);

        ImGui::Spacing();
        ImGui::TextUnformatted("Rooms");
        ImGui::Separator();
        trle::Button("New Up", btn, &trle::Cyan);
        ImGui::SameLine();
        trle::Button("New Down", btn, &trle::Cyan);
        trle::Button("Flip", btn);
        ImGui::SameLine();
        trle::Button("Water", btn);

        ImGui::Spacing();
        ImGui::TextUnformatted("Properties");
        ImGui::Separator();

        static int   roomHeight = 20;
        static float ambient    = 0.6f;
        static bool  outside    = true;
        static bool  quicksand  = false;
        static char  roomName[32] = "Room 0";

        ImGui::SetNextItemWidth(-1);
        ImGui::InputText("##name", roomName, sizeof(roomName));
        trle::DrawBevel(true); // sunken value box

        ImGui::SetNextItemWidth(140);
        ImGui::SliderInt("Height", &roomHeight, 1, 31);
        ImGui::SetNextItemWidth(140);
        ImGui::SliderFloat("Ambient", &ambient, 0.0f, 1.0f, "%.2f");
        ImGui::Checkbox("Outside", &outside);
        ImGui::SameLine();
        ImGui::Checkbox("Quicksand", &quicksand);

        ImGui::Spacing();
        if (ImGui::CollapsingHeader("Texture Info")) {
            ImGui::BulletText("Tile: 42");
            ImGui::BulletText("Page: 3");
        }

        // The modal must be submitted from inside the window that opened it
        trle::SystemRequestModal("SYSTEM REQUEST", "Arg list too big");
    }
    ImGui::End();
}

int main() {
    glfwSetErrorCallback(GlfwErrorCallback);
    if (!glfwInit()) return 1;

#if defined(__APPLE__)
    const char* glslVersion = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    const char* glslVersion = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    GLFWwindow* window = glfwCreateWindow(1024, 640, "TRLE ImGui Style", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; // keep the demo stateless
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // The default ProggyClean bitmap font suits the 90s look well.
    // For a closer match, load a small Tahoma/MS Sans Serif-like TTF here:
    // io.Fonts->AddFontFromFileTTF("fonts/tahoma.ttf", 13.0f);

    trle::ApplyStyle();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    bool showImGuiDemo = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) glfwSetWindowShouldClose(window, GLFW_TRUE);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("ImGui Demo Window", nullptr, &showImGuiDemo);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        DrawEditorPanel();
        if (showImGuiDemo) ImGui::ShowDemoWindow(&showImGuiDemo);

        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.16f, 0.16f, 0.16f, 1.0f); // dark 3D-viewport backdrop
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
