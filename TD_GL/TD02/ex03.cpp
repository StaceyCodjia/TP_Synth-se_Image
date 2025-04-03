#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include <iostream>
#include "glbasimac/glbi_convex_2d_shape.hpp"

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* OpenGL Engine */
GLBI_Engine myEngine;
GLBI_Set_Of_Points thePoints;

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

 void initScene(){
	std::vector<float> coordonnes = {
        0.0f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,
		-0.5f, -0.5f
    };

	std::vector<float> colors = {
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f
	};
	thePoints.initSet(coordonnes, colors);
 }
 
 void renderScene(){
	glPointSize(4.0);
    thePoints.drawSet();
 }

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        //Conversion des coordonées espace écran en coordonées espace virtuel
        float x = static_cast<float>(xpos / width) * 2.0f - 1.0f;
        float y = static_cast<float>(1.0f - ypos / height) * 2.0f - 1.0f;


        std::vector<float> newCoordonnes = {x, y};
        std::vector<float> newColors = {1.0f, 1.0f, 1.0f};
        thePoints.addAPoint(newCoordonnes.data(), newColors.data());
    }
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ( action == GLFW_PRESS) {
		if(key == GLFW_KEY_A){
			thePoints.changeNature(GL_LINE_STRIP);
		}
		if(key == GLFW_KEY_B){
			thePoints.changeNature(GL_POINTS);
		}
		
	}
}

int main() {
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 800, "TD 02 Ex 3", nullptr, nullptr);
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
	onWindowResized(window,800, 800);

	initScene();
	
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetKeyCallback(window, keyCallback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClearColor(0.2f,0.f,0.f,0.f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderScene();

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