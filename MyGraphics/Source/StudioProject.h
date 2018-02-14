#ifndef StudioProject_H
#define StudioProject_H
#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Dinosaur.h"
#include <iomanip>

class StudioProject : public Scene
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


		U_LIGHT0_COLOR,
		U_LIGHT1_COLOR,
		U_LIGHT2_COLOR,
		U_LIGHT3_COLOR,
		U_LIGHT4_COLOR,
		U_LIGHT5_COLOR,

		U_LIGHT0_POWER,
		U_LIGHT1_POWER,
		U_LIGHT2_POWER,
		U_LIGHT3_POWER,
		U_LIGHT4_POWER,
		U_LIGHT5_POWER,

		U_LIGHT0_KC,
		U_LIGHT1_KC,
		U_LIGHT2_KC,
		U_LIGHT3_KC,
		U_LIGHT4_KC,
		U_LIGHT5_KC,

		U_LIGHT0_KL,
		U_LIGHT1_KL,
		U_LIGHT2_KL,
		U_LIGHT3_KL,
		U_LIGHT4_KL,
		U_LIGHT5_KL,

		U_LIGHT0_KQ,
		U_LIGHT1_KQ,
		U_LIGHT2_KQ,
		U_LIGHT3_KQ,
		U_LIGHT4_KQ,
		U_LIGHT5_KQ,

		U_LIGHT0_TYPE,
		U_LIGHT1_TYPE,
		U_LIGHT2_TYPE,
		U_LIGHT3_TYPE,
		U_LIGHT4_TYPE,
		U_LIGHT5_TYPE,

		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT5_SPOTDIRECTION,

		U_LIGHT0_COSCUTOFF,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT5_COSCUTOFF,

		U_LIGHT0_COSINNER,
		U_LIGHT1_COSINNER,
		U_LIGHT2_COSINNER,
		U_LIGHT3_COSINNER,
		U_LIGHT4_COSINNER,
		U_LIGHT5_COSINNER,

		U_LIGHT0_EXPONENT,
		U_LIGHT1_EXPONENT,
		U_LIGHT2_EXPONENT,
		U_LIGHT3_EXPONENT,
		U_LIGHT4_EXPONENT,
		U_LIGHT5_EXPONENT,


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
		GEO_TREE,
		GEO_SPEAR,
		GEO_DINO1,
		GEO_CHECKPOINT,
		GEO_HELDITEM,	   // Added 14/2/2018 (Lindsay)
		GEO_BITESYMBOL,	   // Added 14/2/2018 (Lindsay)
		GEO_TAILSYMBOL,	   // Added 14/2/2018 (Lindsay)
		GEO_STEAK,		   // Added 14/2/2018 (Lindsay)
		GEO_SPEARSYMBOL,   // Added 14/2/2018 (Lindsay)
		GEO_ITEMBOX,	   // Added 14/2/2018 (Lindsay)
		NUM_GEOMETRY,
	};

public:
	StudioProject();
	~StudioProject();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];


	//temporary
	int test;
	bool fire = false;	

	//values
	double FPS; //fps

	double speed; //speed of dinosaur

	//bools 
	bool isPlayerinGame; //check player in game
	bool isKeyPressed; //check if is keypressed


	//string
	std::string frames;


	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	Mesh* meshList[NUM_GEOMETRY];
	Light light[6];

	//Init of car
	Dinosaur maindinosaur; //main car

	//functions
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	//void BoundsCheck();
	//void CollisionChecks();
};

#endif

