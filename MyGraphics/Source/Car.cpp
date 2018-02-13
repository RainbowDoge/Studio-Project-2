#include "Car.h"


Car::Car()
{
	x = 0;
	y = 0;
	z = 0;
	speed = 0;
	carPosition = (x, y, z);

}

Car::~Car()
{
}

void Car::MoveCarForward()
{
	float dirX = cos(Math::DegreeToRadian(-rotation));
	float dirZ = sin(Math::DegreeToRadian(-rotation));
	direction = Vector3(dirX, 0, dirZ);
	carPosition += direction * GetSpeed();
}

void Car::MoveCarBackward()
{
	float dirX = cos(Math::DegreeToRadian(-rotation));
	float dirZ = sin(Math::DegreeToRadian(-rotation));
	direction = Vector3(dirX,0, dirZ);
	carPosition -= direction * -GetSpeed();
}

float Car::GetRotation(void)
{
	return rotation;
}

float Car::GetSpeed(void)
{
	return speed;
}

void Car::SetRotation(float _RotationAmount)
{
	rotation += _RotationAmount;
}

Vector3 Car::GetPosition(void)
{
	return carPosition;
}

void Car::SetPosition(Vector3 vec)
{
	carPosition = vec;
}


void Car::SetSpeed(float speedsetter)
{
	speed = speedsetter;
}

