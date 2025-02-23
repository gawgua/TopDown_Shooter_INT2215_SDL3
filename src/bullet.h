#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "constant.h"
#include "entity.h"
#include "game.h"

class Bullet : public Entity {
public:
	Bullet(GameState* gameState);
	~Bullet();
	void Render();
	void Update();

	void onCollision(EntityType type);
private:
	void move();

	const char* mBulletTexturePath = "assets/image/bullet.png";
	const float mTexSize = 30.0;
	const float mHitboxSize = 25.0;
	const float mSpeed = 5.0;
};
