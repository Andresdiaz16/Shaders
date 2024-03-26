#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>
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

    VkInstance instance;

    //method to create an instance of vulkan
    void createInstance() {

        VkApplicationInfo appInfo{};
        VkInstanceCreateInfo createInfo{};
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        uint32_t extensionCount = 0;


        /*
         * appInfo struct is optional but it gives basic information
         * about the application.
         * 
         */
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Triangle Test";
        appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,extensions.data());

        std::cout << "available extension:\n";

        for(const auto& extension : extensions){
            std::cout << '\t' << extension.extensionName << '\n';
        }

        /*
         * This fucntion call is used to retrived the extensions needed by 
         * glfw
         *
         */
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::cout << glfwExtensions;


        /*
         *
         * this struct is used to stored the necessary extesinos to create 
         * the vulkan instance
         *
         */
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledLayerNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
            throw std::runtime_error("failed to create instance!");
        }

    }

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

        createInstance();

    }


    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    //method to clean and delete all used vulkan objects
    void cleanup() {

        //destroy the vulkan instance
        vkDestroyInstance(instance,nullptr);

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

