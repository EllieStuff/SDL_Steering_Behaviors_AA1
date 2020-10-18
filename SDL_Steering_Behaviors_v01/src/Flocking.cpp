#include "Flocking.h"

Flocking::Flocking() {

	min_distance = 100;
	max_distance = 300;

	//sep_force.x = 0; sep_force.y = 0;
	//coh_force.x = 0; coh_force.y = 0;
	//ali_force.x = 0; ali_force.y = 0;

	sep_const = 500.0f;
	coh_const = 400.0f;
	ali_const = 300.0f;

	flock_const = 300.0f;
}

Flocking::~Flocking() {}

void Flocking::Separation(int p, std::vector<Pursuer>& bros)
{
	sep_force.resize(bros.size());
	sep_force[p].x = 0; sep_force[p].y = 0;

	float bro_count = 0;

	for (int i = 0; i < bros.size(); i++)
	{
			if (i == p) { }
			else { bro_count++;
				my_pos = bros.operator[](p).getPosition();
				bro_pos = bros.operator[](i).getPosition();

				float x = my_pos.x - bro_pos.x;
				float y = my_pos.y - bro_pos.y;

				if (x < 0) { x *= -1; }
				if (y < 0) { y *= -1; }

				float root = sqrt(pow(x, 2) + pow(y, 2));

				if (root < min_distance) {
					sep_force[p] += my_pos - bro_pos;
				}
			}
		sep_force[p].x /= bro_count;
		sep_force[p].y /= bro_count;

		sep_force[p].x = sep_force[p].Normalize().x;
		sep_force[p].y = sep_force[p].Normalize().y;
		}
}

void Flocking::Cohesion(int p, std::vector<Pursuer>& bros)
{
	coh_force.resize(bros.size());
	coh_force[p].x = 0; coh_force[p].y = 0;

	float bro_count = 0;

	for (int i = 0; i < bros.size(); i++)
	{
		if (i == p) {}
		else { bro_count++;
			my_pos = bros.operator[](p).getPosition();
			bro_pos = bros.operator[](i).getPosition();

			float x = my_pos.x - bro_pos.x;
			float y = my_pos.y - bro_pos.y;

			if (x < 0) { x *= -1; }
			if (y < 0) { y *= -1; }

			float root = sqrt(pow(x, 2) + pow(y, 2));

			if (root > max_distance) {
				coh_force[p] += bro_pos;
			}
		}
		coh_force[p].x /= bro_count;
		coh_force[p].y /= bro_count;

		coh_force[p].x -= bros.operator[](p).getPosition().x;
		coh_force[p].y -= bros.operator[](p).getPosition().y;

		coh_force[p].x = coh_force[p].Normalize().x;
		coh_force[p].y = coh_force[p].Normalize().y;
	}
}

void Flocking::Alignment(int p, std::vector<Pursuer>& bros)
{
	ali_force.resize(bros.size());
	ali_force[p].x = 0; ali_force[p].y = 0;

	float bro_count = 0;

	for (int i = 0; i < bros.size(); i++)
	{
		if (i == p) {}
		else { bro_count++;
			my_pos = bros.operator[](p).getPosition();
			bro_pos = bros.operator[](i).getPosition();

			float x = my_pos.x - bro_pos.x;
			float y = my_pos.y - bro_pos.y;

			if (x < 0) { x *= -1; }
			if (y < 0) { y *= -1; }

			float root = sqrt(pow(x, 2) + pow(y, 2));

			if (root > min_distance && root < max_distance) {
				ali_force[p] += bros.operator[](i).getVelocity();
			}
		}
		ali_force[p].x /= bro_count;
		ali_force[p].y /= bro_count;

		ali_force[p].x = ali_force[p].Normalize().x;
		ali_force[p].y = ali_force[p].Normalize().y;
	}
}

void Flocking::FlockingForce(int p, std::vector<Pursuer>& bros, float dtime)
{
	flock_force.resize(bros.size());
	flock_force[p].x = 0; flock_force[p].y = 0;

		flock_force[p].x = (sep_force[p].x*sep_const) + (coh_force[p].x*coh_const) + (ali_force[p].x*ali_const);
		flock_force[p].y = (sep_force[p].y*sep_const) + (coh_force[p].y*coh_const) + (ali_force[p].y*ali_const);

		flock_force[p].x *= flock_const;
		flock_force[p].y *= flock_const;

		flock_force[p].Truncate(bros.operator[](p).getMaxForce());
		Vector2D acc = flock_force[p] / bros.operator[](p).getMass();

		bros.operator[](p).setVelocity(((bros.operator[](p).getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * bros.operator[](p).getMaxVelocity());
		bros.operator[](p).setPosition(bros.operator[](p).getPosition() + (bros.operator[](p).getVelocity() * dtime));

}

void Flocking::applySteeringForce(Pursuer *pursuer, float dtime)
{
	Vector2D desiredVelocity = pursuer->getTarget() - pursuer->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= pursuer->getMaxVelocity();

	Vector2D steeringForce = desiredVelocity - pursuer->getVelocity();
	steeringForce.Truncate(pursuer->getMaxForce());
	Vector2D acc = steeringForce / pursuer->getMass();
	//d = v*t + 1/2*(a*t^2)  --  a = F/m
	pursuer->setVelocity(((pursuer->getVelocity() * dtime) + ((acc * dtime * dtime) / 2)).Normalize() * pursuer->getMaxVelocity());
	pursuer->setPosition(pursuer->getPosition() + (pursuer->getVelocity() * dtime));


}