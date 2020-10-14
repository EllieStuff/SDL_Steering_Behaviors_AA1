#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Truncate(agent->getMaxForce());
	//d = v*t + 1/2*(a*t^2)  --  a = F/m
	agent->setVelocity(((agent->getVelocity() * dtime) + ((steeringForce * dtime * dtime) / (2 * agent->getMass()))).Normalize() * agent->getMaxVelocity());
	agent->setPosition(agent->getPosition() + (agent->getVelocity() * dtime));


}
