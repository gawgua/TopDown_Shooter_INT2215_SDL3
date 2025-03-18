#include "map.h"

Map::Map(GameState* gameState)
{
	mGameState = gameState;
	mBgTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mBgTexturePath);
	mBgRenderMask = { (float)mBgTexture->w / 2, (float)mBgTexture->h / 2, 900, 900 };
}

void Map::Update()
{
	mBgRenderMask.x -= mGameState->movedX;
	mBgRenderMask.y -= mGameState->movedY;
}

void Map::Render()
{
	SDL_RenderTexture(mGameState->game->getRenderer(), mBgTexture, &mBgRenderMask, &mBgTexRect);
}