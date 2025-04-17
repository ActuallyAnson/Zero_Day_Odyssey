//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once
#ifndef GAME_OBJECT_ENEMY_BOMBER
#define GAME_OBJECT_ENEMY_BOMBER

/*!
@file             GameObject_EnemyBomber.h
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            Handles the logic of the Bomber Enemy.
				  Shoots from a distance with the special piercing bullet.
				  Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/
#include "cprocessing.h"
#include "GameObject.h"
#include "Utils_Physics_Collision.h"
#include "Utils_UIGameScene.h"

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
////////////////////////////////////////////////////////////////
//Variables are in .c files

GameObject* GameObject_Enemy_Bomber_Init(GameObject* data, CP_Vector m_WorldCenter);
void GameObject_Enemy_Bomber_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Enemy_Bomber_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Enemy_Bomber_Destroy(GameObject* data);

void GameObject_Enemy_Bomber_Shoot(CP_Vector Pos, CP_Vector worldCenter, double renderDir);
#endif