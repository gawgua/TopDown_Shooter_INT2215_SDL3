#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "gamestate.h"

class Tree
{
public:
	Tree() {};
	Tree(GameState* gameState, float x, float y);
	~Tree();

	void Update();
	void Render();

	SDL_FRect getHitbox() { return mTexRect; }
private:
	GameState* mGameState;
	SDL_Texture* mTexture;
	SDL_FRect mTexRect;

	const char* mTreeTexturePath = "assets/image/tree.png";
};