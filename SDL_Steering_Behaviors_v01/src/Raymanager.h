#pragma once
#include "Obstacle.h"
#include "utils.h"
#include <math.h>

class RayManager
{
public:
	Obstacle *obstacles;

	int rayNum;
	float raySeparation;
	float rayLength;
	

	//Actor's position
	Vector2D *position;
	//Veldir will be the normalized direction of the character's velocity, since the character is always facing in this velocity vector,
	//the velDir determines the facing forward vector of the actor, all check rays are constructed from this facing forward vector
	Vector2D velDir;
	//Pointer to the actor's velocity
	Vector2D *velocity;


	RayManager(int gRayNum, float gRaySeparation, float gRayLength, Vector2D *gPosition, Vector2D *gVelocity);

	void UpdateData(Vector2D gPosition, Vector2D gVelocity);

	bool CheckObstacleInRadius(Obstacle gObstacle);

	Vector2D GetRotatedVector(Vector2D initVec, float rotAngle);

	float GetDistLinePoint(Vector2D dir, Vector2D lineP, Vector2D point);

	void drawRayAngle(float gRayAngle);

	void drawAllRays();

	Vector2D Update();
};