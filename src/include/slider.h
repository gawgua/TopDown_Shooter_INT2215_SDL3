#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class Slider
{
public:
	Slider(SDL_Renderer* renderer, SDL_Color color, int x, int y, int w, int h, int initVal);
	~Slider();

	void Render();

	bool IsClicked(float x, float y);
	int GetValue() { return mValue; }
	void SetValue(int value) { mValue = value; }
private:
	SDL_FRect mBackRect;
	SDL_FRect mFrontRect;
	SDL_Color mColor;
	SDL_Renderer* mRenderer;
	TTF_Font* mFont;
	int mValue;

	const char* mFontPath = "assets/font/font.ttf";
};