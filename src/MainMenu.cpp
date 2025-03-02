#include "mainmenu.h"

MainMenu::MainMenu(GameState* gameState)
{
	mGameState = gameState;
	mBgTexture = IMG_LoadTexture(gameState->game->getRenderer(), mBgTexturePath);
	mPlayButtonTexture = IMG_LoadTexture(gameState->game->getRenderer(), mPlayButtonTexturePath);
	mExitButtonTexture = IMG_LoadTexture(gameState->game->getRenderer(), mExitButtonTexturePath);
	mTutorialTexture = IMG_LoadTexture(gameState->game->getRenderer(), mTutorialTexturePath);
	SDL_SetTextureAlphaMod(mTutorialTexture, 0);
	mPlayButton = new Button(gameState->game->getRenderer(), mPlayButtonTexture, 157, 733, 199, 116, [this]() { mStartPlay = true; });
	mExitButton = new Button(gameState->game->getRenderer(), mExitButtonTexture, 394, 733, 201, 117, [this]() { mGameState->game->userExit(); });
}

MainMenu::~MainMenu()
{
	SDL_DestroyTexture(mBgTexture);
	SDL_DestroyTexture(mTutorialTexture);
	//button destructor will destroy its texture
	delete mPlayButton;
	delete mExitButton;
}

void MainMenu::Run()
{
	SDL_Event e;
	while (!mGameState->game->isUserWantExit() && !mStartPlay)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_EVENT_QUIT:
				mGameState->game->userExit();
				break;
			case SDL_EVENT_MOUSE_MOTION:
				mPlayButton->IsHover(e.button.x, e.button.y);
				mExitButton->IsHover(e.button.x, e.button.y);
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					mPlayButton->IsClicked(e.button.x, e.button.y);
					mExitButton->IsClicked(e.button.x, e.button.y);
				}
				break;
			}
		}
		Render();

		SDL_Delay(1000 / TARGET_FPS);
	}
	
	if (mStartPlay)
	{
		//fade in tutorial screen
		Uint8 alpha = 0;
		while (alpha < 255)
		{
			SDL_SetTextureAlphaMod(mTutorialTexture, ++alpha);
			SDL_RenderTexture(mGameState->game->getRenderer(), mTutorialTexture, NULL, NULL);
			SDL_RenderPresent(mGameState->game->getRenderer());

			SDL_Delay(10);
		}

		SDL_Delay(2000);
	}
}

void MainMenu::Render()
{
	SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(mGameState->game->getRenderer());
	SDL_RenderTexture(mGameState->game->getRenderer(), mBgTexture, NULL, NULL);
	mPlayButton->Render();
	mExitButton->Render();
	SDL_RenderPresent(mGameState->game->getRenderer());
}