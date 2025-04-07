#include "game.h"

#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

Game::Game()
{
#ifdef TOPDOWN_DEBUG
	mWindow = SDL_CreateWindow(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED);
#else
	mWindow = SDL_CreateWindow(TITLE, NULL, NULL, SDL_WINDOW_FULLSCREEN);
#endif // TOPDOWN_DEBUG
	mRenderer = SDL_CreateRenderer(mWindow, NULL);
	SDL_SetRenderLogicalPresentation(mRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
	mBgTexture = IMG_LoadTexture(mRenderer, mBgTexturePath);
	mGameState = { this, nullptr, nullptr, nullptr, 0, 0, 0.0, 0.0, 0, 0, false, false, false };
	mUI = nullptr;
	mMap = nullptr;
	mAudioManager = new AudioManager();
}

Game::~Game()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_DestroyTexture(mBgTexture);

	delete mAudioManager;
}

bool Game::Init()
{
	SDL_srand(SDL_GetPerformanceCounter());

	if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	if (!TTF_Init())
	{
		SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
		return false;
	}

	Mix_OpenAudio(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

	return true;
}

void Game::Quit()
{
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
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
	mUI = new UI(&mGameState);
	mMap = new Map(&mGameState);
	mAudioManager->playMusic();
	// filter out repeat key event so when player hold key the event queue will not be spammed
	SDL_SetEventFilter([](void* userdata, SDL_Event* event) -> bool {
		if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP)
			return !event->key.repeat;
		return true;
	}, nullptr);

	while (!mGameState.isGameOver && !mGameState.isUserExit)
	{
		double before = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();

		ProcessInput();
		if (!mGameState.isPaused)
			UpdateGame();
		RenderScreen();

		SDL_Delay(1); // 1ms delay to prevent 90% GPU usage
		
		double after = (double)SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
		mGameState.deltaTime = after - before;
	}

	mAudioManager->toggleMusic();
	if (mGameState.isGameOver)
	{
		mAudioManager->playGameOver();
	}

	//clear all array of player, bullet, enemy
	delete mGameState.enemies;
	delete mGameState.bullets;
	delete mGameState.player;
	delete mUI;
	delete mMap;
}

static bool moveUp = false;
static bool moveDown = false;
static bool moveLeft = false;
static bool moveRight = false;
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			mGameState.isUserExit = true;
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			//mGameState.score++;
			mGameState.player->shoot();
			mAudioManager->playShoot();
			break;
		case SDL_EVENT_MOUSE_MOTION:
			mGameState.mouseX = event.motion.x;
			mGameState.mouseY = event.motion.y;
			break;
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
			switch (event.key.key)
			{
			case SDLK_ESCAPE:
#ifdef TOPDOWN_DEBUG
				if (mGameState.isPaused)
					SDL_Log("Game resumed");
				else
					SDL_Log("Game paused");
#endif // TOPDOWN_DEBUG
				if (event.key.down)
				{
					mAudioManager->playClick();
					mAudioManager->toggleMusic();
					mGameState.isPaused = !mGameState.isPaused;
				}
				break;
			case SDLK_W:
				moveUp = event.key.down;
				break;
			case SDLK_A:
				moveLeft = event.key.down;
				break;
			case SDLK_S:
				moveDown = event.key.down;
				break;
			case SDLK_D:
				moveRight = event.key.down;
				break;
			}
			break;
		}
	}
}

double enemySpawnDeltaTime = ENEMY_SPAWN_INTERVAL;
//idk what to do here
void Game::UpdateGame()
{
	//move player
	if (moveDown && (mMap->getAllowDirection(mGameState.player->getHitbox()) & 0b0010))
		mGameState.movedY += mGameState.deltaTime * -mGameState.player->getSpeed();
	if (moveUp && (mMap->getAllowDirection(mGameState.player->getHitbox()) & 0b0001))
		mGameState.movedY += mGameState.deltaTime * mGameState.player->getSpeed();
	if (moveRight && (mMap->getAllowDirection(mGameState.player->getHitbox()) & 0b1000))
		mGameState.movedX += mGameState.deltaTime * -mGameState.player->getSpeed();
	if (moveLeft && (mMap->getAllowDirection(mGameState.player->getHitbox()) & 0b0100))
		mGameState.movedX += mGameState.deltaTime * mGameState.player->getSpeed();

	enemySpawnDeltaTime -= mGameState.deltaTime;
	SDL_Log("enemy: %llf, delta: %llf", enemySpawnDeltaTime, mGameState.deltaTime);
	if (enemySpawnDeltaTime <= 0)
	{
		mGameState.enemies->push_back(new Enemy(&mGameState));
		enemySpawnDeltaTime = ENEMY_SPAWN_INTERVAL;
	}

	mGameState.player->Update();
	if (!mGameState.player->isAlive())
		mGameState.isGameOver = true;

	mMap->Update();

	//update bullet
	LinkedList<Bullet>::Node* bulletNode = mGameState.bullets->head();
	while (bulletNode)
	{
		LinkedList<Bullet>::Node* next = bulletNode->next;
		
		if (!bulletNode->data->isAlive())
			mGameState.bullets->erase(bulletNode);
		else
			bulletNode->data->Update();

		bulletNode = next;
	}

	//update enemy
	LinkedList<Enemy>::Node* enemyHead = mGameState.enemies->head();
	while (enemyHead)
	{
		LinkedList<Enemy>::Node* next = enemyHead->next;
		
		if (!enemyHead->data->isAlive())
			mGameState.enemies->erase(enemyHead);
		else
			enemyHead->data->Update();
		
		enemyHead = next;
	}

	mGameState.movedX = 0.0;
	mGameState.movedY = 0.0;
}

void Game::RenderScreen()
{
	SDL_SetRenderDrawColor(mRenderer, mBgColor.r, mBgColor.g, mBgColor.b, mBgColor.a);
	SDL_RenderClear(mRenderer);

	mMap->Render();

	//render player, bullet, enemy
	mGameState.player->Render();

	LinkedList<Bullet>::Node* bulletNode = mGameState.bullets->head();
	while (bulletNode)
	{
		bulletNode->data->Render();
		bulletNode = bulletNode->next;
	}

	LinkedList<Enemy>::Node* enemyNode = mGameState.enemies->head();
	while (enemyNode)
	{
		enemyNode->data->Render();
		enemyNode = enemyNode->next;
	}

	// background
	SDL_RenderTexture(mRenderer, mBgTexture, nullptr, &mBgRenderRect);

	//score text
	mUI->Render();

	//to screen
	SDL_RenderPresent(mRenderer);
}