//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file				GameObject_Bullet.c
@primary_author		Mog Shi Feng (s.mog)
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Handles the logic of the bullet movement. Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/

//Necesary Libraries needed to run the functions below.
#include "GameObject_Bullet.h"
#include "GameObjectManager.h"

//////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS

//////////////////////////////////////////////////////////////////////////////
//GameObject Init
GameObject* GameObject_Bullet_Init(GameObject* data, CP_Vector* m_WorldCenter)
{
	data->m_LifeTime = 0.25f; // Set m_LifeTime on init
	data->m_Active = true;	
	data->m_Scale = 15;
	data->m_RenderScale = 25;
	data->m_PNG = CP_Image_Load("Assets/GameObject_PlayerBulletFull.png");
	return data;
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Update
void GameObject_Bullet_Update(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active || isGamePaused)
		return; 

	data->m_LocalPos = CP_Vector_Add(data->m_LocalPos,
		CP_Vector_Set(data->m_Vel.x * data->m_Movement_Spd * CP_System_GetDt(), data->m_Vel.y * data->m_Movement_Spd * CP_System_GetDt()));
	data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);

	data->m_LifeTime -= CP_System_GetDt();

	if (data->m_LifeTime <= 0)
		GameObject_Bullet_Destroy(data);
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Render
void GameObject_Bullet_Render(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active)
		return;

	//Render IMG
	CP_Settings_BlendMode(CP_BLEND_MAX);
	CP_Image_DrawAdvanced(data->m_PNG, 
		(float)data->m_GlobalPos.x - (float)data->m_RenderScale / 2.0f,
		(float)data->m_GlobalPos.y - (float)data->m_RenderScale / 2.0f,
		(float)data->m_RenderScale,
		(float)data->m_RenderScale,
		255, 
		(float)data->m_RenderAngle);
	CP_Settings_BlendMode(CP_BLEND_ALPHA);
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Destroy
void GameObject_Bullet_Destroy(GameObject* data)
{
	data->m_Vel = CP_Vector_Zero();
	data->m_Active = false;
}