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
	void SetCenter();
	void SetFontSize(int size) { TTF_SetFontSize(mFont, size); }
	void SetStartPoint(SDL_FPoint point) { mStartPoint = point; }
	void SetColor(SDL_Color color) { mFontColor = color; }
private:
	GameState* mGameState;
	TTF_Font* mFont;

	SDL_FRect mTextPos;
	SDL_FPoint mStartPoint = { 25, 35 };
	SDL_Color mFontColor = { 255, 255, 255 };
	const char* mFontPath = "assets/font/font.ttf";
	const int mFontSize = 40;
};

#include "gamestate.h"