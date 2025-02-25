#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "gamestate.h"
#include "entity.h"

class Player : public Entity {
public:
	Player(GameState* gameState);
	void Update();

	void onCollision(EntityType type);
	void shoot();
private:
	void rotateToMouse();

	const char* mPlayerTexturePath = "assets/image/player.png";
	const float mTexSize = 100.0;
	const float mHitboxSize = 75.0;
};
