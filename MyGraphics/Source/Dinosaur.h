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

public:
	Dinosaur();
	~Dinosaur();

	//functions to move car forward and backward
	void MoveDinoForward();
	void MoveDinoBackward();

	//accesors
	float GetSpeed(void);
	float GetRotation(void);
	Vector3 GetPosition(void);

	//setters
	void SetRotation(float _RotationAmount);
	void SetSpeed(float speedsetter);
	void SetPosition(Vector3);


};