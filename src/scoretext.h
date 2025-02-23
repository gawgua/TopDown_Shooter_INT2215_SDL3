#pragma once
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

#include "game.h"

class ScoreText
{
public:
	ScoreText(GameState* gameState, SDL_Renderer* renderer);
	~ScoreText();
	void Render();
private:
	GameState* mGameState;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;

	const char* mFontPath = "assets/font/font.ttf";
	const int mFontSize = 50;
	const SDL_Color mFontColor = { 255, 255, 255 };
};