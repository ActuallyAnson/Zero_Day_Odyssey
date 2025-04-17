//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*
@file				GameObject_Player.c
@primary_author		Mog Shi Feng (s.mog)
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Handles the logic of the player controls and shooting.
*//*______________________________________________________________________*/

//Necesary Libraries needed to run the functions below.
#include "GameObject_Player.h"
#include "GameObjectManager.h" 
#include "Utils_UIGameScene.h"

//////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
int moveSpd = 800;
int rotSpd = 100;
float maxVel_precise = 4.0f;
int maxVel_speed = 10;
float accelHoldTime = 0.0f;
int currentControlScheme = 0;

//Gun Stat
double gunHoldTime = 0;

//////////////////////////////////////////////////////////////////////////////
//GameObject Init
void GameObject_Player_Init(GameObject* data)
{
	data->m_Active = true;
	ChangeWeapon(Pistol);
	data->m_Health = 100;
	data->m_Mass = 10;
	data->m_GlobalPos = CP_Vector_Set(m_NewWindowScale.x / 2, m_NewWindowScale.y / 2);
	data->m_LocalPos = CP_Vector_Zero();
	data->m_Scale = 30;
	data->m_RenderScale = 100;
	data->m_PNG = CP_Image_Load("Assets/GameObject_PlayerMain.png");
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Update
void GameObject_Player_Update(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active || isGamePaused)
		return;

	//Changing between controls
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_RIGHT))
		currentControlScheme = currentControlScheme == 0 ? 1 : 0;

	//For Debugging
	if (CP_Input_KeyTriggered(KEY_Q))
		ChangeWeapon(currWeap.type = currWeap.type + 1 > SplitShot ? Pistol : currWeap.type + 1);

	////////////////////////////////////////////////////////////////////////
	//FIRE WEAPON
	gunHoldTime -=  gunHoldTime >= 0 ? CP_System_GetDt() : 0;
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		if (gunHoldTime <= 0 && currWeap.ammoCount > 0)
		{
			gunHoldTime = currWeap.rateOfFire;
			Shoot(data->m_GlobalPos, *m_WorldCenter, (float)data->m_RenderAngle);
		}
	}

	////////////////////////////////////////////////////////////////////////
	// VELOCITY DECAY
	if(!(CP_Input_KeyDown(KEY_W) && CP_Input_KeyDown(KEY_A) && CP_Input_KeyDown(KEY_S) && CP_Input_KeyDown(KEY_D)))
	{
		data->m_Vel.x += data->m_Vel.x < -0.2 ? 0.1f : (data->m_Vel.x > 0.2 ? -0.1f : 0);
		data->m_Vel.y += data->m_Vel.y < -0.2 ? 0.1f : (data->m_Vel.y > 0.2 ? -0.1f : 0);
	}

	////////////////////////////////////////////////////////////////////////
	//PRECISE MOVEMENT
	if (currentControlScheme == 0)
	{
		if (CP_Input_KeyDown(KEY_W))
		{
			data->m_Vel.y = -moveSpd * CP_System_GetDt();
		}
		else if (CP_Input_KeyReleased(KEY_W))
		{
			data->m_Vel.y = 0;
		}

		if (CP_Input_KeyDown(KEY_S))
		{
			data->m_Vel.y = moveSpd * CP_System_GetDt();
		}
		else if (CP_Input_KeyReleased(KEY_S))
		{
			data->m_Vel.y = 0;
		}

		if (CP_Input_KeyDown(KEY_A))
		{
			data->m_Vel.x = -moveSpd * CP_System_GetDt();
		}
		else if (CP_Input_KeyReleased(KEY_A))
		{
			data->m_Vel.x = 0;
		}

		if (CP_Input_KeyDown(KEY_D))
		{
			data->m_Vel.x = moveSpd * CP_System_GetDt();
		}
		else if (CP_Input_KeyReleased(KEY_D))
		{
			data->m_Vel.x = 0;
		}

		if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_A) || CP_Input_KeyDown(KEY_S) || CP_Input_KeyDown(KEY_D))
		{
			data->m_Vel = CP_Vector_Scale(CP_Vector_Normalize(data->m_Vel), maxVel_precise);
		}

		if (CP_Vector_Length(data->m_Vel) > 0)
		{
			(*m_WorldCenter) = CP_Vector_Subtract(*m_WorldCenter, data->m_Vel);
			data->m_LocalPos = CP_Vector_Add(data->m_LocalPos, data->m_Vel);
			data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);
		}
		data->m_RenderAngle = (float)PlayerRotation(data->m_RenderAngle, data->m_GlobalPos);
	}
	////////////////////////////////////////////////////////////////////////
	//FAST TRAVEL MOVEMENT
	else if (currentControlScheme == 1)
	{
		if (CP_Input_KeyDown(KEY_A))
		{
			data->m_RenderAngle -= rotSpd * CP_System_GetDt();
			data->m_Vel = UpdateVelocity(accelHoldTime, maxVel_speed, (float)data->m_RenderAngle);
		}
		else if (CP_Input_KeyDown(KEY_D))
		{
			data->m_RenderAngle += rotSpd * CP_System_GetDt();
			data->m_Vel = UpdateVelocity(accelHoldTime, maxVel_speed, (float)data->m_RenderAngle);
		}
		if (CP_Input_KeyDown(KEY_W))
		{
			if (accelHoldTime <= 1)
			{
				accelHoldTime += CP_System_GetDt() * 2;
			}
			data->m_Vel = UpdateVelocity(accelHoldTime, maxVel_speed, (float)data->m_RenderAngle);
		}
		else if (CP_Input_KeyDown(KEY_S))
		{
			if (accelHoldTime >= -1)
			{
				accelHoldTime -= CP_System_GetDt() * 2;
			}
			data->m_Vel = UpdateVelocity(accelHoldTime, maxVel_speed, (float)data->m_RenderAngle);
		}
		else
		{
			if (accelHoldTime <= -0.02f || accelHoldTime >= 0.02f)
			{
				accelHoldTime -= accelHoldTime > 0 ? CP_System_GetDt() : 0;
				accelHoldTime += accelHoldTime < 0 ? CP_System_GetDt() : 0;
				data->m_Vel = UpdateVelocity(accelHoldTime, maxVel_speed, (float)data->m_RenderAngle);
			}
			else accelHoldTime = 0;
		}

		if (CP_Vector_Length(data->m_Vel) > 0)
		{
			(*m_WorldCenter) = CP_Vector_Subtract(*m_WorldCenter, data->m_Vel);
			data->m_LocalPos = CP_Vector_Add(data->m_LocalPos, data->m_Vel);
			data->m_GlobalPos = CP_Vector_Add(data->m_LocalPos, *m_WorldCenter);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Render
void GameObject_Player_Render(GameObject* data, CP_Vector* m_WorldCenter)
{
	if (!data->m_Active)
		return;

	//Rendering of PlayerImg
	CP_Image_DrawAdvanced(data->m_PNG, 
		(float)data->m_LocalPos.x + m_WorldCenter->x - (float)data->m_RenderScale/2,
		(float)data->m_LocalPos.y + m_WorldCenter->y - (float)data->m_RenderScale/2,
		(float)data->m_RenderScale,
		(float)data->m_RenderScale,
		255, 
		(float)data->m_RenderAngle);

	//Rendering of bullet count
	char string[4] = "";
	string[0] = (currWeap.ammoCount / 100) + '0';			// Hundreds digit
	string[1] = ((currWeap.ammoCount / 10) % 10) + '0';		// Tens digit
	string[2] = (currWeap.ammoCount % 10) + '0';			// Ones digit

	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText(string, data->m_LocalPos.x + m_WorldCenter->x + 30, data->m_LocalPos.y + m_WorldCenter->y + 30);
}

//////////////////////////////////////////////////////////////////////////////
//GameObject Destroy
void GameObject_Player_Destroy(GameObject* data)
{

}

//////////////////////////////////////////////////////////////////////////////
//Additional Function calls
//////////////////////////////////////////////////////////////////////////////
/*
@brief	This function will be used to update the current velocity of the player based on accelHoldTime and current rotation.
@param	float accelHoldTime, int velocity, float rotation
@return CP_Vector
*/
CP_Vector UpdateVelocity(float accelHoldTime, int velocity, float rotation)
{
	return CP_Vector_Set(sinf(rotation / 180 * PI) * accelHoldTime * velocity, -cosf(rotation / 180 * PI) * accelHoldTime * velocity);
}

/*
@brief	This function will be used to rotate the player and look at the current mouse position.
@param	double currRot, CP_Vector currPos
@return double
*/
double PlayerRotation(double currRot, CP_Vector currPos)
{
	currRot = LookAt(currPos, CP_Vector_Set(CP_Input_GetMouseX(), CP_Input_GetMouseY()));
	return currRot;
}

/*
@brief	This function will be used to set the currWeap's stats when the current weap is being changed.
@param	struct GunType newGun
@return void
*/
void ChangeWeapon(GunType newGun)
{
	switch (newGun)
	{
		case Pistol:
		{
			currWeap.type = newGun;
			currWeap.ammoCount = 15;
			currWeap.rateOfFire = .3f;
			currWeap.bulletDmg = 10;
			currWeap.bulletLifeTime = 0.3f;
			currWeap.bulletSpd = 2500;
			break;
		}

		case Shotgun:
		{
			currWeap.type = newGun;
			currWeap.ammoCount = 50;
			currWeap.rateOfFire = .7f;
			currWeap.bulletDmg = 40;
			currWeap.bulletLifeTime = 0.2f;
			currWeap.bulletSpd = 3000;
			break;
		}

		case Rifle:
		{
			currWeap.type = newGun;
			currWeap.ammoCount = 30;
			currWeap.rateOfFire = .2f;
			currWeap.bulletDmg = 50;
			currWeap.bulletLifeTime = 0.6f;
			currWeap.bulletSpd = 6000;
			break;
		}

		case SplitShot:
		{
			currWeap.type = newGun;
			currWeap.ammoCount = 150;
			currWeap.rateOfFire = .1f;
			currWeap.bulletDmg = 5;
			currWeap.bulletLifeTime = 1.3f;
			currWeap.bulletSpd = 750;
			break;
		}
	}
}

/*
@brief	This function will be used handle the shooting based on the currWeap selected.
@param	CP_Vector playerPos, CP_Vector worldCenter, float renderDir
@return void
*/
void Shoot(CP_Vector playerPos, CP_Vector worldCenter, float renderDir)
{
	switch (currWeap.type)
	{
		case Pistol:
		{
			currWeap.ammoCount--;
			int temp = GameManager_SpawnOBJ(id_Player_Bullet);
			_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set(playerPos.x, playerPos.y);
			_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, worldCenter);
			_List[temp]._OBJ.m_Vel =  FindVectorOfAngle(renderDir);
			_List[temp]._OBJ.m_LifeTime = currWeap.bulletLifeTime;			
			_List[temp]._OBJ.m_Bullet_Dmg = currWeap.bulletDmg;
			_List[temp]._OBJ.m_Movement_Spd = currWeap.bulletSpd;
			break;
		}

		case Shotgun:
		{
			float rand = 0;
			for (int i = 0; i < 5; i++)
			{
				currWeap.ammoCount--;
				rand = CP_Random_RangeFloat(renderDir - 20, renderDir + 20);
				int temp = GameManager_SpawnOBJ(id_Player_Bullet);
				_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set(playerPos.x, playerPos.y);
				_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, worldCenter);
				_List[temp]._OBJ.m_Vel = FindVectorOfAngle(rand);
				_List[temp]._OBJ.m_LifeTime = currWeap.bulletLifeTime;
				_List[temp]._OBJ.m_Bullet_Dmg = currWeap.bulletDmg;
				_List[temp]._OBJ.m_Movement_Spd = CP_Random_RangeInt(currWeap.bulletSpd - 150, currWeap.bulletSpd + 150);
			}
			break;
		}

		case Rifle:
		{
			currWeap.ammoCount--;
			int temp = GameManager_SpawnOBJ(id_Player_Bullet);
			_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set(playerPos.x, playerPos.y);
			_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, worldCenter);
			_List[temp]._OBJ.m_Vel = FindVectorOfAngle(renderDir);
			_List[temp]._OBJ.m_LifeTime = currWeap.bulletLifeTime;
			_List[temp]._OBJ.m_Bullet_Dmg = currWeap.bulletDmg;
			_List[temp]._OBJ.m_Movement_Spd = currWeap.bulletSpd;
			break;
		}

		case SplitShot:
		{
			for (float i = renderDir - 20; i <= renderDir + 20; i += 20)
			{
				currWeap.ammoCount--;
				int temp = GameManager_SpawnOBJ(id_Player_Bullet);
				_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set(playerPos.x, playerPos.y);
				_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, worldCenter);
				_List[temp]._OBJ.m_Vel = FindVectorOfAngle(i);
				_List[temp]._OBJ.m_LifeTime = currWeap.bulletLifeTime;
				_List[temp]._OBJ.m_Bullet_Dmg = currWeap.bulletDmg;
				_List[temp]._OBJ.m_Movement_Spd = currWeap.bulletSpd;
			}
			break;
		}
	}

	if (currWeap.ammoCount <= 0)
		ToggleGunOptionMenu();
}