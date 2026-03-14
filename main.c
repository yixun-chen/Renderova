#include <stdlib.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define OVA_WINDOW_WIDTH  800
#define OVA_WINDOW_HEIGHT 600

void initWindow(GLFWwindow** window){
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	*window = glfwCreateWindow(OVA_WINDOW_WIDTH, OVA_WINDOW_HEIGHT, "Vulkan", NULL, NULL);
}

void initVulkan(){}

void mainLoop(GLFWwindow* window){
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}
}

void cleanup(GLFWwindow* window){
	glfwDestroyWindow(window);

	glfwTerminate();
}

void run(){
	GLFWwindow* window;		// window ptr stores the window's handle created by glfw
	initWindow(&window);
	initVulkan();
	mainLoop(window);
	cleanup(window);
}

int main(){
	run();
	
	return EXIT_SUCCESS;
}
