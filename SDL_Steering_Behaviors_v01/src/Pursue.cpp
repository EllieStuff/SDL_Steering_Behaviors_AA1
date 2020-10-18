#include "Pursue.h"

Pursue::Pursue()
{
}

Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Pursuer *pursuer, float dtime)
{
	//float T = 1;
	////float T = Vector2D::Distance(bros[id].getPosition(), bros[id].getTarget()->getPosition()) / bros[id].getTarget()->getSpeed();
	//Vector2D predictedTarget = bros[id].getTarget()->getPosition() + bros[id].getTarget()->getVelocity() * T;

	//Vector2D desiredVelocity = predictedTarget - bros[id].getPosition();
	//desiredVelocity.Normalize();
	//desiredVelocity *= bros[id].getMaxVelocity();

	//Vector2D steeringForce = desiredVelocity - bros[id].getVelocity();
	//steeringForce.Truncate(bros[id].getMaxForce());

	////d = v*t + 1/2*(a*t^2)  --  a = F/m
	//Vector2D acc = steeringForce / bros[id].getMass();
	//bros[id].setVelocity(((bros[id].getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * bros[id].getMaxVelocity());
	//bros[id].setPosition(bros[id].getPosition() + (bros[id].getVelocity() * dtime));


	float T = 1;
	//float T = Vector2D::Distance(pursuer->getPosition(), pursuer->getTarget()->getPosition()) / pursuer->getTarget()->getSpeed();
	Vector2D predictedTarget = pursuer->getTarget()->getPosition() + pursuer->getTarget()->getVelocity() * T;

	Vector2D desiredVelocity = predictedTarget - pursuer->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= pursuer->getMaxVelocity();

	Vector2D steeringForce = desiredVelocity - pursuer->getVelocity();
	steeringForce.Truncate(pursuer->getMaxForce());

	//d = v*t + 1/2*(a*t^2)  --  a = F/m
	Vector2D acc = steeringForce / pursuer->getMass();
	pursuer->setVelocity(((pursuer->getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * pursuer->getMaxVelocity());
	pursuer->setPosition(pursuer->getPosition() + (pursuer->getVelocity() * dtime));

}
