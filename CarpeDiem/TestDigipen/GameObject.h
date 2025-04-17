//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     GameObject.h
@author   Soh Wei Jie (weijie.soh)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Values of GameObjects
*//*______________________________________________________________________*/

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cprocessing.h>
#include <stdbool.h>
#include "stdio.h"
#include "math.h"

typedef unsigned int (*fnPtr)();

typedef struct GameObject
{
	CP_Vector m_LocalPos; //Position for render (World Pos)curr
	CP_Vector m_GlobalPos; //Position for calculation (Screen Pos)curr
	CP_Vector m_Vel; //Movement velocity
	CP_Vector m_AngularVel; //Movement velocity
	float m_RenderAngle; //Rendering Direction - for rotational movement
	double m_Scale; //For the size of Collision obj
	double m_RenderScale; //For rendering the size of obj
	int m_NodeID; //For m_list in manager
	int m_ID; //Object Type
	int m_Health; //Health
	bool m_Active; //Check if this object is still being used
	double m_Mass; //Mass of Obj
	CP_Image m_PNG; //Image of Obj to render

	//Bullet Specific 
	double m_LifeTime; //
	int m_Bullet_Dmg;
	int m_Movement_Spd;

	//Enemy Specific
	double m_EnemyShootingDelay;

	//ScoreOrb Specific
	double m_ColorR, m_ColorG, m_ColorB; //For color to cycle through
	bool m_ActivateFunction; //To force a specific response contrary to usual behaviour

	//Entity specific
	double m_DamageResponseTimer; //for 

	fnPtr OBJ_Init;//To store address of init
	fnPtr OBJ_Update;//To store address of update
	fnPtr OBJ_Render;//To store address of render
	fnPtr OBJ_Destroy;//To store address of Destroy
}GameObject;


#endif