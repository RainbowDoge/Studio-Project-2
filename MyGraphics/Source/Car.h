#pragma once
#include "MyMath.h"
#include "Vector3.h"

class Car
{
private:
	Vector3 carPosition; //car position
	Vector3 direction;

	float rotation;
	float speed;

	//pos coords of car
	float x;
	float y;
	float z;

public:
	Car();
	~Car();

	//functions to move car forward and backward
	void MoveCarForward();
	void MoveCarBackward();

	//accesors
	float GetSpeed(void);
	float GetRotation(void);
	Vector3 GetPosition(void);

	//setters
	void SetRotation(float _RotationAmount);
	void SetSpeed(float speedsetter);
	void SetPosition(Vector3);


};