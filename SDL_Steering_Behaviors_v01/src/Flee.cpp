#include "Flee.h"

Flee::Flee()
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D desiredVelocity = (agent->getTarget() - agent->getPosition()) * -1;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Truncate(agent->getMaxForce());

	//d = v*t + 1/2*(a*t^2)  --  a = F/m
	Vector2D acc = steeringForce / agent->getMass();
	agent->setVelocity(((agent->getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + (agent->getVelocity() * dtime));
}
