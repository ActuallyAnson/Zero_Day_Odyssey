//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

#ifndef ENGINE_STATEMANAGER_H
#define ENGINE_STATEMANAGER_H

/*!
@file     StateManager.h
@author   Soh Wei Jie (weijie.soh)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief	  Functions to easily change between scenes
*//*______________________________________________________________________*/

//////////////////////////////////////////////////////
//GAME STATE MANAGER SELECTOR V1.0
///////////////////////////////////////////////////////
#pragma once

#include "Scene_SplashScreen.h"
#include "Scene_MainMenu.h"
#include "Scene_Game.h"
typedef unsigned int (*fnPtr)();

////////////////////////////////////////////////////////////////
//DEFINITION OF A SCENE STATE - Don't need to alter
typedef struct State {
	fnPtr init;
	fnPtr update;
	fnPtr destroy;
} State;

////////////////////////////////////////////////////////////////
//NAME ALL SCENES HERE - Add if necessary
typedef enum GameState {
	m_SplashScreen,
	m_Menu,
	m_Game
} GameState;

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
GameState currStateName;
State* currState;
State _SplashScreen, _Menu, _Game;

void StateManagerInit(void);
void StateManagerUpdate(void);
void StateManagerExit(void);
void ChangeState(int _val);
#endif