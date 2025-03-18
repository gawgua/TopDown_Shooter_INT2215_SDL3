#include "game.h"
#include "mainmenu.h"
#include "gameover.h"
#include <string>

int main(int argc, char* argv[]) {
	Game::Init();
	//Game menu, game over screen
	Game* game = new Game();
	MainMenu* mainMenu = new MainMenu(game->getGameState());
	GameOver* gameOver = new GameOver(game->getGameState());
	//show menu
	mainMenu->Run();
	delete mainMenu;

#ifdef TOPDOWN_DEBUG
	int gameCount = 0;
#endif // TOPDOWN_DEBUG

	while (!game->isUserWantExit())
	{
#ifdef TOPDOWN_DEBUG
		SDL_Log("#######    GAME ROUND %d   ########################", ++gameCount);
#endif // TOPDOWN_DEBUG
		game->Run();
		//show game over screen
		//if (button !play again) and (exit not been set be4); exit = true;
		gameOver->Run();
	}

	delete game;
	delete gameOver;
	//clean up
	Game::Quit();

	return 0;
}