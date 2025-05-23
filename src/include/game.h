#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "constant.h"
#include "gamestate.h"
#include "audiomanager.h"
class UI;
#include "ui.h"
class Map;
#include "map.h"

class Game {
public:
	Game();
	~Game();
	static bool Init();
	void Run();
	static void Quit();

	SDL_Window* getWindow() const { return mWindow; }
	SDL_Renderer* getRenderer() const { return mRenderer; }
	AudioManager* getAudioManager() const { return mAudioManager; }
	int getScore() const { return mGameState.score; }
	Map* getMap() { return mMap; }
	GameState* getGameState() { return &mGameState; }
	bool isUserWantExit() const { return mGameState.isUserExit; }
	void userExit() { mGameState.isUserExit = true; }
private:
	void ProcessInput();
	void UpdateGame();
	void RenderScreen();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	GameState mGameState;
	AudioManager* mAudioManager;
	SDL_Texture* mBgTexture;
	UI* mUI;
	Map* mMap;

	const SDL_Color mBgColor = { 123, 201, 24 };
	const SDL_FRect mBgRenderRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	const char* mBgTexturePath = "assets/image/bg.png";
};