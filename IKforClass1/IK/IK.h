#pragma once
#include "scene.h"
const int linksNum = 8;
const int maximumIterations = 1;

const int blue_cubes = 5;
const int red_cubes = 5;

const int first_link = 0;
const int last_link = first_link + linksNum - 1;
const int target_cube = linksNum;

const float step_size = 0.5f;
const float epsilon = 0.0001f;

const int blue_cubes_0 = linksNum;
const int red_cubes_0 = linksNum + blue_cubes;
const int walls_0 = linksNum + blue_cubes + red_cubes;


class IK : public Scene
{
	bool cameraMode;
	glm::vec3 tipPosition;
	glm::vec3 targetPosition;
	bool isIKactive;
	double delta;
    float maxDistance;

public:
	glm::vec3 destination;
	bool movementActive = true;
	int score = 0;
	bool gameOver = false;

	IK(void);
	virtual ~IK(void);
	IK(glm::vec3 position,float angle,float hwRelation,float near, float far);
	
	void init(Vertex *vertices,unsigned int *indices,int verticesSize,int indicesSize);

	void addShape(int type, int parent);
	void addShape(const std::string& fileName, int parent);
	void addShape(const std::string& fileName,const std::string& textureFileName, int parent);
	void addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, int parent);
	void addShape(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices,const std::string& textureFileName, int parent);
	void addShape(int CylParts,int linkPosition,int parent);
	void addShape(int CylParts,int linkPosition,const std::string& textureFileName,int parent);

	void apply_transformation(std::vector<glm::vec3>& p);
	void calculate_step();
	void make_change();
	float distance(int indx1, int indx2);
	void pick_next(int offset);
	void pick_box();
	void pick_head();
	void pick_tail();
	void check_collisions();
	static bool is_blue_shape(int indx);
	static bool is_red_shape(int indx);
	static bool is_wall(int indx);
	bool is_active() const { return isIKactive;}
	void change_mode() { pickedShape = pickedShape == -1 ? 0 : -1; }
	void set_activation(const bool is_active) { isIKactive = is_active; }
	void move_enemies();
};

