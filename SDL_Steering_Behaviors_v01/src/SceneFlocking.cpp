#include "SceneFlocking.h"
#include "Flocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	min_voids = 20;

	for (int f = 0; f < min_voids; f++) {
		Agent *agent = new Agent;

		agent->setBehavior(new Flocking);
		agent->setPosition(Vector2D(640, 360));
		agent->setTarget(Vector2D(640, 360));
		agent->loadSpriteTexture("../res/soldier.png", 4);
		target = Vector2D(640, 360);

		agents.push_back(agent);
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
			for (int i = 0; i < (int)agents.size(); i++)
			{
				agents[i]->setTarget(target);
			}
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}
}

void SceneFlocking::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}