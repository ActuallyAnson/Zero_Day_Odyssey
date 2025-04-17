//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file             GameObject_EnemyBandit.c
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            Handles the logic of the Bandit Enemy.	
		          Shoots from a distance with the special piercing bullet. 
		          Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/

#include "GameObject_Enemy_Bandit.h"
#include "GameObjectManager.h"


////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS

////////////////////////////////////////////////////////////////////////
//GameObject Init
GameObject* GameObject_Enemy_Bandit_Init(GameObject* data, CP_Vector m_WorldCenter)
{
	data->m_Health = 15;
	data->m_Active = true;
	data->m_Mass = 60.0;
	data->m_Scale = 40.0;
	data->m_RenderScale = 80.0;
	data->m_EnemyShootingDelay = 0.0f;
	data->m_PNG = CP_Image_Load("Assets/GameObject_EnemyBandit.png");

	return data;
}

////////////////////////////////////////////////////////////////////////
//GameObject Update
void GameObject_Enemy_Bandit_Update(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active || isGamePaused)
		return;

	data->m_LocalPos = CP_Vector_Add(data->m_LocalPos, data->m_Vel);
	data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);

	float dist = CP_Vector_Distance(_List[id_Player]._OBJ.m_GlobalPos, data->m_GlobalPos);
	CP_Vector newVel = CP_Vector_Normalize(CP_Vector_Subtract(_List[id_Player]._OBJ.m_GlobalPos, data->m_GlobalPos));
	if (dist < 300)
	{
		data->m_Vel = CP_Vector_Add(data->m_Vel, CP_Vector_Scale(newVel, 30.0f / dist));
		data->m_RenderAngle = Lerp(data->m_RenderAngle, LookAt(data->m_LocalPos, _List[id_Player]._OBJ.m_LocalPos), 0.1f);
	}
	else
	{
		data->m_Vel = CP_Vector_Add(data->m_Vel, CP_Vector_Scale(newVel,0.02f));
		data->m_RenderAngle = Lerp(data->m_RenderAngle,
			LookAt(data->m_LocalPos, CP_Vector_Add(data->m_LocalPos, CP_Vector_Normalize(data->m_Vel))),
			0.1f);
	}
	
	
}

////////////////////////////////////////////////////////////////////////
//GameObject Render
void GameObject_Enemy_Bandit_Render(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active)
		return;

	if (rand() % 2 == 1)
		data->m_DamageResponseTimer -= CP_System_GetDt();

	if (data->m_DamageResponseTimer > 0.0f)
	{
		CP_Image_DrawAdvanced(data->m_PNG,
			(float)data->m_GlobalPos.x - (float)data->m_RenderScale / 2.0f,
			(float)data->m_GlobalPos.y - (float)data->m_RenderScale / 2.0f,
			(float)data->m_RenderScale, (float)data->m_RenderScale,
			rand() % 2 == 1 ? 255 : 110, 
			(float)data->m_RenderAngle);
	}
	else
	{
		CP_Image_DrawAdvanced(data->m_PNG,
			(float)data->m_GlobalPos.x - (float)data->m_RenderScale / 2.0f,
			(float)data->m_GlobalPos.y - (float)data->m_RenderScale / 2.0f,
			(float)data->m_RenderScale, (float)data->m_RenderScale,
			255, (float)data->m_RenderAngle);
	}
}


////////////////////////////////////////////////////////////////////////
//GameObject Destroy
void GameObject_Enemy_Bandit_Destroy(GameObject* data)//To spawn new asteroids
{
	data->m_Vel.x = 0;
	data->m_Vel.y = 0;
	data->m_Active = false;
}
