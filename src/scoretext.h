#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct GameState;

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
	const int mFontSize = 70;
	const SDL_Color mFontColor = { 255, 255, 255 };
};

#include "gamestate.h"