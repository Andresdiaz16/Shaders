#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

GLFWwindow* window;

const uint32_t WIDTH = 800;
const uint32_t HEIGTH = 600;

//validation layers vector
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHORONOS_validation"
};

//defines if the app is being built in debug or release
#ifdef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

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

        //checks if the validation layers were requestesd but are not available
        if(enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

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
        
        //check if the validation layers are present and assign them to the create instance
        if(enableValidationLayers){
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else{
        createInfo.enabledLayerCount = 0;
        }

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS){
            throw std::runtime_error("failed to create instance!");
        }

    }


    //function that validates if the validation layers exists
    bool checkValidationLayerSupport(){
        uint32_t layercount;

        vkEnumerateInstanceLayerProperties(&layercount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layercount);
        vkEnumerateInstanceLayerProperties(&layercount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers ) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            
            }
            
            if (!layerFound) {
                return false;
            
            }
        
        }

        return true;

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

