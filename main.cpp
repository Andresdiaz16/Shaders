#include <cstdint>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

GLFWwindow* window;

const uint32_t WIDTH = 800;
const uint32_t HEIGTH = 600;

class HelloTriangleApplication {
public:
    void run() {
        initVulkan();
        initWindow();
        mainLoop();
        cleanup();
    }

private:

    //Method to initialize GLFW window
    void initWindow(){
        //initializes the GLFW lib
        glfwInit();

        //telling glfw to not create the OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        //telling glfw to not be able to resizw
        glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);

        //window reference
        window = glfwCreateWindow(WIDTH,HEIGTH, "Vulkan Test" , nullptr, nullptr);

    }

    //Methd to initialize every vulkan object
    void initVulkan() {

    }


    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    //method to clean and delete all used vulkan objects
    void cleanup() {

        //detroy window
        glfwDestroyWindow(window);

        //terminate glfw
        glfwTerminate();

    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

