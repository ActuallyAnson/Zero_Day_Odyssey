//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once
#ifndef GAME_OBJECT_ENEMYBULLET
#define GAME_OBJECT_ENEMYBULLET

/*!
@file             GameObject_EnemyBullet.h
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            Handles the logic of the enemy bullet movement.
				  Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/
#include "cprocessing.h"
#include "GameObject.h"
#include "Utils_Physics_Collision.h"

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
////////////////////////////////////////////////////////////////
//Variables are in .c files

GameObject* GameObject_EnemyBullet_Init(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_EnemyBullet_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_EnemyBullet_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_EnemyBullet_Destroy(GameObject* data);

#endif