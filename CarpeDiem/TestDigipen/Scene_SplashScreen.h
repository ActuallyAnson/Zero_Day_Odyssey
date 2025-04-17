//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     Scene_SplashScreen.h
@author   Anson (anson.t)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Loading of Icons
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include <math.h>
#include <stdlib.h>

#pragma once
//////////////////////////////////////////////////////
//Scene Splash Screen
///////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
CP_Image logo;
CP_Image team_logo;
float m_time;
int m_abs;
float m_Transparency;
float m_CursorX, m_CursorY;
float valueX, valueY;

void splash_screen_init(void);
void splash_screen_update(void);
void splash_screen_exit(void);
void CursorPositionUpdate(void);
