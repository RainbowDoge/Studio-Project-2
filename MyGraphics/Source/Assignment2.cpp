#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "Collision.h"
#include "MyMath.h"

Assignment2::Assignment2()
{
}

Assignment2::~Assignment2()
{
}

void Assignment2::Init()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	camera.Init(Vector3(-19.1468, -26, -29.2893), Vector3(0, -26, -29.28), Vector3(0, 1, 0));


	//Car init
	isPlayerinCar = false; // boolean if player in car
	isKeyPressed = false; // to alter car speed if user has not pressed anything
	car.SetPosition(Vector3(-20.298, -28.75, -23.4837));
	car.SetRotation(0); //set rotation of 0 
	car.SetSpeed(0); //set speed of 0
	//End of car inits

	//Side car inits
	car2.SetPosition(Vector3(-60, -28.75, -41));
	car3.SetPosition(Vector3(70,-28.75, -46.5));
	//End of side car inits

	//Distance calculations init
	distfromcar = 0;
	distfromelectricbox = 0;
	distfromfountain = 0;
	distfromtrashcan = 0;
	//End of distance calculations

	//Light inits
	lighttimer = 0;
	lightcount = 0;
	//End of light inits

	//Interaction bools V1 ( for interactions with objects)
	carinteraction = false;
	electricboxinteraction = false;
	fountaininteraction = false;
	trashcaninteraction = false;
	//Interaction bools V2 (bools that result after the interaction of objects)
	carcooldown = false;
	lightturnon = false;
	lightturnedon = false;
	fountainpressed = false;

	//Multiple instance bool
	multipleinstance = false;

	//Sensitivity bool
	sensitivitychanged = false;
	sensitivitydisappeartimer = 1.5;

	//bool for keypressed
	keypressed = false;

	//Translate amt change in car
	translateAmt = -80;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	////m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	//m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
	//m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	//MATERIALS
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	#pragma region LIGHT INIT

		m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
		m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
		m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
		m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
		m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
		m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
		m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
		m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
		m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
		m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
		m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

		m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
		m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
		m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
		m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
		m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
		m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
		m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
		m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
		m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
		m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
		m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

		m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
		m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
		m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
		m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
		m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
		m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
		m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
		m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
		m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
		m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
		m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

		m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
		m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
		m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
		m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
		m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
		m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
		m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
		m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
		m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
		m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
		m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

		m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
		m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
		m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
		m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
		m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
		m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
		m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
		m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
		m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
		m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
		m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

		m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
		m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
		m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
		m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
		m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
		m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
		m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
		m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
		m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
		m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
		m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

		m_parameters[U_LIGHT5_POSITION] = glGetUniformLocation(m_programID, "lights[5].position_cameraspace");
		m_parameters[U_LIGHT5_COLOR] = glGetUniformLocation(m_programID, "lights[5].color");
		m_parameters[U_LIGHT5_POWER] = glGetUniformLocation(m_programID, "lights[5].power");
		m_parameters[U_LIGHT5_KC] = glGetUniformLocation(m_programID, "lights[5].kC");
		m_parameters[U_LIGHT5_KL] = glGetUniformLocation(m_programID, "lights[5].kL");
		m_parameters[U_LIGHT5_KQ] = glGetUniformLocation(m_programID, "lights[5].kQ");
		m_parameters[U_LIGHT5_TYPE] = glGetUniformLocation(m_programID, "lights[5].type");
		m_parameters[U_LIGHT5_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[5].spotDirection");
		m_parameters[U_LIGHT5_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[5].cosCutoff");
		m_parameters[U_LIGHT5_COSINNER] = glGetUniformLocation(m_programID, "lights[5].cosInner");
		m_parameters[U_LIGHT5_EXPONENT] = glGetUniformLocation(m_programID, "lights[5].exponent");

		m_parameters[U_LIGHT6_POSITION] = glGetUniformLocation(m_programID, "lights[6].position_cameraspace");
		m_parameters[U_LIGHT6_COLOR] = glGetUniformLocation(m_programID, "lights[6].color");
		m_parameters[U_LIGHT6_POWER] = glGetUniformLocation(m_programID, "lights[6].power");
		m_parameters[U_LIGHT6_KC] = glGetUniformLocation(m_programID, "lights[6].kC");
		m_parameters[U_LIGHT6_KL] = glGetUniformLocation(m_programID, "lights[6].kL");
		m_parameters[U_LIGHT6_KQ] = glGetUniformLocation(m_programID, "lights[6].kQ");
		m_parameters[U_LIGHT6_TYPE] = glGetUniformLocation(m_programID, "lights[6].type");
		m_parameters[U_LIGHT6_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[6].spotDirection");
		m_parameters[U_LIGHT6_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[6].cosCutoff");
		m_parameters[U_LIGHT6_COSINNER] = glGetUniformLocation(m_programID, "lights[6].cosInner");
		m_parameters[U_LIGHT6_EXPONENT] = glGetUniformLocation(m_programID, "lights[6].exponent");

		m_parameters[U_LIGHT7_POSITION] = glGetUniformLocation(m_programID, "lights[7].position_cameraspace");
		m_parameters[U_LIGHT7_COLOR] = glGetUniformLocation(m_programID, "lights[7].color");
		m_parameters[U_LIGHT7_POWER] = glGetUniformLocation(m_programID, "lights[7].power");
		m_parameters[U_LIGHT7_KC] = glGetUniformLocation(m_programID, "lights[7].kC");
		m_parameters[U_LIGHT7_KL] = glGetUniformLocation(m_programID, "lights[7].kL");
		m_parameters[U_LIGHT7_KQ] = glGetUniformLocation(m_programID, "lights[7].kQ");
		m_parameters[U_LIGHT7_TYPE] = glGetUniformLocation(m_programID, "lights[7].type");
		m_parameters[U_LIGHT7_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[7].spotDirection");
		m_parameters[U_LIGHT7_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[7].cosCutoff");
		m_parameters[U_LIGHT7_COSINNER] = glGetUniformLocation(m_programID, "lights[7].cosInner");
		m_parameters[U_LIGHT7_EXPONENT] = glGetUniformLocation(m_programID, "lights[7].exponent");


		//INIT NUM LIGHTS 
		m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
		//LIGHT 1

		m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	#pragma endregion

	//TEXT
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP"); //update the MVP uniform

	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_NUMLIGHTS], 8); //set the amount of maximum lights to be 8 since we have 8 lights

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	//INIT LIGHTS
	
	#pragma region LIGHTS INTO SHADER

		//LAMPPOST LIGHTS SETTINGS
				light[0].type = Light::LIGHT_POINT;
				light[0].position.Set(19, -19, 12);
				light[0].color.Set(1, 1, 1);
				light[0].power = 0;
				light[0].kC = 1.f;
				light[0].kL = 0.01f;
				light[0].kQ = 0.001f;
				light[0].cosCutoff = cos(Math::DegreeToRadian(45));
				light[0].cosInner = cos(Math::DegreeToRadian(30));
				light[0].exponent = 3.f;
				light[0].spotDirection.Set(0.f, 1.f, 0.f);

				light[1].type = Light::LIGHT_POINT;
				light[1].position.Set(19, -19, -12);
				light[1].color.Set(1, 1, 1);
				light[1].power = 0;
				light[1].kC = 1.f;
				light[1].kL = 0.01f;
				light[1].kQ = 0.001f;
				light[1].cosCutoff = cos(Math::DegreeToRadian(45));
				light[1].cosInner = cos(Math::DegreeToRadian(30));
				light[1].exponent = 3.f;
				light[1].spotDirection.Set(0.f, 1.f, 0.f);

				light[2].type = Light::LIGHT_POINT;
				light[2].position.Set(19, -19, -36);
				light[2].color.Set(1, 1, 1);
				light[2].power = 0;
				light[2].kC = 1.f;
				light[2].kL = 0.01f;
				light[2].kQ = 0.001f;
				light[2].cosCutoff = cos(Math::DegreeToRadian(45));
				light[2].cosInner = cos(Math::DegreeToRadian(30));
				light[2].exponent = 3.f;
				light[2].spotDirection.Set(0.f, 1.f, 0.f);

				light[3].type = Light::LIGHT_POINT;
				light[3].position.Set(-19, -19, 12);
				light[3].color.Set(1, 1, 1);
				light[3].power = 0;
				light[3].kC = 1.f;
				light[3].kL = 0.01f;
				light[3].kQ = 0.001f;
				light[3].cosCutoff = cos(Math::DegreeToRadian(45));
				light[3].cosInner = cos(Math::DegreeToRadian(30));
				light[3].exponent = 3.f;
				light[3].spotDirection.Set(0.f, 1.f, 0.f);

				light[4].type = Light::LIGHT_POINT;
				light[4].position.Set(-19, -19, -12);
				light[4].color.Set(1, 1, 1);
				light[4].power = 0;
				light[4].kC = 1.f;
				light[4].kL = 0.01f;
				light[4].kQ = 0.001f;
				light[4].cosCutoff = cos(Math::DegreeToRadian(45));
				light[4].cosInner = cos(Math::DegreeToRadian(30));
				light[4].exponent = 3.f;
				light[4].spotDirection.Set(0.f, 1.f, 0.f);

				light[5].type = Light::LIGHT_POINT;
				light[5].position.Set(-19, -19, -36);
				light[5].color.Set(1, 1, 1);
				light[5].power = 0;
				light[5].kC = 1.f;
				light[5].kL = 0.01f;
				light[5].kQ = 0.001f;
				light[5].cosCutoff = cos(Math::DegreeToRadian(45));
				light[5].cosInner = cos(Math::DegreeToRadian(30));
				light[5].exponent = 3.f;
				light[5].spotDirection.Set(0.f, 1.f, 0.f);

				light[6].type = Light::LIGHT_SPOT;
				light[6].position.Set(car.GetPosition().x + 3, car.GetPosition().y, car.GetPosition().z - 2);
				light[6].color.Set(1, 1, 1);
				light[6].power = 0.75;
				light[6].kC = 1.f;
				light[6].kL = 0.01f;
				light[6].kQ = 0.001f;
				light[6].cosCutoff = cos(Math::DegreeToRadian(10));
				light[6].cosInner = cos(Math::DegreeToRadian(5));
				light[6].exponent = 3.f;
				light[6].spotDirection.Set(lightsdirection.x, lightsdirection.y, lightsdirection.z);

				light[7].type = Light::LIGHT_SPOT;
				light[7].position.Set(car.GetPosition().x + 3, car.GetPosition().y, car.GetPosition().z +2);
				light[7].color.Set(1, 1, 1);
				light[7].power = 0.75;
				light[7].kC = 1.f;
				light[7].kL = 0.01f;
				light[7].kQ = 0.001f;
				light[7].cosCutoff = cos(Math::DegreeToRadian(10));
				light[7].cosInner = cos(Math::DegreeToRadian(5));
				light[7].exponent = 3.f;
				light[7].spotDirection.Set(lightsdirection.x, lightsdirection.y, lightsdirection.z);

		// END OF LAMPPOST LIGHTS SETTINGS
				for (int i = 0; i < 8; i++)
				{
					//PASSING LIGHT STUFF INTO THE SHADER
					glUniform3fv(m_parameters[U_LIGHT0_COLOR + i], 1, &light[i].color.r);
					glUniform1f(m_parameters[U_LIGHT0_POWER + i], light[i].power);
					glUniform1f(m_parameters[U_LIGHT0_KC + i], light[i].kC);
					glUniform1f(m_parameters[U_LIGHT0_KL + i], light[i].kL);
					glUniform1f(m_parameters[U_LIGHT0_KQ + i], light[i].kQ);
					glUniform1i(m_parameters[U_LIGHT0_TYPE + i], light[i].type);
					glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF + i], light[i].cosCutoff);
					glUniform1f(m_parameters[U_LIGHT0_COSINNER + i], light[i].cosInner);
					glUniform1f(m_parameters[U_LIGHT0_EXPONENT + i], light[i].exponent);
				}
	#pragma endregion

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i] != NULL)
		{
			delete meshList[i];
		}
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_SPHERE1] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 1);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 18, 36, 1);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//ground.tga");

	#pragma region SKYBOX
		//INIT SKYBOX LEFT
		meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.0f, 1.0f);
		meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
		//INIT SKYBOX RIGHT
		meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.0f, 1.0f);
		meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
		//INIT SKYBOX TOP
		meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.0f, 1.0f);
		meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
		//INIT SKYBOX BOTTOM
		meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.0f, 1.0f);
		meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
		//INIT SKYBOX FRONT
		meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.0f, 1.0f);
		meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
		//INIT SKYBOX BACK
		meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.0f, 1.0f);
		meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	#pragma endregion

	//meshList[GEO_IMAGE] = MeshBuilder::GenerateQuad("copy", Color(1, 1, 1), 1.0f, 1.0f);
	//meshList[GEO_IMAGE]->textureID = LoadTGA("Image//copy.tga");

	meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("doorman", "OBJ//doorman.obj");
	meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");

	//CAR
	meshList[GEO_CAR] = MeshBuilder::GenerateOBJ("car", "OBJ//Car2.obj");
	meshList[GEO_CAR]->textureID = LoadTGA("Image//Car2.tga");

	meshList[GEO_CAR_STEERING] = MeshBuilder::GenerateOBJ("steering", "OBJ//steering.obj");
	meshList[GEO_CAR_STEERING]->textureID = LoadTGA("Image//Car2.tga");

	meshList[GEO_CAR_WHEELS] = MeshBuilder::GenerateOBJ("steering", "OBJ//Wheels.obj");
	meshList[GEO_CAR_WHEELS]->textureID = LoadTGA("Image//Wheels.tga");

	meshList[GEO_CAR2] = MeshBuilder::GenerateOBJ("car", "OBJ//Car2.obj");
	meshList[GEO_CAR2]->textureID = LoadTGA("Image//Car2.tga");

	meshList[GEO_CAR2_STEERING] = MeshBuilder::GenerateOBJ("steering", "OBJ//steering.obj");
	meshList[GEO_CAR2_STEERING]->textureID = LoadTGA("Image//Car2.tga");

	meshList[GEO_CAR2_WHEELS] = MeshBuilder::GenerateOBJ("steering", "OBJ//Wheels.obj");
	meshList[GEO_CAR2_WHEELS]->textureID = LoadTGA("Image//Wheels.tga");

	meshList[GEO_CAR3] = MeshBuilder::GenerateOBJ("car", "OBJ//Car2.obj");
	meshList[GEO_CAR3]->textureID = LoadTGA("Image//Car2.tga");

	meshList[GEO_CAR3_STEERING] = MeshBuilder::GenerateOBJ("steering", "OBJ//steering.obj");
	meshList[GEO_CAR3_STEERING]->textureID = LoadTGA("Image//Car2.tga");

	meshList[GEO_CAR3_WHEELS] = MeshBuilder::GenerateOBJ("steering", "OBJ//Wheels.obj");
	meshList[GEO_CAR3_WHEELS]->textureID = LoadTGA("Image//Wheels.tga");

	//END CAR

	meshList[GEO_HOUSE] = MeshBuilder::GenerateOBJ("house", "OBJ//house.obj");
	meshList[GEO_HOUSE]->textureID = LoadTGA("Image//House.tga");

	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("fence","OBJ//fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//bonus.tga");

	meshList[GEO_LAMPPOST] = MeshBuilder::GenerateOBJ("lamppost", "OBJ//lamppost.obj");
	meshList[GEO_LAMPPOST]->textureID = LoadTGA("Image//lamppost.tga");

	meshList[GEO_ELECTRICBOX] = MeshBuilder::GenerateOBJ("electricbox", "OBJ//electricbox.obj");
	meshList[GEO_ELECTRICBOX]->textureID = LoadTGA("Image//electricbox.tga");

	meshList[GEO_FOUNTAIN] = MeshBuilder::GenerateOBJ("fountainbottom", "OBJ//fountain.obj");
	meshList[GEO_FOUNTAIN]->textureID = LoadTGA("Image//fountainbottom.tga");

	meshList[GEO_TRASHCAN] = MeshBuilder::GenerateOBJ("trashcan", "OBJ//trashcan.obj");
	meshList[GEO_TRASHCAN]->textureID = LoadTGA("Image//trashcan.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("tree", "OBJ//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//tree.tga");

	//TEXTS
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_CARTEXT] = MeshBuilder::GenerateText("cartext", 16, 16);
	meshList[GEO_CARTEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_FOUNTAINTEXT] = MeshBuilder::GenerateText("fountaintext", 16, 16);
	meshList[GEO_FOUNTAINTEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_LIGHTBOXTEXT] = MeshBuilder::GenerateText("lightboxtext", 16, 16);
	meshList[GEO_LIGHTBOXTEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TRASHCANTEXT] = MeshBuilder::GenerateText("trashcantext", 16, 16);
	meshList[GEO_TRASHCANTEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_SPEAR] = MeshBuilder::GenerateOBJ("spear", "OBJ//Spear.obj");
	meshList[GEO_SPEAR]->textureID = LoadTGA("Image//SpearUV.tga");
	//END OF TEXTS

}
bool isPointinBox(Vector3 position, Box box)
{
	return (position.x >= box.minX && position.x <= box.maxX) &&
		(position.y >= box.minY && position.y <= box.maxY) &&
		(position.z >= box.minZ && position.z <= box.maxZ);
}

