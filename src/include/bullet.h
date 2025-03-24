#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "gamestate.h"
#include "entity.h"

class Bullet : public Entity {
public:
	Bullet(GameState* gameState);
	void Update();

	void onCollision(Entity* other);
private:
	void move();

	const char* mBulletTexturePath = "assets/image/bullet.png";
	const float mTexSize = 40.0;
	const float mHitboxSize = 35.0;
	const float mSpeed = 280.0;
};
