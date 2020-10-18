#pragma once
#include <vector>
#include "Scene.h"
#include "Flocking.h"
#include "Seek.h"

class SceneFlocking :
	public Scene
{
public:
	int min_voids;

	std::vector<Pursuer> pursuers;

	SceneFlocking();
	~SceneFlocking();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};

