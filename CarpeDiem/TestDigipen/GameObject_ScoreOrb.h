//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once
#ifndef GAME_OBJECT_SCORE_ORB
#define GAME_OBJECT_SCORE_ORB

/*!
@file			  GameObject_ScoreOrb.h
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief			  Responsible for increasing the score upon collection by player.
				  Drop by destroyable gameobjects.
*//*______________________________________________________________________*/
#include "cprocessing.h"
#include "GameObject.h"
#include "Utils_Physics_Collision.h"
#include "Utils_EaseFunctions.h"
////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
////////////////////////////////////////////////////////////////
//Variables are in .c files

GameObject* GameObject_ScoreOrb_Init(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_ScoreOrb_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_ScoreOrb_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_ScoreOrb_Destroy(GameObject* data);

#endif