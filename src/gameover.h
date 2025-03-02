#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "constant.h"
#include "scoretext.h"
#include "button.h"

class GameOver
{
public:
	GameOver(GameState* gameState);
	~GameOver();

	void Run();
private:
	void Render();

	GameState* mGameState;
	SDL_Texture* mBgTexture;
	SDL_Texture* mPlayAgainButtonTexture;
	SDL_Texture* mExitButtonTexture;
	Button* mPlayAgainButton;
	Button* mExitButton;
	ScoreText* mScoreText;
	bool mStartPlay = false;

	const char* mBgTexturePath = "assets/image/gameover.png";
	const char* mPlayAgainButtonTexturePath = "assets/image/play_again_button_hover.png";
	const char* mExitButtonTexturePath = "assets/image/exit_button2_hover.png";
};