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

	while (!game->isUserWantExit())
	{
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