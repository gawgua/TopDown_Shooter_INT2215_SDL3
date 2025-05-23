#include "button.h"

Button::Button(SDL_Renderer* renderer, SDL_Texture* tex, float x, float y, float w, float h, std::function<void(void)> func)
{
	mRenderer = renderer;
	mTexture = tex;
	mRect = { x, y, w, h };
	mIsHover = false;
	mFunc = func;
}

Button::~Button()
{
	SDL_DestroyTexture(mTexture);
}

void Button::Render()
{
	if (mIsHover)
		SDL_RenderTexture(mRenderer, mTexture, nullptr, &mRect);

	/*SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);
	SDL_RenderRect(mRenderer, &mRect);*/
}

bool Button::IsClicked(float x, float y)
{
	if (IsHover(x,y))
	{
		mFunc();
		return true;
	}

	return false;
}

bool Button::IsHover(float x, float y)
{
	float rx, ry;
	SDL_RenderCoordinatesFromWindow(mRenderer, x, y, &rx, &ry);

	mIsHover = (rx >= mRect.x && rx <= mRect.x + mRect.w && ry >= mRect.y && ry <= mRect.y + mRect.h);
	return mIsHover;
}
