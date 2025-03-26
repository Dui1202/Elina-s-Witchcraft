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

void ResourceManager::loadSFX(std::vector<std::string> p_paths) {
	Mix_Chunk* effect = NULL;
	for (std::string& path : p_paths) {
		effect = Mix_LoadWAV(path.c_str());
		if (effect == NULL) {
			std::cout << "Failed to load SFX: " << path << "! Error: " << Mix_GetError() << std::endl;
			continue;
		}
		soundEffects.insert(std::make_pair(path, effect));
	}
}

void ResourceManager::loadMusic(std::vector<std::string> p_paths) {
	Mix_Music* music = NULL;
	for (std::string& path : p_paths) {
		music = Mix_LoadMUS(path.c_str());
		if (music == NULL) {
			std::cout << "Failed to load Music: " << path << "! Error: " << Mix_GetError() << std::endl;
			continue;
		}
		musics.insert(std::make_pair(path, music));
	}
}

SDL_Texture* ResourceManager::getTexture(std::string& p_path) {
	return textures[p_path];
}

Mix_Chunk* ResourceManager::getSFX(std::string& p_path) {
	return soundEffects[p_path];
}

Mix_Music* ResourceManager::getMusic(std::string& p_path) {
	return musics[p_path];
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

void ResourceManager::clearMusic() {
	for (auto& pair : musics) {
		if (pair.second) {
			Mix_FreeMusic(pair.second);
		}
	}
	musics.clear();
	std::cout << "All musics cleared!" << std::endl;
}

void ResourceManager::clearSFX() {
	for (auto& pair : soundEffects) {
		if (pair.second) {
			Mix_FreeChunk(pair.second);
		}
	}
	soundEffects.clear();
	std::cout << "All SFXs cleared!" << std::endl;
}

void ResourceManager::clear() {
	clearTexture();
	clearMusic();
	clearSFX();
}