#ifndef EJS_NULL
    #define EJS_NULL ((void*)0)
#endif
/*-------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define WIDTH  800
#define HEIGHT 600

bool createInstance(VkInstance* instanceHandle){
    VkApplicationInfo appInfo = {
        .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pNext              = EJS_NULL,
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
		.pNext						= EJS_NULL,
		.flags						= 0x0,
        .pApplicationInfo           = &appInfo,
        .enabledLayerCount          = 0,
		.ppEnabledLayerNames		= EJS_NULL,
	    .enabledExtensionCount      = glfwExtensionCount,
        .ppEnabledExtensionNames    = glfwExtensions,
    };

    if(vkCreateInstance(&createInfo, EJS_NULL, instanceHandle) != VK_SUCCESS){
        fprintf(stderr, "Failed to create instance!");
        return false;
    }

	return true;
}

void initWindow(GLFWwindow** window){
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	*window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", EJS_NULL, EJS_NULL);
}

bool initVulkan(VkInstance* instanceHandle){
    if(createInstance(instanceHandle) == false){
		return false;
	}
	return true;
}

void mainLoop(GLFWwindow* window){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
        fprintf(stdout, "Running...\n");
        fprintf(stdout, "Ctrl-C to terminate\n");
	}
}

void cleanup(GLFWwindow* windowHandle, VkInstance instanceHandle){
    vkDestroyInstance(instanceHandle, EJS_NULL);

	glfwDestroyWindow(windowHandle);

	glfwTerminate();
}

bool run(void){
	GLFWwindow* window;		// window ptr stores the window's handle created by glfw
	initWindow(&window);

    VkInstance instance;    // Handle to the Vulkan instance object
	if(initVulkan(&instance) == false){
		return false;
	}

	mainLoop(window);

	cleanup(window, instance);

	return true;
}

int main(void){
	if(run() == false){
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
