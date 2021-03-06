#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
#include "IK.h"


const int DISPLAY_WIDTH = 1200;
const int DISPLAY_HEIGHT = 800;
const float FAR = 100.0f;
const float NEAR = 1.0f;
const float CAM_ANGLE = 60.0f;
float relation = (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT;

Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

IK scn(glm::vec3(0.0f, 5.0f, -50.0f), CAM_ANGLE, relation, NEAR, FAR);

float factor = 1.0;

double x1 = 0, x2=0;
double ys1 = 0, y2 = 0;
float depth;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		/*glm::vec3 a = scn.get_tip(first_link);
		glm::vec3 b = scn.get_base(first_link);
		std::cout << "a=(" << a.x << "," << a.y << "," << a.z << ")" <<
			" , " << "b=(" << b.x << "," << b.y << "," << b.z << ")" << std::endl;*/
		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
				case GLFW_KEY_ESCAPE:			
					glfwSetWindowShouldClose(window,GLFW_TRUE);
				break;
				case GLFW_KEY_D:
					scn.movementActive = false;
					scn.destination = glm::vec3(-50, 0, -50);
					//scn.pick_head();
					//scn.shapeTransformation(scn.yGlobalRotate,-30.f);
					break;
				case GLFW_KEY_A:
					scn.movementActive = false;
					scn.destination = glm::vec3(50, 0, -50);
					//scn.pick_head();
					//scn.shapeTransformation(scn.yGlobalRotate,30.f);
					break;
				case GLFW_KEY_W:
					scn.movementActive = false;
					scn.destination = glm::vec3(0, 50, 0);
					//scn.shapeTransformation(scn.xGlobalRotate,30.f);
					break;
				case GLFW_KEY_S:
					scn.movementActive = false;
					scn.destination = glm::vec3(0, -50, 0);
					//scn.shapeTransformation(scn.xGlobalRotate,-30.f);
					break;
				case GLFW_KEY_UP:
					scn.pickedShape = -1;
					scn.camIndx = 0;
					scn.shapeTransformation(scn.zLocalTranslate, -1.f);
					break;
				case GLFW_KEY_DOWN:
					scn.pickedShape = -1;
					scn.camIndx = 0;
					scn.shapeTransformation(scn.zLocalTranslate, 1.f);
					break;
				case GLFW_KEY_LEFT:
					scn.pickedShape = -1;
					scn.camIndx = 0;
					scn.shapeTransformation(scn.xLocalTranslate, 1.f);
					break;
				case GLFW_KEY_RIGHT:
					scn.pickedShape = -1;
					scn.camIndx = 0;
					scn.shapeTransformation(scn.xLocalTranslate, -1.f);
					break;
				case GLFW_KEY_C:
					if (scn.camIndx == 0) scn.camIndx = 1;
					else scn.camIndx = 0;
					break;
				case GLFW_KEY_P:
					scn.paused = !scn.paused;
					break;
			default:
				break;
			}
		}
		else {
			scn.destination = glm::vec3(0, 0, 100);
			scn.movementActive = true;
		}
	}
	
	void updatePosition(double xpos, double ypos)
	{
		x1  = x2;
		x2 = xpos;
		ys1 = y2; 
		y2 = ypos;
	}

	

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		
		scn.resize(width,height,NEAR,FAR);
		relation = (float)width/(float)height;
	}