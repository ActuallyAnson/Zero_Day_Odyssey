//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
/*!
@file				Utils_Physics_Collision.c
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

// To implement the functions declared in the header files
#include "Utils_Physics_Collision.h"

/*
@brief	This function will be used to check if a user clicked within the specific area.
@param	float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y
@return bool
*/
bool IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	return (click_x <= area_center_x + area_width / 2 && click_x >= area_center_x - area_width / 2 && click_y <= area_center_y + area_height / 2 && click_y >= area_center_y - area_height / 2);
}

/*
@brief	This function will be used to check if a user clicked within a specific circle.
@param	float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y
@return bool
*/
bool IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	return (CP_Vector_Distance(CP_Vector_Set(circle_center_x, circle_center_y), CP_Vector_Set(click_x, click_y)) <= diameter);
}

/*
@brief	This function will be used to check if two circles are intersecting or not based on their position and radious
@param	CP_Vector first_circle, float r1, CP_Vector second_circle, float r2
@return bool
*/
bool AreCirclesIntersecting(CP_Vector first_circle, float r1, CP_Vector second_circle, float r2)
{
	// Check if first circle and second circle are colliding with each other based on the cp_vector_distance and radius of first and second circles
	return (CP_Vector_Distance(first_circle, second_circle) <= (r1 + r2));
}

/*
@brief	This function will be used to check if two gameobjects are intersecting or not
@param	GameObject m_OBJ1, GameObject m_OBJ2
@return bool
*/
bool AreGameObjectsIntersecting(GameObject m_OBJ1, GameObject m_OBJ2)
{
	CP_Vector dist = CP_Vector_Subtract(m_OBJ2.m_GlobalPos, m_OBJ1.m_GlobalPos);
	CP_Vector diffofvel = CP_Vector_Subtract(m_OBJ1.m_Vel, m_OBJ2.m_Vel);
	if (CP_Vector_Length(dist) < m_OBJ1.m_Scale + m_OBJ2.m_Scale && CP_Vector_DotProduct(diffofvel, dist) > 0.0f)
	{
		return true;
	}
	return false;
}

/*
@brief	This function will be used to handle the collision and do the appropriate calculation for the physics if the two game objects collided with each other.
@param	GameObject *m_FirstOBJ, GameObject *m_SecondOBJ
@return void
*/
void HandleCollision(GameObject* m_FirstOBJ, GameObject* m_SecondOBJ)
{
	float m1 = (float)m_FirstOBJ->m_Mass;
	float m2 = (float)m_SecondOBJ->m_Mass;
	CP_Vector u1 = m_FirstOBJ->m_Vel; // Vel of OBJ1
	CP_Vector u2 = m_SecondOBJ->m_Vel; // Vel of OBJ2
	CP_Vector au1 = m_FirstOBJ->m_AngularVel; // Angular Vel of OBJ1
	CP_Vector au2 = m_SecondOBJ->m_AngularVel; // Angular Vel of OBJ2

	CP_Vector DirofOBJS = CP_Vector_Normalize(CP_Vector_Subtract(m_FirstOBJ->m_GlobalPos, m_SecondOBJ->m_GlobalPos)); // Calculate the direction of the objects involved

	// Calculate the unit vector of the two objects to represent the direction of object 1 and 2 with the influence of its' velocity
	// Calculate the scalar using dot product of the object respective velocity vector and the direction vector and scale the direction vector by this scalar
	// The result is the unit vector of object 1 and 2 pointing in the direction vector adjusted by the respective velocity vector 
	CP_Vector u1N = CP_Vector_Scale(DirofOBJS, CP_Vector_DotProduct(u1, DirofOBJS));
	CP_Vector u2N = CP_Vector_Scale(DirofOBJS, CP_Vector_DotProduct(u2, DirofOBJS));

	// go->vel = u1 + (2 * m2) / (m1 + m2) * (u2N - u1N); KINEMATIC FORMULA + MOMENTUM
	// Calculate the relative velocity by subtracting u1N from u2N (for object 1)
	// Scale up the relative velocity by 2.0f/3.0f
	// Scale up the new vector by (2 * mass2) / (total mass of the two objects collided) - Momentum after collision
	// Add the initial velocity of the object by the new vectors and assign it as the object new velocity
	m_FirstOBJ->m_Vel = CP_Vector_Add(u1, CP_Vector_Scale(CP_Vector_Scale(CP_Vector_Subtract(u2N, u1N), 2.0f / 3.0f), (2 * m2) / (m1 + m2)));
	m_SecondOBJ->m_Vel = CP_Vector_Add(u2, CP_Vector_Scale(CP_Vector_Scale(CP_Vector_Subtract(u1N, u2N), 2.0f / 3.0f), (2 * m1) / (m1 + m2)));

	// Calculation of angular Velocity
	// Scale each of the angular velocity of the objects based on their respective mass and add them up
	CP_Vector m_CombinedAngularVel = CP_Vector_Add(CP_Vector_Scale(au1, m1), CP_Vector_Scale(au2, m2));

	// Scale the combined angular velocity by  -0.5 divided by its' respective object mass
	// Add the scaled combined angular velocity with the original angular velocity and assigned it to the object's angular velocity
	m_FirstOBJ->m_AngularVel = CP_Vector_Add(au1, CP_Vector_Scale(m_CombinedAngularVel, -0.5f / m1));
	m_SecondOBJ->m_AngularVel = CP_Vector_Add(au2, CP_Vector_Scale(m_CombinedAngularVel, -0.5f / m2));
}

/*
@brief	This function will be used to find the vector of an angle. Mainly used to set a forward velocity of a gameobject.
@param	float rotation
@return CP_Vector
*/
CP_Vector FindVectorOfAngle(float rotation)
{
	return CP_Vector_Set(sinf(rotation / 180 * PI), -cosf(rotation / 180 * PI));
}

/*
@brief	This function will be used to calculate the angle based of the input Vector.
@param	CP_Vector Vector
@return double
*/
double FindAngleofVector(CP_Vector Vector)
{
	double angle = 0.0;
	if (Vector.x < 0) 
	{
		angle = 270 - (atan(Vector.y / -Vector.x) * 180 / PI);
	}
	else 
	{
		angle = 90 + (atan(Vector.y / Vector.x) * 180 / PI);
	}
	return angle;
}

/*
@brief	This function will be used to calculate the angle between 2 objects. Returns float from a range of 0 - 360 degree.
@param	CP_Vector start, CP_Vector target
@return float
*/
float LookAt(CP_Vector start, CP_Vector target)
{
	double opp = target.x - start.x;
	double adj = target.y - start.y;
	float angle = (float)atan(-opp / adj) * 180 / PI;
	if (opp > 0)
	{
		if (adj > 0)
		{
			angle = 180 + angle;
		}
	}
	else
	{
		if (adj > 0)
		{
			angle += 180;
		}
		else
		{
			angle += 360;
		}
	}
	return angle;
}

/*
@brief	This function will be used to wrap values.
@param	float val, float minVal, float maxVal
@return float
*/
float Wrap(float val, float minVal, float maxVal)
{
	if (val < minVal)
		return maxVal;
	else if (val > maxVal)
		return minVal;
	return val;
}