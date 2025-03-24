#include "map.h"

Map::Map(GameState* gameState)
{
	mGameState = gameState;
	mBgTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mBgTexturePath);
	mBgTexRect = { -(float)mBgTexture->w / 2, -(float)mBgTexture->h / 2, (float)mBgTexture->w, (float)mBgTexture->h };

	for (int i = 0; i < mTrees.size(); i++)
	{
		SDL_FPoint location = { SDL_rand(mBgTexture->w) + mBgTexRect.x, SDL_rand(mBgTexture->h) + mBgTexRect.y };
		mTrees[i] = new Tree(mGameState, location.x, location.y);
	}
}

Map::~Map()
{
	SDL_DestroyTexture(mBgTexture);

	for (Tree* tree : mTrees)
	{
		delete tree;
	}
}

void Map::Update()
{
	mBgTexRect.x += mGameState->movedX;
	mBgTexRect.y += mGameState->movedY;

	for (Tree* tree : mTrees)
	{
		tree->Update();
	}
}

void Map::Render()
{
	SDL_RenderTexture(mGameState->game->getRenderer(), mBgTexture, nullptr, &mBgTexRect);

	for (Tree* tree : mTrees)
	{
		tree->Render();
	}
}

bool Map::isInMap(SDL_FRect hitbox)
{
	return SDL_HasRectIntersectionFloat(&mBgTexRect, &hitbox);
}

Uint8 Map::getAllowDirection(SDL_FRect hitbox)
{
	enum Dir {
		UP = 0b0001, DOWN = 0b0010, LEFT = 0b0100, RIGHT = 0b1000
	};

	Uint8 allowDir = 0b0000;
	if (hitbox.y > mBgTexRect.y)
		allowDir |= UP;
	if (hitbox.y + hitbox.h < mBgTexRect.y + mBgTexRect.h)
		allowDir |= DOWN;
	if (hitbox.x > mBgTexRect.x)
		allowDir |= LEFT;
	if (hitbox.x + hitbox.w < mBgTexRect.x + mBgTexRect.w)
		allowDir |= RIGHT;

	return allowDir;
}