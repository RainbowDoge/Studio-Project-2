#ifndef  COLLISION_H
#define COLLISION_H
#include "Vector3.h"

struct Box
{
	Vector3 position;

	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;


	Box(Vector3 _position, float _size)
	{
		position = _position;
		minX = position.x - _size;
		maxX = position.x + _size;
		minY = position.y - _size;
		maxY = position.y + _size;
		minZ = position.z - _size;
		maxZ = position.z + _size;

	}

};

struct Rect
{
	Vector3 position;

	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;

	Rect(Vector3 _position, float _length, float _width, float _height)
	{
		position = _position;
		minX = position.x - _length;
		maxX = position.x + _length;
		minY = position.y - _height;
		maxY = position.y + _height;
		minZ = position.z - _width;
		maxZ = position.z + _width;

	}

};

struct Circle
{
	float xpos;
	float zpos;
	float radius;

	Circle()
	{
		xpos = 0;
		zpos = 0;
		radius = 0;
	}
	Circle(float x, float z, float r)
	{
		xpos = x;
		zpos = z;
		radius = r;
	}

};

#endif 
