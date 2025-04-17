//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     Utils_Settings.c
@author   Anson (anson.t)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Sound Settings Variables and Functions
*//*______________________________________________________________________*/

#include "Utils_Settings.h"
#include "StateManager.h"

float soundvolume = 50.0f;

float getterSoundVolume(void) {
	return soundvolume;
}

void setVolume(float sound) {
	soundvolume = sound;
}