#pragma once
#include "scene.h"

const std::string resources_path = R"(C:\Users\tbarami\Documents\GitHub\3D-Snake\IKforClass1\IK\res\)";

const std::string theme_sound = resources_path + "sounds\\theme.wav";
const std::string win_sound = resources_path + "sounds\\win.wav";
const std::string lose_sound = resources_path + "sounds\\lose.wav";
const std::string prize_sound = resources_path + "sounds\\prize.wav";


const int linksNum = 8;
const int maximumIterations = 1;

const int blue_cubes = 6;
const int red_cubes = 6;

const int first_link = 0;
const int last_link = first_link + linksNum - 1;
const int target_cube = linksNum;

const float step_size = 0.5f;
const float epsilon = 0.0001f;

const int blue_cubes_0 = linksNum;
const int red_cubes_0 = blue_cubes_0 + blue_cubes;
const int yellow_cube_0 = red_cubes_0 + red_cubes;
const int walls_0 = yellow_cube_0 + 1;

const int up_wall = walls_0;
const int down_wall = walls_0 + 1;
const int left_wall = walls_0 + 2;
const int right_wall = walls_0 + 3;
const int floor_wall = walls_0 + 4;


const int above_camera = 0;
const int snake_camera = 1;

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
	int gameOver = 0;
	bool paused = false;

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
	void update_cameras();
	void calculate_step();
	void make_change();
	void update_movement();
	float distance(int indx1, int indx2);
	void pick_next(int offset);
	void pick_box();
	void pick_head();
	void pick_tail();
	bool collides(int s1, int s2);
	void check_collisions();
	static bool is_blue_shape(int indx);
	static bool is_red_shape(int indx);
	static bool is_yellow_shape(int indx);
	static bool is_wall(int indx);
	bool is_active() const { return isIKactive;}
	void change_mode() { pickedShape = pickedShape == -1 ? 0 : -1; }
	void set_activation(const bool is_active) { isIKactive = is_active; }
	void move_enemies();
};
