#include "gameover.h"

GameOver::GameOver(GameState* gameState)
{
	mGameState = gameState;
	mBgTexture = IMG_LoadTexture(gameState->game->getRenderer(), mBgTexturePath);
	mPlayAgainButtonTexture = IMG_LoadTexture(gameState->game->getRenderer(), mPlayAgainButtonTexturePath);
	mExitButtonTexture = IMG_LoadTexture(gameState->game->getRenderer(), mExitButtonTexturePath);
	mPlayAgainButton = new Button(gameState->game->getRenderer(), mPlayAgainButtonTexture, 148, 680, 274, 76, [this]() { mStartPlay = true; });
	mExitButton = new Button(gameState->game->getRenderer(), mExitButtonTexture, 501, 680, 274, 76, [this]() { mGameState->game->userExit(); });
	mScoreText = new ScoreText(gameState);
	mScoreText->SetFontSize(150);
	mScoreText->SetColor({ 97, 161, 93 });
}

GameOver::~GameOver()
{
	SDL_DestroyTexture(mBgTexture);
	SDL_DestroyTexture(mPlayAgainButtonTexture);
	SDL_DestroyTexture(mExitButtonTexture);
	//button destructor will destroy its texture
	delete mPlayAgainButton;
	delete mExitButton;
	delete mScoreText;
}

void GameOver::Run()
{
	SDL_Event e;
	while (!mGameState->isUserExit && !mStartPlay)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_EVENT_QUIT:
				mGameState->game->userExit();
				break;
			case SDL_EVENT_MOUSE_MOTION:
				mPlayAgainButton->IsHover(e.button.x, e.button.y);
				mExitButton->IsHover(e.button.x, e.button.y);
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					if (mPlayAgainButton->IsClicked(e.button.x, e.button.y) 
					|| mExitButton->IsClicked(e.button.x, e.button.y))
						mGameState->game->getAudioManager()->playClick();
				}
				break;
			}
		}
		Render();
	}

	mStartPlay = false;
}

void GameOver::Render()
{
	SDL_SetRenderDrawColor(mGameState->game->getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(mGameState->game->getRenderer());
	SDL_RenderTexture(mGameState->game->getRenderer(), mBgTexture, NULL, NULL);
	mScoreText->Render();
	mScoreText->SetCenter();
	mPlayAgainButton->Render();
	mExitButton->Render();
	SDL_RenderPresent(mGameState->game->getRenderer());
}