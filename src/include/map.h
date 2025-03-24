#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>

class Tree;
#include "tree.h"
#include "gamestate.h"

const int mTreeCount = 25;
class Map {
public:
	Map() {};
	Map(GameState* gameState);
	~Map();

	void Update();
	void Render();

	std::array<Tree*, mTreeCount>* getTrees() { return &mTrees; }
	bool isInMap(SDL_FRect hitbox);
	Uint8 getAllowDirection(SDL_FRect hitbox);
private:
	GameState* mGameState;
	SDL_Texture* mBgTexture;
	SDL_FRect mBgTexRect;
	std::array<Tree*, mTreeCount> mTrees;

	const char* mBgTexturePath = "assets/image/map.png";
};