#include "Flocking.h"

Flocking::Flocking() {

	min_distance = 5;
	max_distance = 10;

	//sep_force.x = 0; sep_force.y = 0;
	//coh_force.x = 0; coh_force.y = 0;
	//ali_force.x = 0; ali_force.y = 0;

	sep_const = 5.0f;
	coh_const = 2.5f;
	ali_const = 1.0f;

	flock_const = 3.0f;
}

Flocking::~Flocking() {}

void Flocking::Separation(std::vector<Agent*> agents)
{
	sep_force.resize(agents.size());

	for (int i = 0; i < agents.size(); i++)
	{
		int bros = 0;
		for (int j = 0; j < agents.size(); j++)
		{
			if (i == j) { }
			else {
				bros++;
				my_pos = agents[i]->getPosition();
				bro_pos = agents[j]->getPosition();

				float x = my_pos.x - bro_pos.x;
				float y = my_pos.y - bro_pos.y;

				if (x < 0) { x *= -1; }
				if (y < 0) { y *= -1; }

				float root = sqrt(pow(x, 2) + pow(y, 2));

				if (root < min_distance) {
					sep_force[i] += my_pos - bro_pos;
				}
			}
		}
		sep_force[i] /= bros;
		sep_force[i] = sep_force[i].Normalize();
	}
}

void Flocking::Cohesion(std::vector<Agent*> agents)
{
	coh_force.resize(agents.size());

	for (int i = 0; i < agents.size(); i++)
	{
		int bros = 0;
		for (int j = 0; j < agents.size(); j++)
		{
			if (i == j) {}
			else {
				bros++;
				my_pos = agents[i]->getPosition();
				bro_pos = agents[j]->getPosition();

				float x = my_pos.x - bro_pos.x;
				float y = my_pos.y - bro_pos.y;

				if (x < 0) { x *= -1; }
				if (y < 0) { y *= -1; }

				float root = sqrt(pow(x, 2) + pow(y, 2));

				if (root > max_distance) {
					coh_force[i] += bro_pos;
				}
			}
		}
		coh_force[i] /= bros;
		coh_force[i] -= agents[i]->getPosition();
		coh_force[i] = coh_force[i].Normalize();
	}
}

void Flocking::Alignment(std::vector<Agent*> agents)
{
	ali_force.resize(agents.size());

	for (int i = 0; i < agents.size(); i++)
	{
		int bros = 0;
		for (int j = 0; j < agents.size(); j++)
		{
			if (i == j) {}
			else {
				bros++;
				my_pos = agents[i]->getPosition();
				bro_pos = agents[j]->getPosition();

				float x = my_pos.x - bro_pos.x;
				float y = my_pos.y - bro_pos.y;

				if (x < 0) { x *= -1; }
				if (y < 0) { y *= -1; }

				float root = sqrt(pow(x, 2) + pow(y, 2));

				if (root < max_distance && root > min_distance)
				{
					ali_force[i] = agents[j]->getVelocity();
				}
			}
		}
		ali_force[i] /= bros;
		ali_force[i] = ali_force[i].Normalize();
	}
}

void Flocking::FlockingForce(std::vector<Agent*> agents, float dtime)
{
	flock_force.resize(agents.size());

	for (int i = 0; i < agents.size(); i++)
	{
		flock_force[i] = (sep_force[i]*sep_const) + (coh_force[i]*coh_const) + (ali_force[i]*ali_const);

		sep_force[i].x = sep_force[i].y = 0;
		coh_force[i].x = coh_force[i].y = 0;
		ali_force[i].x = ali_force[i].y = 0;

		flock_force[i] *= flock_const;

		flock_force[i].Truncate(agents[i]->getMaxForce());
		Vector2D acc = flock_force[i] / agents[i]->getMass();

		agents[i]->setVelocity(((agents[i]->getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * agents[i]->getMaxVelocity());
		agents[i]->setPosition(agents[i]->getPosition() + (agents[i]->getVelocity() * dtime));
	}
}
