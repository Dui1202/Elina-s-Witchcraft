#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <vector>

class ResourceManager {
public:
	ResourceManager(SDL_Renderer* p_renderer);
	void loadTexture(std::vector<std::string> p_path);
	SDL_Texture* getTexture(std::string& p_path);
	void clearTexture();
private:
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> textures;
};