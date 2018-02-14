#pragma once
#include "MyMath.h"
#include "Vector3.h"

class Dinosaur
{
private:
	Vector3 dinosaurPosition; //car position
	Vector3 direction;

	float rotation;
	float speed;
	float speed2;
	float acceleration;

public:
	Dinosaur();
	~Dinosaur();

	//functions to move car forward and backward
	void MoveDinoForward();
	void MoveDinoBackward();

	//accesors
	float GetRotation(void);
	float GetSpeed(void); // <-- final value of speed
	float GetSpeed2(void); // speed value that is affected by accel that is later passed in
	float GetAcceleration(void);
	Vector3 GetPosition(void);

	//setters
	void SetRotation(float _RotationAmount);
	void SetSpeed(float speedsetter);
	void SetSpeed2(float speed2setter);
	void SetAcceleration(float accel);
	void SetPosition(Vector3);



	


};