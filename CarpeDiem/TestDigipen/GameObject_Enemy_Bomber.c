//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file             GameObject_EnemyBomber.c
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            Handles the logic of the Bomber Enemy.
		          Shoots from a distance with the special piercing bullet. 
		          Hit Detection will be handled in GameObjectManager.c
*//*______________________________________________________________________*/

#include "GameObject_Enemy_Bomber.h"
#include "GameObjectManager.h"

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS

////////////////////////////////////////////////////////////////////////
//GameObject Init
GameObject* GameObject_Enemy_Bomber_Init(GameObject* data, CP_Vector m_WorldCenter)
{
	data->m_Health = 100;
	data->m_Active = true;
	data->m_Mass = 100.0;
	data->m_Scale = 40.0;
	data->m_RenderScale = 80.0;
	data->m_EnemyShootingDelay = 7.0f;
	data->m_PNG = CP_Image_Load("Assets/GameObject_EnemyBomber.png");

	return data;
}

////////////////////////////////////////////////////////////////////////
//GameObject Update
void GameObject_Enemy_Bomber_Update(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active || isGamePaused)
		return;

	double dist = CP_Vector_Distance(_List[id_Player]._OBJ.m_GlobalPos, data->m_GlobalPos);
	CP_Vector newVel = CP_Vector_Normalize(CP_Vector_Subtract(_List[id_Player]._OBJ.m_GlobalPos, data->m_GlobalPos));
	//Move towards it	
	data->m_Vel = CP_Vector_Add(data->m_Vel, CP_Vector_Scale(newVel, 0.02f));
	data->m_RenderAngle = LookAt(data->m_LocalPos, _List[id_Player]._OBJ.m_LocalPos);

	data->m_EnemyShootingDelay -= CP_System_GetDt();
	if (data->m_EnemyShootingDelay < 0.0f)
	{
		GameObject_Enemy_Bomber_Shoot(data->m_GlobalPos, *m_WorldCenter, data->m_RenderAngle);
		data->m_Vel = CP_Vector_Scale(newVel, -2.0f);
		data->m_EnemyShootingDelay = 7.0f;
	}

	data->m_LocalPos = CP_Vector_Add(data->m_LocalPos, data->m_Vel);
	data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);

}

////////////////////////////////////////////////////////////////////////
//GameObject Render
void GameObject_Enemy_Bomber_Render(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active)
		return;

	if (rand() % 2 == 1)
		data->m_DamageResponseTimer -= CP_System_GetDt();

	CP_Settings_BlendMode(CP_BLEND_MAX);
	if (data->m_DamageResponseTimer > 0.0f)
	{
		CP_Image_DrawAdvanced(data->m_PNG,
			(float)data->m_GlobalPos.x - (float)data->m_RenderScale / 2.0f,
			(float)data->m_GlobalPos.y - (float)data->m_RenderScale / 2.0f,
			(float)data->m_RenderScale, (float)data->m_RenderScale,
			rand() % 2 == 1 ? 255 : 110, data->m_RenderAngle);
	}
	else
	{
		CP_Image_DrawAdvanced(data->m_PNG,
			(float)data->m_GlobalPos.x - (float)data->m_RenderScale / 2.0f,
			(float)data->m_GlobalPos.y - (float)data->m_RenderScale / 2.0f,
			(float)data->m_RenderScale, (float)data->m_RenderScale,
			255, data->m_RenderAngle);
	}
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

}


////////////////////////////////////////////////////////////////////////
//GameObject Destroy
void GameObject_Enemy_Bomber_Destroy(GameObject* data)//To spawn new asteroids
{
	data->m_Vel.x = 0;
	data->m_Vel.y = 0;
	data->m_Active = false;
}

//////////////////////////////////////////////////////////////////////////////
//Additional Function calls
//////////////////////////////////////////////////////////////////////////////

void GameObject_Enemy_Bomber_Shoot(CP_Vector Pos, CP_Vector worldCenter, double renderDir)
{
	int temp = GameManager_SpawnOBJ(id_Enemy_BulletTypeS);
	_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set(Pos.x, Pos.y);
	_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, worldCenter);
	_List[temp]._OBJ.m_Vel = FindVectorOfAngle((float)renderDir);
	_List[temp]._OBJ.m_LifeTime = 5.0;
	_List[temp]._OBJ.m_Bullet_Dmg = 50;
	_List[temp]._OBJ.m_Movement_Spd = 25;
}