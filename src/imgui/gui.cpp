#include "gui.h"

extern "C" {
#include "../global.h"
#include "../config/config.h"
}

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

static const char* EFFECTS[] = {
    "Prismo", "Breathe", "Steady", "Neon", "Tail",
    "Colorful Tail", "Stream", "Reaction", "Heart", "LED Off"
};

static void setup_style(void) {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding    = 10.0f;
    style.FrameRounding     = 6.0f;
    style.GrabRounding      = 6.0f;
    style.PopupRounding     = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.WindowPadding     = ImVec2(18, 18);
    style.FramePadding      = ImVec2(10, 6);
    style.ItemSpacing       = ImVec2(10, 8);
    style.ItemInnerSpacing  = ImVec2(8, 6);

    ImVec4* c = style.Colors;
    c[ImGuiCol_WindowBg]         = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
    c[ImGuiCol_PopupBg]          = ImVec4(0.11f, 0.11f, 0.14f, 0.98f);
    c[ImGuiCol_Border]           = ImVec4(0.24f, 0.24f, 0.30f, 0.60f);
    c[ImGuiCol_FrameBg]          = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
    c[ImGuiCol_FrameBgHovered]   = ImVec4(0.22f, 0.22f, 0.30f, 1.00f);
    c[ImGuiCol_FrameBgActive]    = ImVec4(0.26f, 0.26f, 0.36f, 1.00f);
    c[ImGuiCol_Button]           = ImVec4(0.36f, 0.40f, 0.90f, 1.00f);
    c[ImGuiCol_ButtonHovered]    = ImVec4(0.44f, 0.48f, 0.98f, 1.00f);
    c[ImGuiCol_ButtonActive]     = ImVec4(0.30f, 0.34f, 0.80f, 1.00f);
    c[ImGuiCol_Header]           = ImVec4(0.36f, 0.40f, 0.90f, 0.55f);
    c[ImGuiCol_HeaderHovered]    = ImVec4(0.44f, 0.48f, 0.98f, 0.80f);
    c[ImGuiCol_HeaderActive]     = ImVec4(0.44f, 0.48f, 0.98f, 1.00f);
    c[ImGuiCol_SliderGrab]       = ImVec4(0.44f, 0.48f, 0.98f, 1.00f);
    c[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.58f, 1.00f, 1.00f);
    c[ImGuiCol_CheckMark]        = ImVec4(0.55f, 0.58f, 1.00f, 1.00f);
    c[ImGuiCol_Separator]        = ImVec4(0.24f, 0.24f, 0.30f, 1.00f);
}

void run_gui(void) {
    if (!glfwInit()) {
        fprintf(stderr, "error: no se pudo inicializar GLFW (revisa DISPLAY/WAYLAND_DISPLAY)\n");
        return;
    }

    const int width = 440, height = 380;
    GLFWwindow* window = glfwCreateWindow(width, height, "Aquila Air", NULL, NULL);
    if (!window) {
        fprintf(stderr, "error: no se pudo crear la ventana\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (GLFWmonitor* monitor = glfwGetPrimaryMonitor()) {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().FontGlobalScale = 1.15f;
    setup_style();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Aquila Air", NULL,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoCollapse);

        bool changed = false;
        float avail = ImGui::GetContentRegionAvail().x;

        ImGui::TextColored(ImVec4(0.55f, 0.58f, 1.00f, 1.00f), "AQUILA AIR");
        ImGui::TextDisabled("VSG Gaming Mouse");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        float color[3] = {
            packet.body.colors[0].r / 255.0f,
            packet.body.colors[0].g / 255.0f,
            packet.body.colors[0].b / 255.0f,
        };
        ImGui::Text("LED color");
        ImGui::SetNextItemWidth(avail);
        if (ImGui::ColorEdit3("##color", color)) {
            Color c = {
                (uint8_t)(color[0] * 255),
                (uint8_t)(color[1] * 255),
                (uint8_t)(color[2] * 255),
            };
            for (int i = 0; i < 7; i++)
                packet.body.colors[i] = c;
            changed = true;
        }

        ImGui::Spacing();
        ImGui::Text("Light effect");
        ImGui::SetNextItemWidth(avail);
        int effect = packet.body.led_mode;
        if (ImGui::Combo("##effect", &effect, EFFECTS, IM_ARRAYSIZE(EFFECTS))) {
            packet.body.led_mode = (uint8_t)effect;
            changed = true;
        }

        ImGui::Spacing();
        ImGui::Text("LED light");
        uint8_t light_min = 0, light_max = 10;
        ImGui::SetNextItemWidth(avail);
        changed |= ImGui::SliderScalar("##light", ImGuiDataType_U8, &packet.body.led_light, &light_min, &light_max);

        ImGui::Spacing();
        ImGui::Text("LED speed");
        uint8_t speed_max = 2;
        ImGui::SetNextItemWidth(avail);
        changed |= ImGui::SliderScalar("##speed", ImGuiDataType_U8, &packet.body.led_speed, &light_min, &speed_max);

        if (changed)
            apply_config();

        ImGui::End();

        ImGui::Render();
        int fb_w, fb_h;
        glfwGetFramebufferSize(window, &fb_w, &fb_h);
        glViewport(0, 0, fb_w, fb_h);
        glClearColor(0.09f, 0.09f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
