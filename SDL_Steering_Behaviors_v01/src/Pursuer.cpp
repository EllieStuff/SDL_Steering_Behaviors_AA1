#include "Pursuer.h"

using namespace std;

Pursuer::Pursuer() {}

Pursuer::Pursuer(int _id, std::vector<Pursuer>* vec) {

	sprite_texture = 0;
	position.x = 100;
	position.y = 100;
	target.x = 1000;
	target.y = 100;
	velocity.x = 0;
	velocity.y = 0;
	speed = 0.5f;
	max_force = 5.0f;
	max_velocity = 200.0f;
	mass = 0.001f;
	orientation = 0.0f;
	sprite_num_frames = 0.0f;
	sprite_w = 0.0f;
	sprite_h = 0.0f;
	draw_sprite = false;

	//steering_behaviour = 0;

	id = _id; // Posición en el vector
	bros = vec;

}

Pursuer::~Pursuer()
{
	/*if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);*/
}

void Pursuer::setBehavior(SteeringBehavior_2 *behavior)
{
	steering_behaviour = behavior;
}

Vector2D Pursuer::getPosition()
{
	return position;
}

Vector2D Pursuer::getTarget()
{
	return target;
}

Vector2D Pursuer::getVelocity()
{
	return velocity;
}

float Pursuer::getMaxVelocity()
{
	return max_velocity;
}

float Pursuer::getMaxForce() {
	return max_force;
}

float Pursuer::getMass() {
	return mass;
}

void Pursuer::setPosition(Vector2D _position)
{
	position = _position;
}

void Pursuer::setTarget(Vector2D _target)
{
	target = _target;
}

void Pursuer::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Pursuer::update(float dtime, SDL_Event *event)
{
	//cout << "Pursuer update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Apply the steering behavior
	//steering_behaviour->applySteeringForce(this, dtime);
	steering_behaviour->Separation(id, *bros);
	//steering_behaviour->Cohesion(id, *bros);
	//steering_behaviour->Alignment(id, *bros);
	steering_behaviour->FlockingForce(id, *bros, dtime);

	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Pursuer::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;

		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;

		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation + 90, &center, SDL_FLIP_NONE);
	}
	else
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x + 15 * cos(orientation*DEG2RAD)), (int)(position.y + 15 * sin(orientation*DEG2RAD)));
	}
}

bool Pursuer::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;

}
