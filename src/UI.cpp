#include "ui.h"

UI::UI(GameState* gameState)
{
	mGameState = gameState;
	mScoreText = new ScoreText(gameState);
	mUITexture = IMG_LoadTexture(mGameState->game->getRenderer(), mUITexturePath);
	mPauseTexture = IMG_LoadTexture(mGameState->game->getRenderer(), mPauseTexturePath);
	mHpTexture[0] = IMG_LoadTexture(mGameState->game->getRenderer(), mHp0TexturePath);
	mHpTexture[1] = IMG_LoadTexture(mGameState->game->getRenderer(), mHp1TexturePath);
	mHpTexture[2] = IMG_LoadTexture(mGameState->game->getRenderer(), mHp2TexturePath);
	mHpTexture[3] = IMG_LoadTexture(mGameState->game->getRenderer(), mHp3TexturePath);
	mHpTexture[4] = IMG_LoadTexture(mGameState->game->getRenderer(), mHp4TexturePath);
	mHpTexture[5] = IMG_LoadTexture(mGameState->game->getRenderer(), mHp5TexturePath);
}

UI::~UI()
{
	SDL_DestroyTexture(mUITexture);

	for (int i = 0; i < 6; i++)
	{
		SDL_DestroyTexture(mHpTexture[i]);
	}

	delete mScoreText;
}

void UI::Render()
{
	SDL_RenderTexture(mGameState->game->getRenderer(), mUITexture, NULL, NULL);
	mScoreText->Render();
	SDL_RenderTexture(mGameState->game->getRenderer(), getTextureFromHP(), NULL, &mHpTexRect);

	if (mGameState->isPaused)
	{
		SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 0, 0, 0, 190);
		SDL_RenderFillRect(mGameState->game->getRenderer(), NULL);
		SDL_RenderTexture(mGameState->game->getRenderer(), mPauseTexture, NULL, NULL);
	}
}

SDL_Texture* UI::getTextureFromHP()
{
	/*switch (mGameState->player->getHp())
	{
	case 0:
		return mHpTexture[0];
		break;
	case 1:
		return mHpTexture[1];
		break;
	case 2:
		return mHpTexture[2];
		break;
	case 3:
		return mHpTexture[3];
		break;
	case 4:
		return mHpTexture[4];
		break;
	case 5:
		return mHpTexture[5];
		break;
	default:
		return mHpTexture[0];
		break;
	}*/
	return mHpTexture[mGameState->player->getHp()];
}