#include "AudioManager.h"
#include <SDL_mixer.h>
#include "Enums.h"

AudioManager::AudioManager(){
}

void AudioManager::setSounds(std::vector<Mix_Music*>* p_musics, std::vector<Mix_Chunk*>* p_sfx) {
	musics = p_musics;
	SFXs = p_sfx;
}

void AudioManager::start() {
	Mix_PlayMusic((*musics)[GAMEPLAY_MUSIC], -1);
}

void AudioManager::playButtonSFX() {
	Mix_PlayChannel(-1, (*SFXs)[BUTTON_SFX], 0);
}

void AudioManager::playFireBallSFX() {
	Mix_PlayChannel(-1, (*SFXs)[FIREBALL_SFX], 0);
}

void AudioManager::playSnowBallSFX() {
	Mix_PlayChannel(-1, (*SFXs)[SNOWBALL_SFX], 0);
}

void AudioManager::playWindStormSFX() {
	Mix_PlayChannel(-1, (*SFXs)[WINDSTORM_SFX], 0);
}

void AudioManager::playLevelUpSFX() {
	Mix_PlayChannel(-1, (*SFXs)[LEVELUP_SFX], 0);
}

void AudioManager::setMusicVolume(int p_volume) {
	Mix_VolumeMusic(p_volume);
}
