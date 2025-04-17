//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once
#ifndef GAME_OBJECT_BULLET
#define GAME_OBJECT_BULLET

/*!
@file				GameObject_Bullet.h
@primary_author		Mog Shi Feng (s.mog)
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Handles the logic of the bullet movement. Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/

#include "GameObject.h"
#include "Utils_Physics_Collision.h"

//////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
//Variables are in .c files

GameObject* GameObject_Bullet_Init(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Bullet_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Bullet_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Bullet_Destroy(GameObject* data);
#endif