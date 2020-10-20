#include "SceneFlocking.h"
#include "Flocking.h"
#include "Flee.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	min_voids = 20;

		Agent *agent = new Agent();

		agent->setBehavior(new Seek);
		agent->setPosition(Vector2D(640, 360));
		agent->setTarget(Vector2D(640, 360));
		agent->loadSpriteTexture("../res/soldier.png", 4);
		agents.push_back(agent);
		target = Vector2D(640, 360);

		//pursuers = std::vector<Pursuer>(min_voids);
		obstacles = new Obstacle[max_obstacles];
		for (int p = 0; p < max_obstacles; p++)
		{
			obstacles[p].SetStats(50 + rand() % 50, Vector2D(rand() % 1000, 50 + rand() % 700));
		}

		for (int p = 0; p < min_voids; p++) 
		{
			pursuers.push_back(Pursuer(p, &pursuers));

			pursuers[p].rayManager->obstacles = obstacles;
			pursuers[p].setBehavior(new Flocking);
			pursuers[p].setPosition(Vector2D(20*p, 30*p));
			pursuers[p].loadSpriteTexture("../res/zombie1.png", 8);
			pursuers[p].setTarget(agent);
		}
}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}

	for (int p = 0; p < min_voids; p++)
	{
		pursuers[p].update(dtime, event);
	}
	agents[0]->update(dtime, event);
}

void SceneFlocking::draw()
{

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();

	for (int p = 0; p < min_voids; p++)
	{
		pursuers[p].draw();
	}

	for (int p = 0; p < max_obstacles; p++)
	{
		obstacles[p].draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}