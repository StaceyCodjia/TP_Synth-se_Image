#include "draw_scene.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Set_Of_Points frame{3};



void initScene() {
	std::vector<float> points {0.0,0.0,0.0};
	somePoints.initSet(points,1.0,1.0,1.0);

	std::vector<float> baseCarre{-10.0,-10.0,0.0,
								 10.0,-10.0,0.0,
								 10.0,10.0,0.0,
								 -10.0,10.0,0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);
	std::vector<float> framePoints {
		0.0, 0.0, 0.0,
		10.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 10.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 10.0,
	};

	std::vector<float> frameColors {
		1.0, 0.0, 0.0,
		10.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 10.0, 0.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 10.0,
	};
	frame.initSet(framePoints,frameColors);
	frame.changeNature(GL_LINES);
}


void drawFrame() {
	frame.drawSet();
}

void drawBase() {
	// TO DO
}

void drawArm() {
	// TO DO
}

void drawPan() {
	// TO DO
}

void drawScene() {
	glPointSize(10.0);

	drawFrame();

	myEngine.setFlatColor(0.2,0.0,0.0);
	ground.drawShape();
	
}



