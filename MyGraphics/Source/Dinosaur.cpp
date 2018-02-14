#include "Dinosaur.h"


Dinosaur::Dinosaur()
{
	speed = 0;
	rotation = 0;
	acceleration = 0;

}

Dinosaur::~Dinosaur()
{
}

void Dinosaur::MoveDinoForward()
{
	float dirX = cos(Math::DegreeToRadian(-rotation));
	float dirZ = sin(Math::DegreeToRadian(-rotation));
	direction = Vector3(dirX, 0, dirZ);
	dinosaurPosition += direction * GetSpeed();
}

void Dinosaur::MoveDinoBackward()
{
	float dirX = cos(Math::DegreeToRadian(-rotation));
	float dirZ = sin(Math::DegreeToRadian(-rotation));
	direction = Vector3(dirX,0, dirZ);
	dinosaurPosition -= direction * -GetSpeed();
}

float Dinosaur::GetRotation(void)
{
	return rotation;
}

float Dinosaur::GetSpeed(void)
{
	return speed;
}

Vector3 Dinosaur::GetPosition(void)
{
	return dinosaurPosition;
}

float Dinosaur::GetAcceleration(void)
{
	return acceleration;
}

float Dinosaur::GetSpeed2(void)
{
	return speed2;
}

void Dinosaur::SetPosition(Vector3 vec)
{
	dinosaurPosition = vec;
}

void Dinosaur::SetRotation(float _RotationAmount)
{
	rotation += _RotationAmount;
}

void Dinosaur::SetSpeed(float speedsetter)
{
	speed = speedsetter;
}

void Dinosaur::SetSpeed2(float speed2setter)
{
	speed2 = speed2setter;
}


void Dinosaur::SetAcceleration(float accel)
{
	acceleration = accel;
}