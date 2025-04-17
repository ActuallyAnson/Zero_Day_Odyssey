//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file			  GameObject_ScoreOrb.c
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief			  Responsible for increasing the score upon collection by player.
				  Drop by destroyable gameobjects.
*//*______________________________________________________________________*/

#include "GameObject_ScoreOrb.h"
#include "GameObjectManager.h"

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS

////////////////////////////////////////////////////////////////////////
//GameObject Init
GameObject* GameObject_ScoreOrb_Init(GameObject* data, CP_Vector* m_WorldCenter)
{
	data->m_Active = true;	
	data->m_Scale = 15;
	data->m_RenderScale = 15;
	data->m_LifeTime = 1.5;
	data->m_ColorR = CP_Random_RangeFloat(0, 255);
	data->m_ColorG = CP_Random_RangeFloat(0, 255);
	data->m_ColorB = CP_Random_RangeFloat(0, 255);

	data->m_ActivateFunction = false;

	return data;
}

////////////////////////////////////////////////////////////////////////
//GameObject Update
void GameObject_ScoreOrb_Update(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active || isGamePaused)
		return;

	//If GameObject is close to the player
	double dist = CP_Vector_Distance(_List[id_Player]._OBJ.m_GlobalPos, data->m_GlobalPos);
	if (dist < 300 || data->m_ActivateFunction)
	{
		//Move towards it
		CP_Vector newVel = CP_Vector_Normalize(CP_Vector_Subtract(_List[id_Player]._OBJ.m_GlobalPos, data->m_GlobalPos));
		//newVel = CP_Vector_Set(CP_Random_RangeFloat(newVel.x - 0.8f, newVel.x + 0.8f), CP_Random_RangeFloat(newVel.y - 0.2f, newVel.y + 0.2f));
		data->m_Vel = CP_Vector_Add(data->m_Vel, CP_Vector_Scale(newVel, 550.f / (float)dist));
		data->m_ActivateFunction = true;
		data->m_LifeTime -= CP_System_GetDt();
		if (data->m_LifeTime < 0.0)
			data->m_Vel = CP_Vector_Scale(newVel, 30); //Need to improve on code
	}
	else if (dist > 500)
	{
		data->m_ActivateFunction = false;
		data->m_Vel = CP_Vector_Length(data->m_Vel) > 0 ? 
			CP_Vector_Set(Lerp(data->m_Vel.x,0,0.1f), Lerp(data->m_Vel.y, 0, 0.1f)) 
			: data->m_Vel;
	}
	
	data->m_LocalPos = CP_Vector_Add(data->m_LocalPos, data->m_Vel);
	data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);

	data->m_ColorR += CP_System_GetDt() * 100;
	data->m_ColorR = (int)data->m_ColorR % 255;
	data->m_ColorG += CP_System_GetDt() * 100;
	data->m_ColorG = (int)data->m_ColorG % 255;
	data->m_ColorB += CP_System_GetDt() * 100;
	data->m_ColorB = (int)data->m_ColorB % 255;
}

////////////////////////////////////////////////////////////////////////
//GameObject Render
void GameObject_ScoreOrb_Render(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active)
		return;


	CP_Settings_Fill(CP_Color_Create((int)data->m_ColorR, (int)data->m_ColorG, (int)data->m_ColorB, 255));
	CP_Graphics_DrawCircle((float)data->m_GlobalPos.x, (float)data->m_GlobalPos.y, (float)data->m_Scale);
}

////////////////////////////////////////////////////////////////////////
//GameObject Destroy
void GameObject_ScoreOrb_Destroy(GameObject* data)
{
	data->m_Vel.x = 0;
	data->m_Vel.y = 0;
	data->m_Active = false;
}