#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "constant.h"
#include "game.h"
#include "entity.h"

class Player : public Entity {
public:
	Player(GameState* gameState);
	~Player();
	void Render();
	void Update();

	void onCollision(EntityType type);
	void shoot();
private:
	void rotateToMouse();

	const char* mPlayerTexturePath = "assets/image/player.png";
	const float mTexSize = 100.0;
	const float mHitboxSize = 75.0;
};
