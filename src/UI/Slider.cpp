#include "slider.h"

#include <string>

Slider::Slider(SDL_Renderer* renderer, SDL_Color color, int x, int y, int w, int h, int initVal = 100)
{
	mRenderer = renderer;
	mBackRect.x = x;
	mBackRect.y = y;
	mBackRect.w = w;
	mBackRect.h = h;
	mFrontRect.x = x;
	mFrontRect.y = y;
	mFrontRect.w = w;
	mFrontRect.h = h;
	mValue = initVal;
	mColor = color;
	mFont = TTF_OpenFont(mFontPath, 60);
}

Slider::~Slider()
{
	TTF_CloseFont(mFont);
}

void Slider::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, &mBackRect);
	SDL_SetRenderDrawColor(mRenderer, mColor.r, mColor.g, mColor.b, mColor.a);
	SDL_RenderFillRect(mRenderer, &mFrontRect);

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_Surface* surface = TTF_RenderText_Solid(mFont, std::to_string(mValue).c_str(), 0, {0, 0, 0});
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_DestroySurface(surface);
	float x = mFrontRect.x + mFrontRect.w - texture->w;
	if (x < mBackRect.x) x = mBackRect.x;
	SDL_FRect textRect = { x, mFrontRect.y + mFrontRect.h / 2 - texture->h / 2, (float)texture->w, (float)texture->h };
	SDL_RenderTexture(mRenderer, texture, NULL, &textRect);
}

bool Slider::IsClicked(float x, float y)
{
	float rx, ry;
	SDL_RenderCoordinatesFromWindow(mRenderer, x, y, &rx, &ry);

	if (rx >= mBackRect.x && rx <= mBackRect.x + mBackRect.w && ry >= mBackRect.y && ry <= mBackRect.y + mBackRect.h)
	{
		mValue = (rx - mBackRect.x) / (mBackRect.w) * 100;
		mFrontRect.w = (float)mValue / 100 * mBackRect.w;

		return true;
	}
	return false;
}