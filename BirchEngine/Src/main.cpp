#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

Game *game = nullptr;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();
	return 0;
}