#pragma once
#include "Pursuer.h"
//#include "Flocking.h"

class Pursue :
	public Pursuer::SteeringBehavior_2
{
public:
	Pursue();
	~Pursue();
	void applySteeringForce(Pursuer *pursuer, float dtime);
};
