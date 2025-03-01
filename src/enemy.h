#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "gamestate.h"
#include "entity.h"

class Enemy : public Entity {
public:
	Enemy(GameState* gameState);
	void Update();	

	void onCollision(EntityType type);
private:
	static SDL_Point getRandSpawnPos();
	void move();
	void rotateToPlayer();
	float speedBasedOnScore();

	const char* mEnemyTexturePath = "assets/image/enemy.png";
	const float mTexSize = 100.0;
	const float mHitboxSize = 90.0;
	float mSpeed = 2.5;
};