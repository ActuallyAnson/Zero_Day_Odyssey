//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
#pragma once
#ifndef GAME_OBJECT_PLAYER
#define GAME_OBJECT_PLAYER

/*
@file				GameObject_Player.h
@primary_author		Mog Shi Feng (s.mog)
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Handles the logic of the player controls and shooting.
*//*______________________________________________________________________*/

//Necesary Libraries needed to run the functions below.
#include "GameObject.h"
#include "Utils_Physics_Collision.h"

typedef enum GunType { Pistol, Shotgun, Rifle, SplitShot, ChargeRifle } GunType;

typedef struct GunStats
{
	GunType type;
	int ammoCount;
	double rateOfFire;
	double bulletLifeTime;
	int bulletDmg;
	int bulletSpd;
}GunStats;

GunStats currWeap;

//////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
//////////////////////////////////////////////////////////////////////////////
//Variables are in .c files

void GameObject_Player_Init(GameObject* data);
void GameObject_Player_Update(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Player_Render(GameObject* data, CP_Vector* m_WorldCenter);
void GameObject_Player_Destroy(GameObject* data);

/*
@brief	This function will be used to update the current velocity of the player based on accelHoldTime and current rotation.
@param	float accelHoldTime, int velocity, float rotation
@return CP_Vector
*/
CP_Vector UpdateVelocity(float accelHoldTime, int velocity, float rotation);

/*
@brief	This function will be used to rotate the player and look at the current mouse position.
@param	double currRot, CP_Vector currPos
@return double
*/
double PlayerRotation(double currRot, CP_Vector currPos);

/*
@brief	This function will be used to set the currWeap's stats when the current weap is being changed.
@param	struct GunType newGun
@return void
*/
void ChangeWeapon(GunType newGun);

/*
@brief	This function will be used handle the shooting based on the currWeap selected.
@param	CP_Vector playerPos, CP_Vector worldCenter, float renderDir
@return void
*/
void Shoot(CP_Vector playerPos, CP_Vector worldCenter, float renderDir);
#endif