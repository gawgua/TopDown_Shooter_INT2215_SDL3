#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "gamestate.h"

class Map {
public:
	Map() {};
	Map(GameState* gameState);
	~Map();

	void Update();
	void Render();

	bool isInMap(SDL_FRect hitbox);
	Uint8 getAllowDirection(SDL_FRect hitbox);
private:
	GameState* mGameState;
	SDL_Texture* mBgTexture;
	SDL_FRect mBgTexRect;

	const char* mBgTexturePath = "assets/image/map.png";
};