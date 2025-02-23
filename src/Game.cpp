#include "game.h"

Game::Game()
{
	mWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_TARGETTEXTURE);
	mBgMusic = Mix_LoadWAV(mBgMusicPath);
	Mix_VolumeChunk(mBgMusic, BACKGROUND_MUSIC_VOL);
	mGameState = { this, nullptr, nullptr, nullptr, 0, 0,0, false, false};
	mScoreText = nullptr;
}

Game::~Game()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	Mix_FreeChunk(mBgMusic);
}

bool Game::Init()
{
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	int imgFlag = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlag) != imgFlag)
	{
		SDL_Log("Failed to initialize SDL_image: %s", IMG_GetError());
		return false;
	}

	if (TTF_Init())
	{
		SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
		return false;
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048))
	{
		SDL_Log("Failed to initialize SDL_mixer: %s", Mix_GetError());
		return false;
	}

	return true;
}

void Game::Quit()
{
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void Game::Run()
{
	//initialize game
	mGameState.score = 0;
	mGameState.isGameOver = false;
	mGameState.isUserExit = false;
	//initialize player, bullet, enemy, sound
	mGameState.player = new Player(&mGameState);
	mGameState.enemies = new LinkedList<Enemy>();
	mGameState.bullets = new LinkedList<Bullet>();
	mScoreText = new ScoreText(&mGameState, mRenderer);
	Mix_FadeInChannel(-1, mBgMusic, -1, 2000); //to not suddenly start the music
	mEnemySpawnTimer = SDL_AddTimer(ENEMY_SPAWN_INTERVAL, Enemy::Spawn, &mGameState); //spawn enemy at interval

	while (!mGameState.isGameOver && !mGameState.isUserExit)
	{
		ProcessInput();
		UpdateGame();
		RenderScreen();

		SDL_Delay(1000 / TARGET_FPS);
	}

	//clear game before next game
	Mix_FadeOutChannel(-1, 500);
	//clear all array of player, bullet, enemy
	delete mGameState.enemies;
	delete mGameState.bullets;
	delete mGameState.player;
	delete mScoreText;
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mGameState.isUserExit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//mGameState.score++;
			mGameState.player->shoot();
			break;
		case SDL_MOUSEMOTION:
			mGameState.mouseX = event.motion.x;
			mGameState.mouseY = event.motion.y;
			break;
		}
	}
}

//idk what to do here
void Game::UpdateGame()
{
	mGameState.player->Update();
	if (!mGameState.player->isAlive())
		mGameState.isGameOver = true;

	if (mGameState.isGameOver)
		SDL_RemoveTimer(mEnemySpawnTimer);

	//update bullet
	LinkedList<Bullet>::Node* bulletNode = mGameState.bullets->head();
	while (bulletNode)
	{
		LinkedList<Bullet>::Node* next = bulletNode->next;
		
		if (!bulletNode->data.isAlive())
			mGameState.bullets->erase(bulletNode);
		else
			bulletNode->data.Update();

		bulletNode = next;
	}

	//update enemy
	LinkedList<Enemy>::Node* enemyHead = mGameState.enemies->head();
	while (enemyHead)
	{
		LinkedList<Enemy>::Node* next = enemyHead->next;
		
		if (!enemyHead->data.isAlive())
			mGameState.enemies->erase(enemyHead);
		else
			enemyHead->data.Update();
		
		enemyHead = next;
	}
}

void Game::RenderScreen()
{
	SDL_SetRenderDrawColor(mRenderer, mBgColor.r, mBgColor.g, mBgColor.b, mBgColor.a);
	SDL_RenderClear(mRenderer);

	//score text
	mScoreText->Render();

	//render player, bullet, enemy
	mGameState.player->Render();

	LinkedList<Bullet>::Node* bulletNode = mGameState.bullets->head();
	while (bulletNode)
	{
		bulletNode->data.Render();
		bulletNode = bulletNode->next;
	}

	LinkedList<Enemy>::Node* enemyNode = mGameState.enemies->head();
	while (enemyNode)
	{
		enemyNode->data.Render();
		enemyNode = enemyNode->next;
	}

	//to screen
	SDL_RenderPresent(mRenderer);
}