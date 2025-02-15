#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include "ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer* p_renderer)
	: renderer(p_renderer){}

void ResourceManager::loadTexture(std::vector<std::string> p_paths) {
	SDL_Texture* tex = NULL;
	for (std::string& path : p_paths) {
		tex = IMG_LoadTexture(renderer, path.c_str());
		if (tex == NULL) {
			std::cout << "Failed to load texture: "<< path <<"! Error: " << SDL_GetError() << std::endl;
			continue;
		}
		textures.insert(std::make_pair(path, tex));
	}
}

SDL_Texture* ResourceManager::getTexture(std::string& p_path) {
	return textures[p_path];
}

void ResourceManager::clearTexture() {
	for (auto& pair : textures) {
		if (pair.second) {
			SDL_DestroyTexture(pair.second);
		}
	}
	textures.clear();
	std::cout << "All textures cleared!" << std::endl;
}