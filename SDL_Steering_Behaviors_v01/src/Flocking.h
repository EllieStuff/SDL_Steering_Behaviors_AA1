#pragma once
#include "Agent.h"

class Flocking :
	public Agent::SteeringBehavior
{
public:

	float min_distance;
	float max_distance;

	Vector2D my_pos;
	Vector2D bro_pos;

	std::vector<Vector2D> sep_force;
	std::vector<Vector2D> coh_force;
	std::vector<Vector2D> ali_force;

	std::vector<Vector2D> flock_force;

	float sep_const, coh_const, ali_const, flock_const;

	Flocking();
	~Flocking();

	void Separation(std::vector<Agent*> agents);
	void Cohesion(std::vector<Agent*> agents);
	void Alignment(std::vector<Agent*> agents);
	void FlockingForce(std::vector<Agent*> agents, float dtime);
};
