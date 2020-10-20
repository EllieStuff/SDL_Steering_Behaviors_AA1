#pragma once
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"

const int max_obstacles = 4;

class Obstacle
{
public:
	float radius;
	Vector2D position;

	void Obstacle::SetStats(float gRadius, Vector2D gPosition);

	void Obstacle::draw();
};