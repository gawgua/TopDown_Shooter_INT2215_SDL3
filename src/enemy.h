#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "gamestate.h"
#include "entity.h"

class Enemy : public Entity {
public:
	Enemy(GameState* gameState);
	~Enemy();
	void Update();	
	void Render();

	static Uint32 Spawn(void* pGameState, SDL_TimerID id, Uint32 interval); // SDL_AddTimer callback need void*

	void onCollision(EntityType type);
private:
	static SDL_Point getRandSpawnPos();
	void move();
	void rotateToPlayer();

	const char* mEnemyTexturePath = "assets/image/enemy.png";
	const float mTexSize = 100.0;
	const float mHitboxSize = 75.0;
	const float mSpeed = 2.5;
};