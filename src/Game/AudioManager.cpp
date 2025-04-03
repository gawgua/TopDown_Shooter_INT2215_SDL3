#include "audiomanager.h"

AudioManager::AudioManager()
{
	mMusic = Mix_LoadMUS(mMusicPath);
	mSfxShoot = Mix_LoadWAV(mSfxShootPath);
	mSfxHit = Mix_LoadWAV(mSfxHitPath);
	mSfxHurt = Mix_LoadWAV(mSfxHurtPath);
	mSfxGameOver = Mix_LoadWAV(mSfxGameOverPath);
	mSfxClick = Mix_LoadWAV(mSfxClickPath);
}

AudioManager::~AudioManager()
{
	Mix_FreeMusic(mMusic);
	Mix_FreeChunk(mSfxShoot);
	Mix_FreeChunk(mSfxHit);
	Mix_FreeChunk(mSfxHurt);
	Mix_FreeChunk(mSfxGameOver);
}

void AudioManager::playMusic()
{
	Mix_PlayMusic(mMusic, -1);
	Mix_VolumeMusic(mMusicVolume);
}

void AudioManager::playShoot()
{
	Mix_PlayChannel(-1, mSfxShoot, 0);
	Mix_VolumeChunk(mSfxShoot, mSoundEffectVolume);
}

void AudioManager::playHit()
{
	Mix_PlayChannel(-1, mSfxHit, 0);
	Mix_VolumeChunk(mSfxHit, mSoundEffectVolume);
}

void AudioManager::playHurt()
{
	Mix_PlayChannel(-1, mSfxHurt, 0);
	Mix_VolumeChunk(mSfxHurt, mSoundEffectVolume);
}

void AudioManager::playGameOver()
{
	Mix_PlayChannel(-1, mSfxGameOver, 0);
	Mix_VolumeChunk(mSfxGameOver, mSoundEffectVolume);
}

void AudioManager::playClick()
{
	Mix_PlayChannel(-1, mSfxClick, 0);
	Mix_VolumeChunk(mSfxClick, mSoundEffectVolume);
}

void AudioManager::toggleMusic()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

void AudioManager::setMusicVolume(int volume)
{
	mMusicVolume = volume;
	Mix_VolumeMusic(mMusicVolume);
}

void AudioManager::setSoundEffectVolume(int volume)
{
	mSoundEffectVolume = volume;
	Mix_VolumeChunk(mSfxShoot, mSoundEffectVolume);
	Mix_VolumeChunk(mSfxHit, mSoundEffectVolume);
	Mix_VolumeChunk(mSfxHurt, mSoundEffectVolume);
	Mix_VolumeChunk(mSfxGameOver, mSoundEffectVolume);
	Mix_VolumeChunk(mSfxClick, mSoundEffectVolume);
}