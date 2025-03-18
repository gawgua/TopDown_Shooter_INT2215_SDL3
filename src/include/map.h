#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "gamestate.h"

class Map {
public:
	Map() {};
	Map(GameState* gameState);
	~Map() {};

	void Update();
	void Render();
private:
	GameState* mGameState;
	SDL_Texture* mBgTexture;
	SDL_FRect mBgRenderMask;

	const char* mBgTexturePath = "assets/image/map.png";
	const SDL_FRect mBgTexRect = { 0, 0, 900, 900 };
};