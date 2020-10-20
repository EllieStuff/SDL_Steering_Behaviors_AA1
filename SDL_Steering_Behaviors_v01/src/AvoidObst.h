#pragma once
#include "Pursuer.h"

class AvoidObst
{
public:
	AvoidObst();
	~AvoidObst();
	void applySteeringForce(Pursuer *agent, Vector2D obstPos, float dtime);
};
