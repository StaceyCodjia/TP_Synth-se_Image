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
	// std::vector<float> carreCoordonnes = {
	// 	-0.5f, -0.5f,
	// 	0.5f, -0.5f,
	// 	0.5f, 0.5f,
	// 	-0.5f, 0.5f
	// };
	// carre.initShape(carreCoordonnes);
	std::vector<float> triangleCoordonnes = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f,
	};
	triangle.initShape(triangleCoordonnes);
}
 
 void renderScene(){
	myEngine.setFlatColor(1.0f, 1.0f, 0.0f);
	// carre.drawShape();
	triangle.drawShape();
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