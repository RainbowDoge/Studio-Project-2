#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "timer.h"

Camera3::Camera3()
{
	xMouse = 0;
	yMouse = 0;
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	 horizontalAngle = 3.14f;
	 verticalAngle = 0.0f;

	 isFirst = true;

	 sensitivity = 1.0f;
}

void Camera3::ResetFPS(void)
{
	Application::SetMousePos();
	horizontalAngle = 0;
	verticalAngle = 0;
}

void Camera3::Update(double dt)
{

	static const float CAMERA_SPEED = 2.0f;
	static const float MOVEMENT_SPEED = 0.25f;

	view = target - position;
	right = view.Cross(up);
	
	if (isFirst)
	{
		xMouse = 400;
		yMouse = 300;
		isFirst = false;
	}
	else
	{
		Application::GetMousePos(xMouse, yMouse);
	}

	horizontalAngle += (sensitivity * dt * float(800 / 2 - xMouse));
	verticalAngle += (sensitivity * dt * float(600 / 2 - yMouse));

	yaw = horizontalAngle;
	pitch = verticalAngle;

	view = (target - position).Normalized();
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	Mtx44 rotation;
	Mtx44 rotation2;

	rotation.SetToRotation(yaw, up.x, up.y, up.z);
	rotation2.SetToRotation(pitch, right.x, right.y, right.z);

	view = rotation * rotation2 * view;
	target = position + view;

	if (isPlayerincar) // they are in car and the camera rotates based on how the car moves
	{
		float dirX = cos(Math::DegreeToRadian(-carrotation));
		float dirZ = sin(Math::DegreeToRadian(-carrotation));
		Vector3 Direction = Vector3(dirX, 0, dirZ);
		view = view + Direction;
		target = position + view;
	}

	else //else they are not in car and they can move by WASD
	{
		if (Application::IsKeyPressed('A'))
		{
			position = position - right * MOVEMENT_SPEED;
			position.y = -26;
			target = position + view;
		}

		if (Application::IsKeyPressed('D'))
		{
			position = position + right *  MOVEMENT_SPEED;
			position.y = -26;
			target = position + view;
		}
		if (Application::IsKeyPressed('W'))
		{
			position = position + view * MOVEMENT_SPEED;
			position.y = -26;
			target = position + view;
		}

		if (Application::IsKeyPressed('S'))
		{
			position = position - view *MOVEMENT_SPEED;
			position.y = -26;
			target = position + view;
		}
	
	}

	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}

	//Sensitivity Changes
	if (Application::IsKeyPressed('K'))
	{
		if (sensitivity > 5)
		{
			sensitivity = 5;
		}
		else
		{
			sensitivity += dt;
		}
		std::cout << sensitivity << std::endl;
	}

	if (Application::IsKeyPressed('L'))
	{
		if (sensitivity < 0.1)
		{
			sensitivity = 0.1;
		}
		else
		{
			sensitivity -= dt;
		}
		std::cout << sensitivity << std::endl;
	}
	//End of Sensitivity Change

	//Arrow Keys
	if (Application::IsKeyPressed(VK_LEFT))
	{

		yaw = (float)(sensitivity * dt);
		view = (target - position).Normalized();
		right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Mtx44 rotation;
		rotation.SetToRotation(yaw, up.x, up.y,up.z);

		view = rotation * view;
		target = position + view;

	}

	if (Application::IsKeyPressed(VK_RIGHT) )
	{
		 yaw = (float)(-sensitivity * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Mtx44 rotation;
		rotation.SetToRotation(yaw, up.x, up.y, up.z);

		view = rotation * view;
		target = position + view;
	}

	if (Application::IsKeyPressed(VK_UP) )
	{

		 pitch = (float)(sensitivity * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);

		view = rotation * view;
		target = position + view;

	}

	if (Application::IsKeyPressed(VK_DOWN))
	{
		
		pitch = (float)(-sensitivity * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();

		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);

		view = rotation * view;
		target = position + view;

	}
	//End of Arrow Keys Movement
	ResetFPS(); //Reset mousepos and stuffs
}

void Camera3::CameraTranslator(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	target = position + view;
}
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	view = (target - position).Normalized();
	right = view.Cross(up);
}

bool Camera3::GetBoolCar(bool isPlayer)
{
	isPlayerincar = isPlayer;
	return isPlayerincar;
}

void Camera3::GetCarRotation(float carrot)
{
	carrotation = carrot;
}
float Camera3::GetSensitivity(void)
{
	return sensitivity;
}