bool isPointinCircle(Circle a,  Circle b )
{
	float dx = a.xpos - b.xpos;
	float dy = a.zpos - b.zpos;

	float distance = sqrt(dx * dx + dy * dy);

	return (distance < a.radius + b.radius);
}

bool isPointinRect(Vector3 position, Rect rect)
{
	return (position.x >= rect.minX && position.x <=rect.maxX) &&
		(position.y >= rect.minY && position.y <=rect.maxY) &&
		(position.z >= rect.minZ && position.z <= rect.maxZ);
}

void Assignment2::CollisionChecks()
{
	static const float MOVEMENT_SPEED = 1.0f;

	Vector3 view = camera.target - camera.position;
	Vector3 right = view.Cross(camera.up);

	keypressed = false;

	//Simple collision check
	if (!keypressed)
	{
		if (Application::IsKeyPressed('W'))
		{

				camera.position = camera.position -  view * MOVEMENT_SPEED;
				camera.target = camera.position + view;
			if (!keypressed)
			{
				if (Application::IsKeyPressed('A'))
				{
					camera.position = camera.position + right * MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}

			if (!keypressed)
			{
				if (Application::IsKeyPressed('D'))
				{
					camera.position = camera.position - right *  MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}

			if (!keypressed)
			{
				if (Application::IsKeyPressed('S'))
				{
					camera.position = camera.position + view *MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			keypressed = true;

		}

		else	if (Application::IsKeyPressed('A'))
		{
			camera.position = camera.position +  right  * MOVEMENT_SPEED;
			camera.target = camera.position + view;
			if (!keypressed)
			{
				if (Application::IsKeyPressed('W'))
				{
					camera.position = camera.position - view * MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			if (!keypressed)
			{
				if (Application::IsKeyPressed('D'))
				{
					camera.position = camera.position - right *  MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			if (!keypressed)
			{
				if (Application::IsKeyPressed('S'))
				{
					camera.position = camera.position + view *MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			keypressed = true;
		}

		else if (Application::IsKeyPressed('S'))
		{
			camera.position = camera.position + view * MOVEMENT_SPEED;
			camera.target = camera.position + view;
			if (!keypressed)
			{
				if (Application::IsKeyPressed('A'))
				{
					camera.position = camera.position - right * MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			if (!keypressed)
			{
				if (Application::IsKeyPressed('D'))
				{
					camera.position = camera.position + right *  MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			if (!keypressed)
			{
				if (Application::IsKeyPressed('W'))
				{
					camera.position = camera.position + view * MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			keypressed = true;
		}
		else if (Application::IsKeyPressed('D'))
		{
			camera.position = camera.position - right * MOVEMENT_SPEED;
			camera.target = camera.position + view;
			if (!keypressed)
			{
				if (Application::IsKeyPressed('A'))
				{
					camera.position = camera.position + right * MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			if (!keypressed)
			{
				if (Application::IsKeyPressed('W'))
				{
					camera.position = camera.position - view * MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;

				}
			}
			if (!keypressed)
			{
				if (Application::IsKeyPressed('S'))
				{
					camera.position = camera.position + view *MOVEMENT_SPEED;
					camera.position.y = -26;
					camera.target = camera.position + view;
					keypressed = true;
				}
			}
			keypressed = true;
		}
		keypressed = false;
	}
}

void Assignment2::BoundsCheck()
{
	//Box and rect  are used for colliding check, circles are used for interaction checks.
	//Box

	Box electricbox = Box(Vector3(0.25, -31, 30), 5);
	Box trashcanbox = Box(Vector3(0.25, -30, 12), 4);

	//Car represents rect for more accuracy
	Rect carbox = Rect(Vector3(car.GetPosition().x, car.GetPosition().y, car.GetPosition().z), 5.25, 3.25, 5);
	Rect boundaries = Rect(Vector3(0, -26, -4), 30 ,32, 5);

	std::cout << camera.position << std::endl;
	//Circle for fountain circle init
	Circle fountaincircle = Circle(0, -12.5, 12.75);

	//CIRCLES ARE ALL INTERACTION BASED 
	Circle playercircle = Circle(camera.position.x, camera.position.z, 1); //player itself kek
	Circle carinteractioncircle = Circle(car.GetPosition().x, car.GetPosition().z, 4); //circle around the car
	Circle fountaininteractioncircle = Circle(0, -12.5, 13.25); //circle around the fountain
	Circle electriccircle = Circle(0.25, 30, 5.25); //circle around the electricbox
	Circle garbagecircle = Circle(0.25, 12, 4.25); //circle around the trash can


	//Rect checks;
	carcollider = isPointinRect(camera.position, carbox); //car collider check
	boundarycollider = isPointinRect(camera.position, boundaries);

	//Box checls
	electricboxcollider = isPointinBox(camera.position, electricbox); //electricbox check
	garbagecancollider = isPointinBox(camera.position, trashcanbox); //trashcan collider check

	//Circle for fountain since its circular shape.
	//Fountain collider check
	fountaincollider = isPointinCircle(playercircle, fountaincircle);

	//Interaction checks
	carinteraction = isPointinCircle(playercircle, carinteractioncircle);
	fountaininteraction = isPointinCircle(playercircle, fountaininteractioncircle);
	electricboxinteraction = isPointinCircle(playercircle, electriccircle);
	trashcaninteraction = isPointinCircle(playercircle, garbagecircle);

	if (!boundarycollider)
	{
		CollisionChecks();
		std::cout << "lmao" << std::endl;
	}

	//if they are inside the colliding zone stop the player from moving
	if (carcollider)
	{
		if (!isPlayerinCar) //not if the player is in the car
		{
			CollisionChecks();
		}
	}
	if (electricboxcollider)
	{
		CollisionChecks();
	}

	if (fountaincollider)
	{
		CollisionChecks();
	}
	if (garbagecancollider)
	{
		CollisionChecks();
	}


	if (Application::IsKeyPressed('E'))
	{
		//check for distance between 2 things because if both in range 2 texts will be rendered, so render lower distance according to camera pos
	 if (distfromelectricbox < distfromcar)
		{
			if (electricboxinteraction)
			{
				lightturnon = true;
			}
		}
	 if ((distfromfountain -12)< distfromcar) // -12 from radius to offset to outer part of item
		{
			if (fountaininteraction)
			{
				fountainpressed = true;
			}
		}
	 if ((distfromtrashcan - 4 ) < distfromcar)// - 4 from radius to offset to outer part of item
	 {
		 if (trashcaninteraction)
		 {
			 garbagecanpressed = true;
		 }
	 }
	 else if (distfromcar < distfromelectricbox &&
				distfromcar < distfromfountain -12 &&
				distfromcar < distfromtrashcan- 4)
	 {
		 if (carinteraction)
		 {
			 carcooldown = true;
		 }
	 }

	}
}

void Assignment2::Update(double dt)
{
	//Framerate update
	FPS = 1.0 / dt;
	frames = std::to_string(FPS); //convert fps into string

	//Sensitivity updater
	sensitivity = camera.GetSensitivity();//Get sensitivity
	sensitivitycount = std::to_string(sensitivity); //Convert the thing to string 

	//For the carlights to follow the rotation of the car
	float dirX = cos(Math::DegreeToRadian(car.GetRotation() + 90));
	float dirZ = sin(Math::DegreeToRadian(car.GetRotation() + 90));
	lightsdirection = Vector3(dirX, 0, dirZ);

	//Setting light //change this if u cant manage to push pop 
	light[6].position.Set(car.GetPosition().x + 3, car.GetPosition().y, car.GetPosition().z - 2);
	light[7].position.Set(car.GetPosition().x + 3, car.GetPosition().y, car.GetPosition().z + 2);


	#pragma region KEY UPDATES
		if (Application::IsKeyPressed('1'))
		{
			glEnable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('2'))
		{
			glDisable(GL_CULL_FACE);
		}
		if (Application::IsKeyPressed('3'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (Application::IsKeyPressed('4'))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	#pragma endregion

	#pragma region Interactive Booleans Updates
		//bool and its updates

		//Translate booleans updates for the car movements at the road.
		if (translateMax)
		{
			translateAmt += 50 * dt; //speed of translate increase
		}
		else
		{
			translateAmt = -80;
		}

		if (translateAmt > 80)
		{
			translateMax = false;
		}
		else if (translateAmt == -80)
		{
			translateMax = true;
		}
		//End of Translate booleans updates

	
		//Light timer to turn on lights 1 by 1
		if (lightturnon)
		{
			if (lightcount < 7) //below light count
			{
				lightturnon = true;
				lighttimer += dt;

				if (lighttimer >= (60 * dt)) // for every 1 second
				{
					light[lightcount].power = 0.75; //set power to 0.75
					glUniform1f(m_parameters[U_LIGHT0_POWER + lightcount], light[lightcount].power); //pass into the shader
					lighttimer = 0; //reset lighttimer
					lightcount++; //increase the light count
				}
			}
			else
			{
				lightturnon = false; //light has finished turning on
				lightturnedon = true;
			}
		}
		//End of Light timer to turn on lights 1 by 1

		//This timer makes sure player gets into the car at a delay
		if (carcooldown)
		{
			cooldowntimer += dt;
			if (cooldowntimer >= (10 * dt))
			{
				if (isPlayerinCar == false)
				{
					isPlayerinCar = true; //boolean check if player is in car?
					cooldowntimer = 0;
					carcooldown = false;
				}
				else
				{
					camera.CameraTranslator(car.GetPosition().x + 2, car.GetPosition().y + 2.75, car.GetPosition().z - 4);
					isPlayerinCar = false;
					cooldowntimer = 0;
					carcooldown = false;
				}
			}
		}
		//End of timer makes sure player gets into the car at a delay

		//bool Fountain pressed so that interaction text disappears if they leave the fountain
		if (fountainpressed)
		{
			if (distfromfountain < 15) //so if player strays away more the distance from center
			{
				fountainpressed = true; //set the fountain pressed state to true
			}
			else
			{
				fountainpressed = false; //else it would have resetted and the fountain can be pressed again
			}
		}
		//End of bool Fountain pressed so that interaction text disappears if they leave the fountain

		if (garbagecanpressed)
		{
			if (distfromtrashcan < 6) //so if player strays away more the distance from center
			{
				garbagecanpressed = true; //set the garbage can pressed state to true
			}
			else
			{
				garbagecanpressed = false; //else it would have resetted and the fountain can be pressed again
			}
		}

		//Bool that checks if player is already in car
		if (isPlayerinCar)
		{
				isKeyPressed = false; // init key pressed as false first
				if (Application::IsKeyPressed('W'))
				{
					//SPEED LIMITER
					if (car.GetSpeed() > 0.5) //max Speed == 0.5
					{
						car.SetSpeed(0.5f);
					}
					car.SetSpeed(car.GetSpeed() + 1 * dt); //increase speed by 1 unit every dt

					car.MoveCarForward(); //move carforward
					isKeyPressed = true; //Key has been pressed
				}
				if (Application::IsKeyPressed('S'))
				{
					//SPEED LIMITER
					if (car.GetSpeed() < -0.2) //Reversing must be slower than frontward
					{
						car.SetSpeed(-0.2f);
					}
					if (car.GetSpeed() >= 0) //car speed below 0
					{
						car.SetSpeed(car.GetSpeed() - 3 * dt); //slow down faster due to brakes
					}
					car.SetSpeed(car.GetSpeed() - 1 * dt);
					car.MoveCarBackward(); //Move car backward
					isKeyPressed = true; //Key has been pressed
				}
				if (Application::IsKeyPressed('A'))
				{
					//so that turning rate is based on frames and the car's speed
					car.SetRotation(175 * dt * car.GetSpeed()); //rotate car
					camera.GetCarRotation(car.GetRotation()); //update the camera
				}
				if (Application::IsKeyPressed('D'))
				{
					car.SetRotation(-175 * dt * car.GetSpeed()); //rotate car
					camera.GetCarRotation(car.GetRotation()); //update the camera
				}

				camera.CameraTranslator(car.GetPosition().x, car.GetPosition().y + 0.70, car.GetPosition().z);
		}


		//to prevent car from rotating on the spot since rotation is determined by the speed of car
		if (!isKeyPressed)
		{
			car.SetSpeed(0);
		}
	#pragma endregion

	#pragma region Distance Calculation for Interactions
		/*Distance Calculation between 2 objects to determine interactions*/
		distfromcar = sqrt((Math::Square(camera.position.x - car.GetPosition().x) + Math::Square(camera.position.z - car.GetPosition().z)));
		distfromelectricbox = sqrt((Math::Square(camera.position.x - 0.25) + Math::Square(camera.position.z - 30)));
		distfromfountain = sqrt((Math::Square(camera.position.x - 0) + Math::Square(camera.position.z + 12.5)));
		distfromtrashcan = sqrt((Math::Square(camera.position.x - 0.25) + Math::Square(camera.position.z - 12)));
	#pragma endregion

	#pragma region Sensitivity Change
		//Sensitivity Change Function
		if (Application::IsKeyPressed('K'))
		{
			sensitivitychanged = true;
		}
		if (Application::IsKeyPressed('L'))
		{
			sensitivitychanged = true;
		}

		if (sensitivitychanged)
		{
			sensitivitydisappeartimer -= dt;
			if (sensitivitydisappeartimer > 0)
			{
				sensitivitychanged = true;
			}
			else
			{
				sensitivitychanged = false;
				sensitivitydisappeartimer = 1.5;
			}
		}
		//End of Sensitivity Change Function
	#pragma endregion

	camera.GetBoolCar(isPlayerinCar); //pass on the bool value for camera to update camera based on car rotation later on
	BoundsCheck();
	camera.Update(dt); //update camera

}

void Assignment2::Render()
{
	//Clear color & depth buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	//Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	//glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	
	for (int i = 0; i < 8; i++)
	{
		if (light[i].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[i].position.x, light[i].position.y, light[i].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + i], 1, &lightDirection_cameraspace.x);
		}
		else if (light[i].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[i].position;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + i], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[i].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION + i], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[i].position;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + i], 1, &lightPosition_cameraspace.x);
		}
	}

	RenderSkybox();

	#pragma region Environment Objects
		modelStack.PushMatrix();
				modelStack.Translate(0, 0, 0);
				RenderMesh(meshList[GEO_SPEAR], true);
		modelStack.PopMatrix();

		//LAMP POST LIGHTS
		
	#pragma endregion

	#pragma region MAIN CAR RENDER


		modelStack.PushMatrix();
				modelStack.Translate(car.GetPosition().x, car.GetPosition().y, car.GetPosition().z);

		modelStack.PushMatrix();
				modelStack.Translate(0, 10, 0);
				modelStack.Rotate(270, 0, 1, 0);
				RenderText(meshList[GEO_TEXT], "Car", (1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PushMatrix();
				modelStack.Translate(0, 10, 0);
				modelStack.Rotate(-270, 0, 1, 0);
				RenderText(meshList[GEO_TEXT], "Car", (1, 0, 0));
		modelStack.PopMatrix();

				modelStack.Rotate(car.GetRotation()+90, 0, 1, 0);
				modelStack.Scale(2, 2, 2);
				modelStack.PushMatrix();
				modelStack.Translate(-0.35, 0, 0);

		RenderMesh(meshList[GEO_CAR], true);

		modelStack.PushMatrix();
				RenderMesh(meshList[GEO_CAR_STEERING], true);

		modelStack.PushMatrix();
				RenderMesh(meshList[GEO_CAR_WHEELS], true);



		modelStack.PopMatrix();
			modelStack.PopMatrix();
				modelStack.PopMatrix();
					modelStack.PopMatrix();
	#pragma endregion

	


	#pragma region TEXT RENDERS
		RenderTextOnScreen(meshList[GEO_TEXT], "FPS:", Color(1, 0, 0), 2, 27, 29);
		RenderTextOnScreen(meshList[GEO_TEXT], frames, Color(1, 0, 0), 2, 31, 29);

		if (isPlayerinCar) //to prevent interactions from showing onto the screen in the car
		{
			multipleinstance = true;
		}
		else
		{
			multipleinstance = false;
		}
	//Interactions portion to display text corrcectly based on player distance between 2 different interactions at 1 time
			if ((distfromcar < distfromfountain - 12) && 
				(distfromcar < distfromelectricbox)  &&
				(distfromcar < distfromtrashcan -4))
			{
				if (carinteraction)
				{
					if (!isPlayerinCar)
					{
						RenderTextOnScreen(meshList[GEO_CARTEXT], "Press 'E' to interact with the car ", Color(1, 0, 0), 2, 3.5, 1);
					}
					else
					{
						RenderTextOnScreen(meshList[GEO_CARTEXT], "Press 'E' to get out of the car ", Color(1, 0, 0), 2, 5, 1);
					}
				}
			}

			if (!multipleinstance) // if player's not inside the car, then..
			{
			 if (distfromelectricbox < distfromcar )
			{
				if (electricboxinteraction)
				{
					if (lightturnon)
					{
						RenderTextOnScreen(meshList[GEO_LIGHTBOXTEXT], "The lights are turning on!", Color(1, 0, 0), 2, 8.5, 15);
					}
					else
					{
						RenderTextOnScreen(meshList[GEO_LIGHTBOXTEXT], "Press 'E' to interact with the lightbox ", Color(1, 0, 0), 2, 1, 1);
					}
				}
			}

			  if ((distfromfountain - 12) < distfromcar)
			{
				if (fountaininteraction)
				{
					if (!fountainpressed)
					{
						RenderTextOnScreen(meshList[GEO_FOUNTAINTEXT], "Press 'E' to interact with the fountain ", Color(1, 0, 0), 2, 1.5, 1);
					}
					else
					{
						if (!lightturnedon)
						{
							RenderTextOnScreen(meshList[GEO_FOUNTAINTEXT], "Turn the lights on first!", Color(1, 0, 0), 2, 8.5, 20);
						}
						else
						{
							RenderTextOnScreen(meshList[GEO_FOUNTAINTEXT], "It's an empty fountain...", Color(1, 0, 0), 2, 9.5, 20);
						}
					}
				}
			}
			   if ((distfromtrashcan-4) < distfromcar)
			{
				if (trashcaninteraction)
				{
					if (!garbagecanpressed)
					{
						RenderTextOnScreen(meshList[GEO_TRASHCANTEXT], "Press 'E' to interact with the trashcan ", Color(1, 0, 0), 2, 1.5, 1);
					}
					else
					{
						if (!lightturnedon)
						{
							RenderTextOnScreen(meshList[GEO_TRASHCANTEXT], "Turn the lights on first!", Color(1, 0, 0), 2, 8.5, 20);
						}
						else
						{
							RenderTextOnScreen(meshList[GEO_TRASHCANTEXT], "You have nothing to throw.", Color(1, 0, 0), 2, 9, 20);
						}
					}
				}
			}


		}
			if (sensitivitychanged)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], "Sensitivity:", Color(1, 0, 0), 2, 1, 29);
				RenderTextOnScreen(meshList[GEO_TEXT], sensitivitycount, Color(1, 0, 0), 2, 13, 29);
			}
	#pragma endregion

}

void Assignment2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once 
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}



}

void Assignment2::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0.5, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0, -0.5);
	modelStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, 0.5, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0 , 0, 0.5);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(-0.5, 0 ,0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Translate(0, -0.5, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void Assignment2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Assignment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	
	glEnable(GL_DEPTH_TEST);
}

void Assignment2::Exit()
{
	// Cleanup VBO here
	glDeleteProgram(m_programID);

}
