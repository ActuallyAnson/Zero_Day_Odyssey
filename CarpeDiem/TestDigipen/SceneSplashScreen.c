//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     SceneSplashScreen.c
@author   Anson (anson.t)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Loading of logos
*//*______________________________________________________________________*/
#include "Scene_MainMenu.h"
#include "Scene_SplashScreen.h"
#include "StateManager.h"

//////////////////////////////////////////////////////////////////////////////
//Initializing Splash Screen
void splash_screen_init(void)
{
	//Load Images
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	team_logo = CP_Image_Load("Assets/TeamIcon.png");
	m_Transparency = m_time = 0.0f;
	m_abs = 1;

	// Hide the cursor on this window
	m_CursorX = m_CursorY = 0.0f;

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
}

//////////////////////////////////////////////////////////////////////////////
//Update Splash Screen
void splash_screen_update(void)
{
	m_time += CP_System_GetDt();
	CursorPositionUpdate();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	// Fades in 2 seconds, then holds
	m_Transparency = fmodf(m_time, 5.0f) / 2.0f * 255; 

	//////////////////////////////////////////////////////////////////////////////
	//First Logo - Digipen -> Transparency Update
	if (m_time <= 2.5f)// "logo" fading in
	{
		m_Transparency = fmodf(m_time, 2.5f) / 2.5f * 255;
	}
	else if (2.5f <= m_time && m_time <= 5.0f)// "logo" fading out
	{
		m_Transparency = 255 - (fmodf(m_time - 2.5f, 2.5f) / 2.5f * 255);
	}

	//////////////////////////////////////////////////////////////////////////////
	//Second Logo - Team -> Transparency Update
	if (5.0f <= m_time && m_time <= 7.5f)// "team_logo" fading in
	{
		m_Transparency = fmodf(m_time - 5.0f, 2.5f) / 2.5f * 255;
	}
	else if (7.5f <= m_time && m_time <= 10.0f)// "team_logo" fading out
	{
		m_Transparency = 255 - (fmodf(m_time - 7.5f, 2.5f) / 2.5f * 255);
	}

	//////////////////////////////////////////////////////////////////////////////
	//Draw Corresponding logos
	if (m_time <= 5.0f) {
		CP_Image_Draw(logo, (float)CP_System_GetDisplayWidth() / 8.0f, (float)CP_System_GetDisplayHeight() / 4, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), (int)m_Transparency);
	}
	else if (5.0f <= m_time && m_time <= 10.0f) {
		CP_Image_Draw(team_logo, (float)CP_System_GetDisplayWidth() / 4.0f + 100, (float)CP_System_GetDisplayHeight() / 2 - 450, (float)CP_Image_GetWidth(team_logo), (float)CP_Image_GetHeight(team_logo), (int)m_Transparency);
	}

	//////////////////////////////////////////////////////////////////////////////
    //Change Scene
	// After both logos finish fading, transition to the menu state
	if (m_time > 10.0f) 
	{
		ChangeState(m_Menu);
	}
}

//////////////////////////////////////////////////////////////////////////////
//Exit Splash Screen
void splash_screen_exit(void)
{
	//Free Images
	CP_Image_Free(&logo);
	CP_Image_Free(&team_logo);
}

//////////////////////////////////////////////////////////////////////////////
//Additional Function calls
//////////////////////////////////////////////////////////////////////////////
//Cursor update
void CursorPositionUpdate()
{
	valueX = CP_Input_GetMouseX();
	valueY = CP_Input_GetMouseY();
	m_CursorX += (valueX - m_CursorX) * CP_System_GetDt() * 15.0f;
	m_CursorY += (valueY - m_CursorY) * CP_System_GetDt() * 15.0f;
}