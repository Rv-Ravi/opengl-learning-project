#include <iostream>

#include "GLFW/glfw3.h"
#include "glad/glad.h"



int main(int args,char** kargs)
{

	//intializing the glfw so that user can use all glfw functionalities.
	//if glfw is not initialized then message will be printed and exit the code.
	if (!glfwInit())
	{
		std::cerr << "There is some issue with initializing the GLFW.\n";
		return 1;
	}

	//informing glfw window about the opengl version 4.5 to be used
	//informing the we are using core profile for the opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creating the window and checking whether the window is crteated successfully or not
	//if window is not created successfully then we print the message and terminate the glfw and code.
	//creating the window with width height and application name
	GLFWwindow* window = glfwCreateWindow(800, 400, "Application",nullptr, nullptr);
	if (!window)
	{
		std::cerr << "There is some issue in creating the window.\n";
		glfwTerminate();
		return 1;
	}

	//informing the glfw and opengl about the window by making the window as current context
	//so that whatever images are drwan it will be in the created window
	//this should be setted up before initializing the glad so the glad will recongnize the current context
	glfwMakeContextCurrent(window);
	//Setting up the swap interval(between front and back buffers) of the current window
	//1 represents v-sync on
	glfwSwapInterval(1);

	//initializing or loading the glad API to use opengl functionalities
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "There is some issue in loading the GLAD API for Opengl.\n";
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		glfwTerminate();
		return -1;
	}


	//if the view port is fixed then the draw ratio will be different when it is resized
	//in such cases we are informing the glfw that whenever the resize happens it will call the lambda function
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int x, int y) {
			// Have to inform opengl that we have to draw in the mentioned cordinates
			//so that the NDC -1 to 1 will be converted to the screen coordinates
			glViewport(0, 0, x, y);
		});

	
	//Loop which run until the window is manually closed or quit or any error occurs
	//will check whether the window is closed are not
	while (!glfwWindowShouldClose(window))
	{
		//clear the color buffer for the current drawing frame with the mentioned color
		glClearColor(0.5f, 0.3f, 0.9f, 1.0f);
		//clear all the mentioned buffers with the provided values
		glClear(GL_COLOR_BUFFER_BIT);


		//will swap the buffers front and back buffer after all the drawing is been done 
		glfwSwapBuffers(window);

		//check for any keyboard or mouse events for the current context window
		glfwPollEvents();
	}

	return 0;
}