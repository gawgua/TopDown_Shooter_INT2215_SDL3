#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <functional>

class Button
{
public:
	Button() {};
	Button(SDL_Renderer* renderer, SDL_Texture* tex, float x, float y, float w, float h, std::function<void()> func);
	~Button();

	void Render();
	bool IsClicked(float x, float y);
	bool IsHover(float x, float y);

	static void convertMousePosToRender(SDL_Renderer* renderer, float x, float y, float* rx, float* ry);
private:
	SDL_Texture* mTexture;
	SDL_FRect mRect;
	SDL_Renderer* mRenderer;
	std::function<void(void)> mFunc;

	bool mIsHover;
};