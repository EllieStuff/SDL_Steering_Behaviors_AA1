#include "Obstacle.h"

void Obstacle::SetStats(float gRadius, Vector2D gPosition)
{
	radius = gRadius;
	position = gPosition;
}

void Obstacle::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), position.x, position.y, radius, 225, 225, 225, 1);
}