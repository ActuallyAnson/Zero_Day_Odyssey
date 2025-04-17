//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*
@file				GameObject_Asteroid.c
@primary_author		Mog Shi Feng (s.mog)
@secondary_author1	Soh Wei Jie (weijie.soh) - Added damage response flicker in update.
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Handles the logic of the asteroid from initalisation to update and being destroyed.
*//*______________________________________________________________________*/

//Necesary Libraries needed to run the functions below.
#include "GameObject_Asteroid.h"
#include "GameObjectManager.h"
#include "Utils_UIGameScene.h"

//////////////////////////////////////////////////////////////////////////////
//GameObject Init
GameObject* GameObject_Asteroid_Init(GameObject* data, CP_Vector m_WorldCenter)
{
	data->m_Health = 20;
	data->m_Active = true;
	data->m_PNG = CP_Image_Load("Assets/GameObject_EAsteroidBIG.png");
	return data;
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Update
void GameObject_Asteroid_Update(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active || isGamePaused)
		return;

	data->m_LocalPos = CP_Vector_Add(data->m_LocalPos, data->m_Vel);
	data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);
	
	float TempAngle = (float)FindAngleofVector(CP_Vector_Normalize(data->m_AngularVel)) - 180.0f;
	if (TempAngle > 0.0001f || TempAngle < -0.0001f)
		data->m_RenderAngle += TempAngle * CP_System_GetDt() * (float)(100.0f* CP_Vector_Length(data->m_AngularVel) / (float)(data->m_Mass* data->m_Mass));
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Render
void GameObject_Asteroid_Render(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active)
		return;

	if(rand() % 2 == 1)
		data->m_DamageResponseTimer -= CP_System_GetDt();

	if (data->m_DamageResponseTimer > 0.0f)
	{
		CP_Image_DrawAdvanced(data->m_PNG,
			(float)data->m_GlobalPos.x - (float) data->m_RenderScale / 2.0f,
			(float)data->m_GlobalPos.y - (float) data->m_RenderScale / 2.0f,
			(float) data->m_RenderScale,
			(float) data->m_RenderScale,
			rand() % 2 == 1 ? 255 : 110, 
			(float) data->m_RenderAngle);
	}
	else
	{
		CP_Image_DrawAdvanced(data->m_PNG,
			(float)data->m_GlobalPos.x - (float) data->m_RenderScale / 2.0f,
			(float)data->m_GlobalPos.y - (float) data->m_RenderScale / 2.0f,
			(float) data->m_RenderScale, (float) data->m_RenderScale,
			255, (float) data->m_RenderAngle);
	}

	CP_Settings_BlendMode(CP_BLEND_ALPHA);
}


//////////////////////////////////////////////////////////////////////////////
//GameObject Destroy
void GameObject_Asteroid_Destroy(GameObject* data)
{
	data->m_Vel = CP_Vector_Zero();
	data->m_Active = false;
}