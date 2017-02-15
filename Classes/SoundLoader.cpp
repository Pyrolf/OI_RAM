#include "SoundLoader.h"
#include "SimpleAudioEngine.h"
#include "FileOperation.h"

using namespace CocosDenshion;

const char* filepathForMusic[CSoundLoader::BACKGROUND_MUSIC::NUM_OF_MUSIC] = 
{
	"audio/music/open_sky_music.wav"	,
	"audio/music/race_duel_music.wav"	,
	"audio/music/chubby_cat_music.wav"
};

const char* filepathForSoundEffects[CSoundLoader::SOUND_EFFECT::NUM_OF_SOUND_EFFECTS] =
{
	"audio/sound_effects/select_sound.wav"	,
	"audio/sound_effects/pause_sound.wav"	,
	"audio/sound_effects/pain_sound.wav",
	"audio/sound_effects/applause_sound.wav",
	"audio/sound_effects/whip_sound.wav"	,
	"audio/sound_effects/jab_sound.wav"		,
	"audio/sound_effects/bounce_sound.wav"	,
	"audio/sound_effects/shush_sound.wav"	,
	"audio/sound_effects/smash_sound.wav"	,
	"audio/sound_effects/jump_sound.wav"	,
	"audio/sound_effects/chime_sound.wav"	,
	"audio/sound_effects/shoot_sound.wav"	,
	"audio/sound_effects/leap_sound.wav"	,
	"audio/sound_effects/suck_sound.wav"	,
	"audio/sound_effects/droplet_sound.wav"
};

void CSoundLoader::preloadAllSounds()
{
	auto audio = SimpleAudioEngine::getInstance();
	
	//  Preload backgrouns music
	for (int i = 0; i < BACKGROUND_MUSIC::NUM_OF_MUSIC; i++)
	{
		audio->preloadBackgroundMusic(filepathForMusic[i]);
	}
}

void CSoundLoader::playBackgroundMusic(BACKGROUND_MUSIC eBGM)
{
	auto audio = SimpleAudioEngine::getInstance();
	// Get data Currency
	std::vector<std::string> vec_sData1 = FileOperation::readFile(FileOperation::SETTINGS_DATA_FILE_TYPE);
	if (vec_sData1.size() > 0)
	{
		if (std::stoi(vec_sData1[0]) == 0)
			audio->playBackgroundMusic(filepathForMusic[eBGM], true);
		return;
	}
	audio->playBackgroundMusic(filepathForMusic[eBGM], true);
}

void CSoundLoader::playSoundEffect(SOUND_EFFECT eSFX)
{
	auto audio = SimpleAudioEngine::getInstance();
	// Get data Currency
	std::vector<std::string> vec_sData1 = FileOperation::readFile(FileOperation::SETTINGS_DATA_FILE_TYPE);
	if (vec_sData1.size() > 1)
	{
		if (std::stoi(vec_sData1[1]) == 0)
			audio->playEffect(filepathForSoundEffects[eSFX]);
		return;
	}
	audio->playEffect(filepathForSoundEffects[eSFX]);
}

void CSoundLoader::pauseSounds(bool bToPause)
{
	auto audio = SimpleAudioEngine::getInstance();
	if (bToPause)
	{
		audio->pauseBackgroundMusic();
		audio->pauseAllEffects();
	}
	else
	{
		audio->resumeBackgroundMusic();
		audio->resumeAllEffects();
	}
}
void CSoundLoader::muteBackgroundMusic(bool bToMute)
{
	auto audio = SimpleAudioEngine::getInstance();
	if (bToMute)
	{
		audio->stopBackgroundMusic();
	}
	else
	{
		playBackgroundMusic(MAIN_MENU_MUSIC);
	}
}

void CSoundLoader::muteSoundEffect(bool bToMute)
{
	auto audio = SimpleAudioEngine::getInstance();
	if (bToMute)
	{
		audio->stopAllEffects();
	}
}

void CSoundLoader::stopBackgroundMusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
}