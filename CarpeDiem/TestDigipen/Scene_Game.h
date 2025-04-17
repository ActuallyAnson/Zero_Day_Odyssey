//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file			  SceneGame.h
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            GamePlay
*//*______________________________________________________________________*/

#include "Utils_UIGameScene.h"
#include "Utils_WindowManipulation.h"
#include "Utils_EaseFunctions.h"
#include "StateManager.h"
#include "GameObjectManager.h"
#pragma once

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
CP_Image m_Background_Main, m_Background_Layer1, m_Background_Layer2, m_Background_Layer3, m_Background_Layer4;
CP_Vector m_BackgroundScale;

void Game_Init(void);
void Game_Update(void);
void Game_Render(void); //For rendering background
void Game_Exit(void);

void Game_RunSpawningAlgorithm(void);