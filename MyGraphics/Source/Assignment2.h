#ifndef Assignment2_H
#define Assignment2_H
#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Car.h"


#include <iomanip>

class Assignment2 : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		U_LIGHT0_POSITION,
		U_LIGHT1_POSITION,
		U_LIGHT2_POSITION,
		U_LIGHT3_POSITION,
		U_LIGHT4_POSITION,
		U_LIGHT5_POSITION,
		U_LIGHT6_POSITION,
		U_LIGHT7_POSITION,

		U_LIGHT0_COLOR,
		U_LIGHT1_COLOR,
		U_LIGHT2_COLOR,
		U_LIGHT3_COLOR,
		U_LIGHT4_COLOR,
		U_LIGHT5_COLOR,
		U_LIGHT6_COLOR,
		U_LIGHT7_COLOR,

		U_LIGHT0_POWER,
		U_LIGHT1_POWER,
		U_LIGHT2_POWER,
		U_LIGHT3_POWER,
		U_LIGHT4_POWER,
		U_LIGHT5_POWER,
		U_LIGHT6_POWER,
		U_LIGHT7_POWER,

		U_LIGHT0_KC,
		U_LIGHT1_KC,
		U_LIGHT2_KC,
		U_LIGHT3_KC,
		U_LIGHT4_KC,
		U_LIGHT5_KC,
		U_LIGHT6_KC,
		U_LIGHT7_KC,

		U_LIGHT0_KL,
		U_LIGHT1_KL,
		U_LIGHT2_KL,
		U_LIGHT3_KL,
		U_LIGHT4_KL,
		U_LIGHT5_KL,
		U_LIGHT6_KL,
		U_LIGHT7_KL,

		U_LIGHT0_KQ,
		U_LIGHT1_KQ,
		U_LIGHT2_KQ,
		U_LIGHT3_KQ,
		U_LIGHT4_KQ,
		U_LIGHT5_KQ,
		U_LIGHT6_KQ,
		U_LIGHT7_KQ,

		U_LIGHT0_TYPE,
		U_LIGHT1_TYPE,
		U_LIGHT2_TYPE,
		U_LIGHT3_TYPE,
		U_LIGHT4_TYPE,
		U_LIGHT5_TYPE,
		U_LIGHT6_TYPE,
		U_LIGHT7_TYPE,

		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT6_SPOTDIRECTION,
		U_LIGHT7_SPOTDIRECTION,

		U_LIGHT0_COSCUTOFF,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT6_COSCUTOFF,
		U_LIGHT7_COSCUTOFF,

		U_LIGHT0_COSINNER,
		U_LIGHT1_COSINNER,
		U_LIGHT2_COSINNER,
		U_LIGHT3_COSINNER,
		U_LIGHT4_COSINNER,
		U_LIGHT5_COSINNER,
		U_LIGHT6_COSINNER,
		U_LIGHT7_COSINNER,

		U_LIGHT0_EXPONENT,
		U_LIGHT1_EXPONENT,
		U_LIGHT2_EXPONENT,
		U_LIGHT3_EXPONENT,
		U_LIGHT4_EXPONENT,
		U_LIGHT5_EXPONENT,
		U_LIGHT6_EXPONENT,
		U_LIGHT7_EXPONENT,


		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE1,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_LIGHTBALL,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_IMAGE,
		GEO_DOORMAN,
		GEO_TEXT,
		GEO_LIGHTBOXTEXT,
		GEO_CARTEXT,
		GEO_FOUNTAINTEXT,
		GEO_TRASHCANTEXT,
		GEO_CAR,
		GEO_CAR_STEERING,
		GEO_CAR_WHEELS,
		GEO_CAR2,
		GEO_CAR2_STEERING,
		GEO_CAR2_WHEELS,
		GEO_CAR3,
		GEO_CAR3_STEERING,
		GEO_CAR3_WHEELS,
		GEO_CAR_SPOTLIGHT,
		GEO_CAR_SPOTLIGHT2,
		GEO_HOUSE,
		GEO_FENCE,
		GEO_LAMPPOST,
		GEO_TREE,
		GEO_ELECTRICBOX,
		GEO_FOUNTAIN,
		GEO_TRASHCAN,
		GEO_SPEAR,

		NUM_GEOMETRY,
	};

public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	//values
	double sensitivity; //current sensitivity
	double FPS; //fps

	//double distance
	double distfromcar;
	double distfromelectricbox;
	double distfromfountain;
	double distfrombench;
	double distfromtrashcan;

	//double timers
	double lighttimer;
	double cooldowntimer;
	double sensitivitydisappeartimer;

	//int
	int lightcount; 

	//bools 
	bool isPlayerinCar; //check player in car
	bool carfollower; // camera follower
	bool isKeyPressed; //check if is keypressed

	//car translate bools
	bool translateMax;
	float translateAmt;

	//collision bools
	bool carcollider;
	bool electricboxcollider;
	bool housecollider;
	bool benchcollider;
	bool garbagecancollider;
	bool fountaincollider;
	bool multipleinstance;
	bool boundarycollider;

	//end of collision bools

	//Interaction bools V1
	bool carinteraction;
	bool electricboxinteraction;
	bool fountaininteraction;
	bool trashcaninteraction;

	//Interaction bools V2
	bool carcooldown;
	bool lightturnon; //the light turns on after generator pressed
	bool lightturnedon;
	bool fountainpressed;
	bool garbagecanpressed;
	bool sensitivitychanged;
	//End of interaction bools

	bool keypressed;
	//Vector 3
	Vector3 lightsdirection;

	//string
	std::string frames;
	std::string sensitivitycount;


	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	Mesh* meshList[NUM_GEOMETRY];
	Light light[8];

	//Init of car
	Car car; //main car

	//Side cars
	Car car2;
	Car car3;

	//functions
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void BoundsCheck();
	void CollisionChecks();
};

#endif

