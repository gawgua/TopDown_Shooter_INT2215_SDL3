#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <time.h>

#include "constant.h"
#include "gamestate.h"
#include "scoretext.h"

class Game {
public:
	Game();
	~Game();
	static bool Init();
	void Run();
	static void Quit();

	SDL_Window* getWindow() const { return mWindow; }
	SDL_Renderer* getRenderer() const { return mRenderer; }

	bool isUserWantExit() const { return mGameState.isUserExit; }
	void userExit() { mGameState.isUserExit = true; }
private:
	void ProcessInput();
	void UpdateGame();
	void RenderScreen();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	GameState mGameState;
	SDL_TimerID mEnemySpawnTimer;
	Mix_Chunk* mBgMusic;
	ScoreText* mScoreText;

	const SDL_Color mBgColor = { 123, 201, 24 };
	const char* mBgMusicPath = "assets/sound/bg_music.wav";
};