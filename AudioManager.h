#pragma once
#include "SDL_mixer.h"
#include <vector>
#include "Enums.h"

class AudioManager {
public:
	AudioManager();
	void setSounds(std::vector<Mix_Music*>* p_musics, std::vector<Mix_Chunk*>* p_sfx);
	void start();
	void playButtonSFX();
	void playFireBallSFX();
	void playSnowBallSFX();
	void playWindStormSFX();
	void playLevelUpSFX();
	void setMusicVolume(int p_volume);
private:
	std::vector<Mix_Music*>* musics;
	std::vector<Mix_Chunk*>* SFXs;
};