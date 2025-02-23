#include "scoretext.h"

ScoreText::ScoreText(GameState* gameState, SDL_Renderer* renderer)
{
	mRenderer = renderer;
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
	SDL_Surface* surface = TTF_RenderUTF8_Solid(mFont, score.c_str(), mFontColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_Rect textPos = { 15, 15, surface->w, surface->h };

	SDL_RenderCopy(mRenderer, texture, nullptr, &textPos);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

