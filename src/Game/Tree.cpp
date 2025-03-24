#include "tree.h"

Tree::Tree(GameState* gameState, float x, float y)
{
	mGameState = gameState;
	mTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mTreeTexturePath);
	if (!mTexture)
	{
		SDL_Log("Failed to load tree texture: %s", SDL_GetError());
	}
	mTexRect = { x, y, (float)mTexture->w, (float)mTexture->h };
}

Tree::~Tree()
{
	SDL_DestroyTexture(mTexture);
}

void Tree::Update()
{
	mTexRect.x += mGameState->movedX;
	mTexRect.y += mGameState->movedY;
}

void Tree::Render()
{
	SDL_RenderTexture(mGameState->game->getRenderer(), mTexture, nullptr, &mTexRect);
}