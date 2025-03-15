#include <iostream>
#include <GLFW/glfw3.h>
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include <chrono>

// OpenGL version
const char* glsl_version = "#version 330";

// Window resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void CheckTag(std::string tagName, int tagIntensity, std::string& currentString, std::string& targetString, float& typeSpeed,
    int& currentIndex) {
    std::cout << "Tag: " << tagName << std::endl;
    if (tagName == "clear") {
        currentString = "";
    }
    else if (tagName == "end") {
        targetString = currentString;
    }
    else if (tagName == "speed") {
        //typeSpeed *= (float)tagIntensity;
    }
    else if (tagName == "skip") {
        currentIndex = currentIndex + tagIntensity;
    }
}

int main()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window with OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui + OpenGL + GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Initialize ImGui for OpenGL and GLFW
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::string targetString = "This is my target<clear> stri<skip:5>ng, This is a veryyyyy looooooooooooooooooooong stringgggggggggggggggggggg";
    std::string currentString = "";
    float timeToType = 3.5f;  // 3.5 seconds
    float typeSpeed = (((float)timeToType) / (float)targetString.length()) * 1000;

    int currentIndex = 0;

    auto startTime = std::chrono::high_resolution_clock::now();
    bool isTypingString = true;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll events
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (isTypingString) {
            if (currentString == targetString) {
                isTypingString = false;
                currentIndex = 0;
                goto SKIP_TYPING;
            }

            auto currentTime = std::chrono::high_resolution_clock::now();
            int elapsedTime = (int)std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count(); // Total elapsed time
            if ((elapsedTime / (1 + currentIndex)) >= typeSpeed) {
                if (targetString[currentIndex] == '<') {
                    int l_currentIndex = currentIndex + 1;
                    std::string tagName = "";
                    int tagIntensity = (int)'0';
                    while (targetString[l_currentIndex] != '>') {
                        if (targetString[l_currentIndex] == ':') {
                            tagIntensity = (int)targetString[l_currentIndex + 1] - tagIntensity;
                            l_currentIndex += 2;
                            continue;
                        }
                        tagName += targetString[l_currentIndex];
                        l_currentIndex++;
                    }
                    currentIndex = l_currentIndex + 1;
                    CheckTag(tagName, tagIntensity, currentString, targetString, typeSpeed, currentIndex);
                }
                if (currentIndex >= targetString.length()) {
                    isTypingString = false;
                    goto SKIP_TYPING;
                }
                currentString += targetString[currentIndex];
                currentIndex++;
            }
        }
        SKIP_TYPING:

        // UI Elements
        static bool show_demo = false;
        static float slider_value = 0.5f;
        static bool checkbox_value = false;

        ImGui::Begin("Main Window");
        //if (ImGui::Button("Click Me")) {
            //std::cout << "Button Clicked!" << std::endl;
        //}
        ImGui::Text(currentString.c_str());
        //ImGui::SliderFloat("Slider", &slider_value, 0.0f, 1.0f);
        //ImGui::Checkbox("Checkbox", &checkbox_value);
        ImGui::End();

        if (show_demo) {
            ImGui::ShowDemoWindow(&show_demo);
        }

        // Render ImGui
        ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
