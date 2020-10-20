#include "Raymanager.h"

RayManager::RayManager(int gRayNum, float gRaySeparation, float gRayLength, Vector2D *gPosition, Vector2D *gVelocity)
{
	rayNum = gRayNum;
	raySeparation = gRaySeparation;
	rayLength = gRayLength;
	position = gPosition;
	velocity = gVelocity;
}

void RayManager::UpdateData(Vector2D gPosition, Vector2D gVelocity)
{

}

bool RayManager::CheckObstacleInRadius(Obstacle gObstacle)
{
	float rawDist = Mod(*position - gObstacle.position);
	if (rawDist - gObstacle.radius - rayLength < 0)
	{
		return true;
	}
	return false;
}

Vector2D RayManager::GetRotatedVector(Vector2D initVec, float rotAngle)
{
	Vector2D finalPos = Normalized(initVec);
	Vector2D tPos = finalPos;
	finalPos.x = (tPos.x * cos(rotAngle)) - (tPos.y * sin(rotAngle));
	finalPos.y = (tPos.x * sin(rotAngle)) + (tPos.y * cos(rotAngle));

	return finalPos;
}

float RayManager::GetDistLinePoint(Vector2D dir, Vector2D lineP, Vector2D point)
{
	float A = dir.y;
	float B = -dir.x;
	float C = -A * lineP.x + (-B * lineP.y);

	float res1 = abs(A*point.x + B * point.y + C);
	float res2 = sqrt(A * A + B * B);

	return abs(res1 / res2);
}

void RayManager::drawRayAngle(float gRayAngle)
{
	Vector2D finalPos = (Normalized(velDir)) * rayLength;
	Vector2D tPos = finalPos;
	finalPos.x = (tPos.x * cos(gRayAngle)) - (tPos.y * sin(gRayAngle));
	finalPos.y = (tPos.x * sin(gRayAngle)) + (tPos.y * cos(gRayAngle));


	draw_circle(TheApp::Instance()->getRenderer(), position->x + finalPos.x, position->y + finalPos.y, 5, 255, 0, 0, 1);
}

void RayManager::drawAllRays()
{
	float rayAngle = fmod((float)((360 - (rayNum * raySeparation / 2)) + (raySeparation / 2)), (float)360);
	for (int i = 0; i < rayNum; i++)
	{
		drawRayAngle(rayAngle * DEG2RAD);
		rayAngle = fmod((rayAngle + raySeparation), 360);
	}
}

//The manager returns a Vector2D if it collides with an obstacle!
Vector2D RayManager::Update()
{

	if (Mod(*velocity) > 0)
	{
		velDir = Normalized(*velocity);
	}


	float rayAngle = fmod((float)((360 - (rayNum * raySeparation / 2)) + (raySeparation / 2)), (float)360);

	for (int i = 0; i < rayNum; i++)
	{
		for (int j = 0; j < max_obstacles; j++)
		{
			if (CheckObstacleInRadius(obstacles[j]))
			{
				float dist = GetDistLinePoint(GetRotatedVector(velDir, rayAngle * DEG2RAD), *position, obstacles[j].position);
				if (dist < obstacles[j].radius)
				{
					//WE HAVE COLLISION
					//If the pursuer is inside the circle, push them back a bit
					if (Mod(*position - obstacles[j].position) < obstacles[j].radius)
					{
						*position = obstacles[j].position + (Normalized(*position - obstacles[j].position) * obstacles[j].radius);
					}
					return obstacles[j].position;
				}
				dist = 0;
			}
		}
		rayAngle = fmod((rayAngle + raySeparation), 360);
	}
	return NULL;
}

