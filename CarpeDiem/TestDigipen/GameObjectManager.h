//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once

#ifndef GAME_OBJECT_MANAGER
#define GAME_OBJECT_MANAGER

/*!
@file			  GameObjectManager.h
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            Responsible for game object pooling and gameobjects Update and Render Cycle
*//*______________________________________________________________________*/

#include "Utils_UIGameScene.h"
#include "GameObject_Player.h"
#include "GameObject_Asteroid.h"
#include "GameObject_Bullet.h"
#include "GameObject_EnemyBullet.h"
#include "GameObject_EnemyBulletTypeS.h"
#include "GameObject_Enemy_Hare.h"
#include "GameObject_Enemy_Bandit.h"
#include "GameObject_Enemy_Bomber.h"
#include "GameObject_ScoreOrb.h"

/////////////////
//v1.1 - Multiple linked lists inside _List
////////////////
#define NUM_OF_TYPES_OBJS 20
#define NUM_OF_OBJS 10000

/////////////////////////////////////////////////////////////////////////////////////////////
// GameObject Pooling Data
// 
// //Explanation
// Stores base object data to immediately spawn an object
// Set in new object datas when creating new classes of objects.
////////////////////////////////////////////////////////////////////////////////////////////
typedef enum ObjData
{
	id_Player,
	id_ScoreOrb,
	id_Asteroid,
	id_Player_Bullet,
	id_Enemy_Bullet,
	id_Enemy_BulletTypeS,
	id_Enemy_Hare,
	id_Enemy_Bandit,
	id_Enemy_Bomber,
}ObjData;

GameObject _ObjData[NUM_OF_TYPES_OBJS];
GameObject _EmptyGameOBJ; //Acting as base for replacement of values

/////////////////////////////////////////////////////////////////////////////////////////////
// Linked list Gameobject for updating
// 
// //Explanation
// The first 100 elements
// _List[0] -------------> _List[19] = PlaceHolders/ Temp objs acting as heads
//									   for their respective linked lists.
//									   Use _List[enum ObjData] to find the obj.
//                                     Then use while loop to cycle through next node.
// _List[20]-------------->_List[***] = Storing spawned object datas (meant for technical
//										 handling)
////////////////////////////////////////////////////////////////////////////////////////////
typedef struct Node {
	int node_num; //DO NOT ALTER
	int next_node_num;
	int last_node_num;
	GameObject _OBJ;
} Node_t;

Node_t _List[NUM_OF_OBJS];

//I'm writing this here because I'm too lazy to write a good solution to this.
CP_Image m_AsteroidSmallPNG1;
CP_Image m_AsteroidSmallPNG2;
CP_Image m_AsteroidMediumPNG1;
CP_Image m_AsteroidMediumPNG2;
CP_Image m_AsteroidLargePNG1;
CP_Image m_AsteroidLargePNG2;

///////////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
CP_Vector m_WorldCenter;

void GameManager_Init(void); //Initialise link list system
void GameManager_Update(void); //Update cycle of all gameobjects in linked list
void GameManager_Render(void); //Render cycle of all gameobjects in linked list
void GameManager_End(void); //Destroy Link list

int GameManager_GetEmptyNode(void);//Returns an array number to set the data in
int GameManager_SpawnOBJ(ObjData type);
void GameManager_DestroyOBJ(int NodeNum);

void RunCheckCollision(int HeaderNum);

#endif