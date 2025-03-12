#include "scoretext.h"

ScoreText::ScoreText(GameState* gameState)
{
	mGameState = gameState;
	mFont = TTF_OpenFont(mFontPath, mFontSize);
}

ScoreText::~ScoreText()
{
	TTF_CloseFont(mFont);
}

void ScoreText::Render()
{
	std::string score = std::to_string(mGameState->score);
	SDL_Surface* surface = TTF_RenderText_Solid(mFont, score.c_str(), 0, mFontColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mGameState->game->getRenderer(), surface);
	mTextPos = { mStartPoint.x, mStartPoint.y, (float)surface->w, (float)surface->h };

	SDL_RenderTexture(mGameState->game->getRenderer(), texture, nullptr, &mTextPos);
	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);
}

void ScoreText::SetCenter()
{
	mStartPoint.x = (SCREEN_WIDTH - mTextPos.w) / 2;
	mStartPoint.y = (SCREEN_HEIGHT - mTextPos.h) / 2;
}
