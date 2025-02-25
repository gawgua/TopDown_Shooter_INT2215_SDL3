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
	SDL_Surface* surface = TTF_RenderText_Solid(mFont, score.c_str(), 0, mFontColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FRect textPos = { 15, 15, surface->w, surface->h };

	SDL_RenderTexture(mRenderer, texture, nullptr, &textPos);
	SDL_DestroySurface(surface);
	SDL_DestroyTexture(texture);
}

