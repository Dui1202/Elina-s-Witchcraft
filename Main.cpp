#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "RenderWindow.hpp"
#include "Entity.h"
#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "ResourceManager.h"
#include "InputManager.h"

int main(int argc, char* agrs[]) {
	//Initialize SDL and IMG
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "Failed to init SDL! Error: " << SDL_GetError() << std::endl;
	}

	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "Failed to init IMG! Error: " << IMG_GetError() << std::endl;
	}

	if (TTF_Init() == -1) {
		std::cout << "Failed to init TTF! Error: " << TTF_GetError() << std::endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
	}
	Game newGame;
	newGame.start();
	newGame.update();
	newGame.clean();
	//Quit the program
	SDL_Quit();

	return 0;
}