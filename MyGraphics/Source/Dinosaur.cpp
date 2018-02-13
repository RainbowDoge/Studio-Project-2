#include "Dinosaur.h"


Dinosaur::Dinosaur()
{
	speed = 0;

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

void Dinosaur::SetRotation(float _RotationAmount)
{
	rotation += _RotationAmount;
}

Vector3 Dinosaur::GetPosition(void)
{
	return dinosaurPosition;
}

void Dinosaur::SetPosition(Vector3 vec)
{
	dinosaurPosition = vec;
}


void Dinosaur::SetSpeed(float speedsetter)
{
	speed = speedsetter;
}

