#pragma once
//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
/*!
@file				Utils_Physics_Collision.h
@primary_author		Neo Hui Zong (neo.h)
@secondary_author1	Soh Wei Jie (weijie.soh) - Wrote boolean check for AreGameObjectsIntersecting, Wrap
@secondary_author2	Mog Shi Feng (s.mog) - FindVectorOfAngle, FindAngleofVector, LookAt
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				- Physics Collision between circle OBJS with kinematic and momentum formula
					- Circle to Circle Collsiion Checks
					- Angle from Vector
*//*______________________________________________________________________*/

// Necessary library to be used together with the functions declared below
#include "cprocessing.h"
#include <stdbool.h>
#include <math.h>
#include "GameObject.h"
#define PI 3.141592654f

////////////////////////////////////////////////////////////////
//BOOLEAN CHECKS FOR COLLISION

/*
@brief	This function will be used to check if a user clicked within the specific area.
@param	float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y
@return bool
*/
bool IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

/*
@brief	This function will be used to check if a user clicked within a specific circle.
@param	float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y
@return bool
*/
bool IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

/*
@brief	This function will be used to check if two circles are intersecting or not based on their position and radious
@param	CP_Vector first_circle, float r1, CP_Vector second_circle, float r2
@return bool
*/
bool AreCirclesIntersecting(CP_Vector first_circle, float r1, CP_Vector second_circle, float r2);

/*
@brief	This function will be used to check if two gameobjects are intersecting or not
@param	GameObject m_OBJ1, GameObject m_OBJ2
@return bool
*/
bool AreGameObjectsIntersecting(GameObject m_OBJ1, GameObject m_OBJ2);

/*
@brief	This function will be used to handle the collision and do the appropriate calculation for the physics if the two game objects collided with each other.
@param	GameObject *m_FirstOBJ, GameObject *m_SecondOBJ
@return void
*/
void HandleCollision(GameObject *m_FirstOBJ, GameObject *m_SecondOBJ);

/*
@brief	This function will be used to find the vector of an angle. Mainly used to set a forward velocity of a gameobject.
@param	float rotation
@return CP_Vector
*/
CP_Vector FindVectorOfAngle(float rotation);

/*
@brief	This function will be used to calculate the angle based of the input Vector.
@param	CP_Vector Vector
@return double
*/
double FindAngleofVector(CP_Vector Vector);

/*
@brief	This function will be used to calculate the angle between 2 objects. Returns float from a range of 0 - 360 degree.
@param	CP_Vector start, CP_Vector target
@return float
*/
float LookAt(CP_Vector start, CP_Vector target);

/*
@brief	This function will be used to wrap values.
@param	float val, float minVal, float maxVal
@return float
*/
float Wrap(float val, float minVal, float maxVal);