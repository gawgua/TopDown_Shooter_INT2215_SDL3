#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct GameState;

class ScoreText
{
public:
	ScoreText(GameState* gameState);
	~ScoreText();
	void Render();
private:
	GameState* mGameState;
	TTF_Font* mFont;

	const char* mFontPath = "assets/font/font.ttf";
	const int mFontSize = 40;
	const SDL_Color mFontColor = { 255, 255, 255 };
	const SDL_FPoint mStartPoint = { 25, 35 };
};

#include "gamestate.h"