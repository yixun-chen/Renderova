#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define WIDTH  800
#define HEIGHT 600

void createInstance(VkInstance* instanceHandle){
    VkApplicationInfo appInfo = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName   = "Hello Triangle",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName        = "No Engine",
        .engineVersion      = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion         = VK_API_VERSION_1_0,
    };

    uint32_t glfwExtensionCount;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkInstanceCreateInfo createInfo = {
        .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo           = &appInfo,
        .ppEnabledExtensionNames    = glfwExtensions,
        .enabledExtensionCount      = glfwExtensionCount,
        .enabledLayerCount          = 0,
    };

    if(vkCreateInstance(&createInfo, NULL, instanceHandle) != VK_SUCCESS){
        fprintf(stderr, "Failed to create instance!");
        exit(1);
    }
}

void initWindow(GLFWwindow** window){
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	*window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", NULL, NULL);
}

void initVulkan(VkInstance* instanceHandle){
    createInstance(instanceHandle);
}

void mainLoop(GLFWwindow* window){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}
}

void cleanup(GLFWwindow* windowHandle, VkInstance instanceHandle){
    vkDestroyInstance(instanceHandle, NULL);

	glfwDestroyWindow(windowHandle);

	glfwTerminate();
}

void run(){
	GLFWwindow* window;		// window ptr stores the window's handle created by glfw
	initWindow(&window);

    VkInstance instance;    // Handle to the Vulkan instance object
	initVulkan(&instance);

	mainLoop(window);

	cleanup(window, instance);
}

int main(){
	run();
	
	return EXIT_SUCCESS;
}
