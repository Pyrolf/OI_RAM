#ifndef __SOUND_LOADER_H__
#define __SOUND_LOADER_H__

#include "cocos2d.h"

class CSoundLoader
{
public:
	enum BACKGROUND_MUSIC {
		MAIN_MENU_MUSIC = 0,
		GAMEPLAY_MUSIC,
		STORE_MUSIC,
		NUM_OF_MUSIC
	};
	enum SOUND_EFFECT {
		SELECT_SOUND_EFFECT = 0,
		PAUSE_SOUND_EFFECT,
		PAIN_SOUND_EFFECT,
		APPLAUSE_SOUND_EFFECT,
		WHIP_SOUND_EFFECT,
		JAB_SOUND_EFFECT,
		BOUNCE_SOUND_EFFECT,
		SHUSH_SOUND_EFFECT,
		SMASH_SOUND_EFFECT,
		JUMP_SOUND_EFFECT,
		CHIME_SOUND_EFFECT,
		SHOOT_SOUND_EFFECT,
		LEAP_SOUND_EFFECT,
		SUCK_SOUND_EFFECT,
		DROPLET_SOUND_EFFECT,
		NUM_OF_SOUND_EFFECTS
	};
	static void preloadAllSounds();
	static void playBackgroundMusic(BACKGROUND_MUSIC eBGM);
	static void playSoundEffect(SOUND_EFFECT eSFX);
	static void pauseSounds(bool bToPause);
	static void muteBackgroundMusic(bool bToMute);
	static void muteSoundEffect(bool bToMute);
	static void stopBackgroundMusic();
};
#endif // __SOUND_LOADER_H__
