//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once
#ifndef GAME_OBJECT_ASTEROID
#define GAME_OBJECT_ASTEROID

/*!
@file				GameObject_Asteroid.h
@primary_author		Mog Shi Feng (s.mog)
@secondary_author1	Soh Wei Jie (weijie.soh) - Added damage response flicker.
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Handles the logic of the asteroid from initalisation to update and being destroyed.
*//*______________________________________________________________________*/

#include "GameObject.h"
#include "Utils_Physics_Collision.h"

//////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
//Variables are in .c files

GameObject* GameObject_Asteroid_Init(GameObject* data, CP_Vector m_WorldCenter);
void GameObject_Asteroid_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Asteroid_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Asteroid_Destroy(GameObject* data);
#endif