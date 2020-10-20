#pragma once
#include "Agent.h"
#include "Raymanager.h"

class Pursuer
{
public:
	RayManager *rayManager;
	class SteeringBehavior_2
	{
	public:
		SteeringBehavior_2() {};
		virtual ~SteeringBehavior_2() {};

		virtual void Separation(int p, std::vector<Pursuer>& bros) {};
		virtual void Cohesion(int p, std::vector<Pursuer>& bros) {};
		virtual void Alignment(int p, std::vector<Pursuer>& bros) {};
		virtual void PursueForce(Pursuer *pursuer, float dtime) {};

		virtual void FlockingForce(int p, std::vector<Pursuer>& bros, float dtime) {};
	};

	class AvoidObst
	{
	public:
		AvoidObst();
		~AvoidObst();
		void applySteeringForce(Pursuer *agent, Vector2D obstPos, float dtime);
	};
	
	std::vector<Pursuer>* bros;

private:
	
	AvoidObst *fleeBehaviour;
	SteeringBehavior_2 *steering_behaviour;
	

	Vector2D position;
	Vector2D velocity;
	//Vector2D *target;
	Agent *target;

	float speed;
	float orientation;
	float max_force;
	float max_velocity;
	float mass;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

	//int min_pursuers = 20;

	int id;


public:
	Pursuer();
	Pursuer(int _id, std::vector<Pursuer>* vec);
	~Pursuer();
	Vector2D getPosition();
	//Vector2D getTarget();
	Agent* getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior_2 *behavior);
	void setPosition(Vector2D position);
	//void setTarget(Vector2D target);
	void setTarget(Agent *target);
	void setVelocity(Vector2D velocity);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Pursuer::loadSpriteTexture(char* filename, int num_frames = 1);

};
