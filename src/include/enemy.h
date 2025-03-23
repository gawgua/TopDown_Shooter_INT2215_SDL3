#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "gamestate.h"
#include "entity.h"
class Map;
#include "map.h"

class Enemy : public Entity {
public:
	Enemy(GameState* gameState);
	void Update();	

	void onCollision(Entity* type);
private:
	static SDL_Point getRandSpawnPos(Map* map);
	void move();
	void rotateToPlayer();
	float speedBasedOnScore();

	const char* mEnemyTexturePath = "assets/image/enemy.png";
	const float mTexSize = 100.0;
	const float mHitboxSize = 90.0;
	float mSpeed = 25;
};