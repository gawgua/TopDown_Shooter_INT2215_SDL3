#include "game.h"
#include <string>

int main(int argc, char* argv[]) {
	Game::Init();
	//Game menu, game over screen
	Game* game = new Game();

	//show menu
	SDL_MessageBoxButtonData buttons[] = {
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 200, "Exit" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 100, "Play" },
	};
	SDL_MessageBoxData gameStartMessageBoxData = {
		SDL_MESSAGEBOX_INFORMATION,
		nullptr,
		"Hello",
		"Welcome to %s",
		SDL_arraysize(buttons),
		buttons,
		NULL
	};
	int buttonid;
	SDL_ShowMessageBox(&gameStartMessageBoxData, &buttonid);
	if (buttonid == 200)
	{
		game->userExit();
	}

	while (!game->isUserWantExit())
	{
		game->Run();
		//show game over screen
		//if (button !play again) and (exit not been set be4); exit = true;

		SDL_MessageBoxButtonData buttons[] = {
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 200, "Exit" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 100, "Play Again" },
		};
		std::string scoreText = "Your score is: " + std::to_string(game->getScore());
		SDL_MessageBoxData gameOverMessageBoxData = {
			SDL_MESSAGEBOX_INFORMATION,
			game->getWindow(),
			"Game Over",
			scoreText.c_str(),
			SDL_arraysize(buttons),
			buttons,
			NULL
		};
		int buttonid;
		if (!game->isUserWantExit())
		{
			SDL_ShowMessageBox(&gameOverMessageBoxData, &buttonid);
			if (buttonid == 200)
			{
				game->userExit();
			}
		}
	}

	//clean up
	Game::Quit();
	delete game;
	return 0;
}