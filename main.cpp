#include <stdexcept>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

void setup_glfw() {
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");
}

GLFWwindow* create_window(int width, int height, const char* title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);  // OpenGL ES 2.0 for Raspberry Pi
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
        throw std::runtime_error("Failed to create GLFW window");
    glfwMakeContextCurrent(window);
    return window;
}

void setup_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 100");
}

void cleanup(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    setup_glfw();
    GLFWwindow* window = create_window(800, 600, "ImGui Test");
    setup_imgui(window);
    
    bool show_window = true;
    float slider_value = 0.0f;
    char text_input[128] = "Hello, ImGui!";
    bool checkbox_value = false;
    int counter = 0;
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if (show_window) {
            ImGui::Begin("My First ImGui Window", &show_window);
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("Float Slider", &slider_value, 0.0f, 1.0f);
            ImGui::InputText("Text Input", text_input, IM_ARRAYSIZE(text_input));
            ImGui::Checkbox("Check me!", &checkbox_value);
            if (ImGui::Button("Click Me!")) {
                counter++;
            }
            ImGui::SameLine();
            ImGui::Text("Clicked %d times", counter);
            if (ImGui::Button("Close")) {
                show_window = false;
            }
            ImGui::End();
        }
        
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    
    cleanup(window);
    return 0;
}
