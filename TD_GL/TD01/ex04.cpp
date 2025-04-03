#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include <iostream>

using namespace glbasimac;
float red = 0.f;
float green = 0.f;
float blue = 0.f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* OpenGL Engine */
GLBI_Engine myEngine;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}
static const float GL_VIEW_SIZE = 1.;
void onWindowResized(GLFWwindow* /*window*/, int width, int height){

 	aspectRatio = width / (float) height;
 	glViewport(0, 0, width, height);
 	if( aspectRatio > 1.0){
		myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
 		GL_VIEW_SIZE * aspectRatio / 2. ,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
 }
 	else{
		myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
 		-GL_VIEW_SIZE / (2. * aspectRatio), 
		GL_VIEW_SIZE / (2. * aspectRatio));
 }
}


void keyCallback (GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_A && action  == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_callback(GLFWwindow* window, int buttton, int action, int mods){
	
	if(buttton == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		// std::cout << "Position Souris : " << x << " " << y << std::endl;

		red = static_cast<float>(static_cast<int> (x) % 256 )/ 255.0f;
		green = static_cast<float>(static_cast<int> (y) % 256 )/ 255.0f;
		blue = 0.f;

	}
}

void cursor_position_callback(GLFWwindow* window, double x, double y){
	// std::cout << "Position Souris : " << x << " " << y << std::endl;
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	red = static_cast<float>(static_cast<int> (x) / width )/ 255.0f;
	green = 0;
	blue = static_cast<float>(static_cast<int> (y) / height )/ 255.0f;
}

int main() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 800, "TD 01 Ex 04", nullptr, nullptr);
   

    if (!window) {
        glfwTerminate();
        return -1;
    }
	glfwSetWindowSizeCallback (window,onWindowResized);
	

    // Make the window's context current
    glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	// Initialize Rendering Engine
	myEngine.initGL();

	glfwSetMouseButtonCallback(window, mouse_callback);
	
	glfwSetKeyCallback (window, keyCallback);
	
	onWindowResized(window,800, 800);
	
	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClearColor(red, green, blue, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

        // render here

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

    glfwTerminate();
    return 0;
}

