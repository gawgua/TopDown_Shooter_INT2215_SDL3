#pragma once
#include <SDL3/SDL.h>

#include "scoretext.h"
#include "gamestate.h"

class UI
{
public:
	UI() {};
	UI(GameState* gameState);
	~UI();

	void Render();
private:
	SDL_Texture* getTextureFromHP();

	GameState* mGameState;
	SDL_Texture* mUITexture;
	SDL_Texture* mPauseTexture;
	SDL_Texture* mHpTexture[6];
	ScoreText* mScoreText;

	const char* mUITexturePath = "assets/image/ui.png";
	const char* mPauseTexturePath = "assets/image/paused.png";

	const char* mHp0TexturePath = "assets/image/hp0.png";
	const char* mHp1TexturePath = "assets/image/hp1.png";
	const char* mHp2TexturePath = "assets/image/hp2.png";
	const char* mHp3TexturePath = "assets/image/hp3.png";
	const char* mHp4TexturePath = "assets/image/hp4.png";
	const char* mHp5TexturePath = "assets/image/hp5.png";
	const SDL_FRect mHpTexRect = { 173, 29, 233, 40 };
};