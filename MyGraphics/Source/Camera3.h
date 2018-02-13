#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"

class Camera3 : public Camera
{
private:
	//Camera movements
	float horizontalAngle; 
	float verticalAngle;

	//boolean for first time loaded in to prevent the snapping of camera
	bool isFirst;

	//Mouse movement values
	double xMouse;
	double yMouse;

	//yaw and pitch values
	float yaw;
	float pitch;
	
	float dinosaurrotation;

	bool temporary;// this is temp
	//Camera vec 3's
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view;
	Vector3 right;

public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Camera3();
	~Camera3();

	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();

	//move the camera somewhere
	virtual void CameraTranslator(float, float, float);

	//function that sets back everything to zero for the mouse
	void ResetFPS(void);

	//Functions that make the camera turn along with the dinosaur
	void GetDinosaurRotation(float); //getting car rotation indirectly
	bool GetDinosaurBool(bool); //pass value of bool in "main" for here to check

	

};

#endif