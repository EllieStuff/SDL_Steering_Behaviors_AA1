#include "AvoidObst.h"

AvoidObst::AvoidObst()
{
}

AvoidObst::~AvoidObst()
{
}

void AvoidObst::applySteeringForce(Pursuer *agent, Vector2D obstPos, float dtime)
{
	Vector2D desiredVelocity = (obstPos - agent->getPosition()) * -1;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Truncate(agent->getMaxForce());

	//d = v*t + 1/2*(a*t^2)  --  a = F/m
	Vector2D acc = steeringForce / agent->getMass();
	agent->setVelocity(((agent->getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + (agent->getVelocity() * dtime));
}
