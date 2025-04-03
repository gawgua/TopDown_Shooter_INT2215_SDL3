#pragma once

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void playMusic();
	void playShoot();
	void playHit();
	void playHurt();
	void playGameOver();
	void playClick();

	void toggleMusic();
	void setMusicVolume(int volume);
	void setSoundEffectVolume(int volume);
private:
	Mix_Music* mMusic;
	Mix_Chunk* mSfxShoot;
	Mix_Chunk* mSfxHit;
	Mix_Chunk* mSfxHurt;
	Mix_Chunk* mSfxGameOver;
	Mix_Chunk* mSfxClick;

	int mMusicVolume = 128; // Default volume (0-128)
	int mSoundEffectVolume = 128; 

	const char* mMusicPath = "assets/sound/music.mp3";
	const char* mSfxShootPath = "assets/sound/shoot.wav";
	const char* mSfxHitPath = "assets/sound/hit.wav";
	const char* mSfxHurtPath = "assets/sound/hurt.wav";
	const char* mSfxGameOverPath = "assets/sound/gameover.wav";
	const char* mSfxClickPath = "assets/sound/click.wav";
};