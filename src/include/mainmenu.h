#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "button.h"
#include "gamestate.h"

class MainMenu
{
public:
	MainMenu(GameState* gameState);
	~MainMenu();

	void Run();
private:
	void Render();

	GameState* mGameState;
	SDL_Texture* mBgTexture;
	SDL_Texture* mPlayButtonTexture;
	SDL_Texture* mExitButtonTexture;
	SDL_Texture* mTutorialTexture;
	Button* mPlayButton;
	Button* mExitButton;
	bool mStartPlay = false;

	const char* mBgTexturePath = "assets/image/mainmenu.png";
	const char* mPlayButtonTexturePath = "assets/image/play_button_hover.png";
	const char* mExitButtonTexturePath = "assets/image/exit_button1_hover.png";
	const char* mTutorialTexturePath = "assets/image/tutorial.png";
};