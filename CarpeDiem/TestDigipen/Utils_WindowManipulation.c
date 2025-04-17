//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     Utils_WindowManipulation.c
@author   Soh Wei Jie (weijie.soh)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Called to manipulate the game window to achieve certain visual effects
*//*______________________________________________________________________*/

#include "Utils_WindowManipulation.h"

//////////////////////////////////////////////////////////////////////////////
//Initializing values
void Util_Window_Init(void)
{
	m_ScreenCentre = CP_Vector_Set((float)CP_System_GetDisplayWidth() / 2.0f, (float)CP_System_GetDisplayHeight() / 2.0f);
	m_WindowScale = m_NewWindowScale = CP_Vector_Set((float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
	m_WindowPos = m_NewWindowPos = CP_Vector_Set(m_ScreenCentre.x - (float)(CP_System_GetWindowWidth() / 2),
												 m_ScreenCentre.y - (float)(CP_System_GetWindowHeight() / 2));
	CP_System_SetWindowPosition((int)m_WindowPos.x, (int)m_WindowPos.y);

	m_MovingSpeed = 0.1f;
	m_ScalingSpeed = 0.2f;
	m_ActivateOrNot = false;
	m_ScreenShakeTimer = 0.0f;
	m_ScreenShakeModifier = 1.0f;
}

//////////////////////////////////////////////////////////////////////////////
//Update values (Lerping)
void Util_Window_Update(void)
{
	if (m_ScreenShakeTimer > 0.0f)
	{
		CP_System_SetWindowTitle("ooooooooowwwwww");
		CP_System_SetWindowPosition(
			(int)CP_Math_ClampFloat(CP_Random_RangeFloat(m_WindowPos.x - (float)m_ScreenShakeTimer * (float)m_ScreenShakeModifier, (float)m_WindowPos.x + (float)m_ScreenShakeTimer * (float)m_ScreenShakeModifier), 0.0f, (float)CP_System_GetDisplayWidth() - (float)m_WindowScale.x / 2.0f),
			(int)CP_Math_ClampFloat(CP_Random_RangeFloat(m_WindowPos.y - (float)m_ScreenShakeTimer * (float)m_ScreenShakeModifier, (float)m_WindowPos.y + (float)m_ScreenShakeTimer * (float)m_ScreenShakeModifier), 37.0f, (float)CP_System_GetDisplayHeight() - 37.0f)
		);
		m_ScreenShakeTimer -= CP_System_GetDt();
		return;
	}

	CP_System_SetWindowTitle("Zero_Day_Odyssey.exe");
	if (m_ActivateOrNot)
	{
		m_WindowPos.x = Lerp(m_WindowPos.x, m_NewWindowPos.x, m_MovingSpeed);
		m_WindowPos.y = Lerp(m_WindowPos.y, m_NewWindowPos.y, m_MovingSpeed);
		m_WindowScale.x = Lerp(m_WindowScale.x, m_NewWindowScale.x, m_ScalingSpeed);
		m_WindowScale.y = Lerp(m_WindowScale.y, m_NewWindowScale.y, m_ScalingSpeed);

		CP_System_SetWindowPosition(
			(int)CP_Math_ClampFloat(m_WindowPos.x, 0, CP_System_GetDisplayWidth() - m_WindowScale.x),
			(int)CP_Math_ClampFloat(m_WindowPos.y, 0, CP_System_GetDisplayHeight() - m_WindowScale.y - 37));
		CP_System_SetWindowSize((int)m_WindowScale.x, (int)m_WindowScale.y);
		
		if (CP_Vector_Length(CP_Vector_Subtract(m_NewWindowPos, m_WindowPos)) + CP_Vector_Length(CP_Vector_Subtract(m_NewWindowScale, m_WindowScale)) < 0.01f)
			m_ActivateOrNot = false;
	}
}

//////////////////////////////////////////////////////////////////////////////
//Move to specific position
void Util_Window_MoveTo(CP_Vector newPos)
{
	m_NewWindowPos = newPos;
	m_ActivateOrNot = true;
}

//////////////////////////////////////////////////////////////////////////////
//Scaling window size
void Util_Window_Resize(float width, float height)
{
	m_NewWindowScale.x = width;
	m_NewWindowScale.y = height;
	m_ActivateOrNot = true;
}

//////////////////////////////////////////////////////////////////////////////
//Screen Shake
void Util_Window_Shake(float duration, float strength)
{
	m_ScreenShakeTimer = duration;
	m_ScreenShakeModifier = strength;

}