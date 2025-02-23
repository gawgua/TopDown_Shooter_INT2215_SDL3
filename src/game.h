#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <time.h>

#include "constant.h"

//forward declaration to avoid circular dependency
template <class T>
class LinkedList;
class Game;
class ScoreText;
class Player;
class Enemy;
class Bullet;

struct GameState {
	Game* game;
	Player* player;
	LinkedList<Enemy>* enemies;
	LinkedList<Bullet>* bullets;

	int mouseX, mouseY;
	unsigned int score;
	bool isGameOver;
	bool isUserExit;
};

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

#include "linkedlist.h"
#include "scoretext.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"