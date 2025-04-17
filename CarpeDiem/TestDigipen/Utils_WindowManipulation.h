//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

#pragma once

/*!
@file     Utils_WindowManipulation.h
@author   Soh Wei Jie (weijie.soh)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Called to manipulate the game window to achieve certain visual effects
*//*______________________________________________________________________*/

#include <cprocessing.h>
#include <stdbool.h>
#include <stdio.h>
#include "Utils_EaseFunctions.h"
CP_Vector m_ScreenCentre;
CP_Vector m_ScreenTopRight, m_ScreenTopLeft, m_ScreenBottomRight, m_ScreenBottomLeft;

CP_Vector m_WindowPos;
CP_Vector m_WindowScale;
CP_Vector m_NewWindowPos;
CP_Vector m_NewWindowScale;

float m_MovingSpeed;
float m_ScalingSpeed;

bool m_ActivateOrNot;
double m_ScreenShakeTimer, m_ScreenShakeModifier;

void Util_Window_Init(void);
void Util_Window_Update(void);
void Util_Window_MoveTo(CP_Vector newPos);
void Util_Window_Resize(float width, float height);
void Util_Window_Shake(float duration, float strength);
