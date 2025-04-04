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
int objectNumber = 0;

/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

GLBI_Convex_2D_Shape carre;
GLBI_Convex_2D_Shape triangle;
GLBI_Convex_2D_Shape cercle;

static const float GL_VIEW_SIZE = 4.;

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
	std::vector<float> carreCoordonnes = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};
	carre.initShape(carreCoordonnes);
	std::vector<float> triangleCoordonnes = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f,
	};
	triangle.initShape(triangleCoordonnes);

	std::vector<float> cercleCoordinates;
    int numSegments = 50; 
    float angleStep = 2.0f * M_PI / numSegments;
    for (int i = 0; i < numSegments; ++i) {
        float angle = i * angleStep;
        float x = cos(angle);
        float y = sin(angle);
        cercleCoordinates.push_back(x);
        cercleCoordinates.push_back(y);
    }
	cercle.initShape(cercleCoordinates);
}
 
 void renderScene(){
	switch(objectNumber) {
		case 0:
			myEngine.setFlatColor(1.0f, 0.0f, 0.0f);
			carre.changeNature(GL_TRIANGLE_FAN);
			carre.drawShape();
			break;
		case 1:
			myEngine.setFlatColor(1.0f, 1.0f, 0.0f);
			triangle.changeNature(GL_TRIANGLE_FAN);
			triangle.drawShape();
			break;
		case 2:
			myEngine.setFlatColor(0.0f, 1.0f, 0.0f);
			cercle.changeNature(GL_TRIANGLE_FAN);
			cercle.drawShape();
			break;
		default:
			break;
		}
 }
 
 void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
 {
	 const char* keyName = glfwGetKeyName(key, scancode);
 
	 if (action == GLFW_PRESS && keyName[0] == 'a') {
		 objectNumber = (objectNumber+1)%3;
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
    GLFWwindow* window = glfwCreateWindow(800, 800, "TD 02 Ex 4", nullptr, nullptr);
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
	glfwSetKeyCallback(window, key_callback);
	initScene();
	

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