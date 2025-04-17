#pragma once
#ifndef GAME_OBJECT_ENEMYBULLETBULLETTYPES
#define GAME_OBJECT_ENEMYBULLETBULLETTYPES

/*!
@file             GameObject_EnemyBulletTypeS.h
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief			  Handles the logic of the special piercing bullet movement. Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include "GameObject.h"
#include "Utils_Physics_Collision.h"

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
////////////////////////////////////////////////////////////////
//Variables are in .c files

GameObject* GameObject_EnemyBulletTypeS_Init(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_EnemyBulletTypeS_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_EnemyBulletTypeS_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_EnemyBulletTypeS_Destroy(GameObject* data);

#endif