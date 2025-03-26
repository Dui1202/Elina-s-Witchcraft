#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <vector>
#include <SDL_mixer.h>

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* p_renderer);
	void loadTexture(std::vector<std::string> p_path);
	void loadSFX(std::vector<std::string> p_path);
	void loadMusic(std::vector<std::string> p_path);
	SDL_Texture* getTexture(std::string& p_path);
	Mix_Chunk* getSFX(std::string& p_path);
	Mix_Music* getMusic(std::string& p_path);
	void clearTexture();
	void clearSFX();
	void clearMusic();
	void clear();
private:
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> textures;
	std::unordered_map<std::string, Mix_Chunk*> soundEffects;
	std::unordered_map<std::string, Mix_Music*> musics;
};