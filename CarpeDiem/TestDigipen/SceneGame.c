//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file			  SceneGame.c
@primary_author   Soh Wei Jie (weijie.soh)
@course			  csd1401
@section          B
@Project          Zero Day Odessey
@date             14/11/2023
@brief            GamePlay
*//*______________________________________________________________________*/
#include "Scene_Game.h"

//////////////////////////////////////////////////////////////////////////////
//Init Game
void Game_Init(void)
{
	Util_Window_Init();
	if (CP_System_GetDisplayWidth() == CP_System_GetWindowWidth() || CP_System_GetDisplayHeight() == CP_System_GetWindowHeight())
	{
		Util_Window_Resize((float)CP_System_GetWindowWidth() * 0.9f, (float)CP_System_GetWindowHeight() * 0.9f);
		Util_Window_MoveTo(CP_Vector_Set(m_ScreenCentre.x - (float)CP_System_GetWindowWidth() * 0.9f / 2.0f, 
										 m_ScreenCentre.y - (float)CP_System_GetWindowHeight() * 0.9f / 2.0f));
	}


	UI_Init();
	GameManager_Init();
	m_Background_Main = CP_Image_Load("Assets/Background1.png");
	m_Background_Layer1 = CP_Image_Load("Assets/Background2.png");
	m_Background_Layer2 = CP_Image_Load("Assets/Background4.png");
	m_Background_Layer3 = CP_Image_Load("Assets/Background5.png");
	m_Background_Layer4 = CP_Image_Load("Assets/Background6.png");
	m_BackgroundScale.x = (float)CP_System_GetDisplayWidth() / CP_Image_GetWidth(m_Background_Main);
	m_BackgroundScale.y = (float)CP_System_GetDisplayHeight() / CP_Image_GetHeight(m_Background_Main);
}

//////////////////////////////////////////////////////////////////////////////
//Update Game
void Game_Update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 0));
 
	//Update
	Game_RunSpawningAlgorithm();
	GameManager_Update(); //Update GameObjects
	Util_Window_Update();

	//Render
	Game_Render(); //Render other objects not inside Object Manager like background
	GameManager_Render(); //Render GameObjects
	UI_Render(); //Render UI
	//Condition for GameOverScreen
	if (CurrentHealth <= 0) {
		GameOverScreen(PlayerScore);
	}
}

//////////////////////////////////////////////////////////////////////////////
//Render Game
void Game_Render(void)
{
	////////////////////////////////////////////////////////////////////////////////////////////
	//Draw parallax Background
	//Base
	CP_Vector m_BackgroundPos = CP_Vector_Scale(m_WorldCenter, 0.3f);
	m_BackgroundPos.x = fmodf(m_BackgroundPos.x, CP_Image_GetWidth(m_Background_Main) * m_BackgroundScale.x);
	m_BackgroundPos.y = fmodf(m_BackgroundPos.y, CP_Image_GetHeight(m_Background_Main) * m_BackgroundScale.y);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			CP_Image_Draw(m_Background_Main, m_BackgroundPos.x + x * CP_Image_GetWidth(m_Background_Main) * m_BackgroundScale.x,
				m_BackgroundPos.y + y * CP_Image_GetHeight(m_Background_Main) * m_BackgroundScale.y,
				CP_Image_GetWidth(m_Background_Main) * m_BackgroundScale.x, 
				CP_Image_GetHeight(m_Background_Main) * m_BackgroundScale.y, 255);
		}
	}
	//Layer 1
	m_BackgroundPos = CP_Vector_Scale(m_WorldCenter, 0.5f);
	m_BackgroundPos.x = fmodf(m_BackgroundPos.x, CP_Image_GetWidth(m_Background_Main) * m_BackgroundScale.x);
	m_BackgroundPos.y = fmodf(m_BackgroundPos.y, CP_Image_GetHeight(m_Background_Main) * m_BackgroundScale.y);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			CP_Image_Draw(m_Background_Layer1, m_BackgroundPos.x + x * CP_Image_GetWidth(m_Background_Main) * m_BackgroundScale.x + x * -1,
				m_BackgroundPos.y + y * CP_Image_GetHeight(m_Background_Main) * m_BackgroundScale.y,
				CP_Image_GetWidth(m_Background_Main) * m_BackgroundScale.x,
				CP_Image_GetHeight(m_Background_Main) * m_BackgroundScale.y, 25);
		}
	}
	//Layer 2
	m_BackgroundPos = CP_Vector_Scale(m_WorldCenter, 0.6f);
	m_BackgroundPos.x = fmodf(m_BackgroundPos.x, CP_Image_GetWidth(m_Background_Layer4) * m_BackgroundScale.x);
	m_BackgroundPos.y = fmodf(m_BackgroundPos.y, CP_Image_GetHeight(m_Background_Layer4) * m_BackgroundScale.y);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			CP_Image_Draw(m_Background_Layer4, m_BackgroundPos.x + x * CP_Image_GetWidth(m_Background_Layer4) * m_BackgroundScale.x + x * -1,
				m_BackgroundPos.y + y * CP_Image_GetHeight(m_Background_Layer4) * m_BackgroundScale.y,
				CP_Image_GetWidth(m_Background_Layer4) * m_BackgroundScale.x,
				CP_Image_GetHeight(m_Background_Layer4) * m_BackgroundScale.y, 255);
		}
	}
	//Layer 3
	m_BackgroundPos = CP_Vector_Scale(m_WorldCenter, 0.7f);
	m_BackgroundPos.x = fmodf(m_BackgroundPos.x, CP_Image_GetWidth(m_Background_Layer3) * m_BackgroundScale.x);
	m_BackgroundPos.y = fmodf(m_BackgroundPos.y, CP_Image_GetHeight(m_Background_Layer3) * m_BackgroundScale.y);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			CP_Image_Draw(m_Background_Layer3, m_BackgroundPos.x + x * CP_Image_GetWidth(m_Background_Layer3) * m_BackgroundScale.x + x * -1,
				m_BackgroundPos.y + y * CP_Image_GetHeight(m_Background_Layer3) * m_BackgroundScale.y,
				CP_Image_GetWidth(m_Background_Layer3) * m_BackgroundScale.x,
				CP_Image_GetHeight(m_Background_Layer3) * m_BackgroundScale.y, 255);
		}
	}
	//Layer 4
	m_BackgroundPos = CP_Vector_Scale(m_WorldCenter, 0.8f);
	m_BackgroundPos.x = fmodf(m_BackgroundPos.x, CP_Image_GetWidth(m_Background_Layer2) * m_BackgroundScale.x);
	m_BackgroundPos.y = fmodf(m_BackgroundPos.y, CP_Image_GetHeight(m_Background_Layer2) * m_BackgroundScale.y);
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			CP_Image_Draw(m_Background_Layer2, m_BackgroundPos.x + x * CP_Image_GetWidth(m_Background_Layer2) * m_BackgroundScale.x + x * -1,
				m_BackgroundPos.y + y * CP_Image_GetHeight(m_Background_Layer2) * m_BackgroundScale.y,
				CP_Image_GetWidth(m_Background_Layer2) * m_BackgroundScale.x,
				CP_Image_GetHeight(m_Background_Layer2) * m_BackgroundScale.y, 255);
		}
	}
	//Draw UI
	UI_Render();

	//Draw cursor
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Debugging
	//Draw Frame-rate - for Debugging purposes

	float frameRate = CP_System_GetFrameRate();
	char string[3] = "";
	string[0] = ((int)frameRate / 100) + '0';			// Hundreds digit
	string[1] = (((int)frameRate / 10) % 10) + '0';		// Tens digit
	string[2] = ((int)frameRate % 10) + '0';				// Ones digit

	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText(string, (float)(CP_System_GetWindowWidth()-30), (float)(CP_System_GetWindowHeight() - 10));
}

//////////////////////////////////////////////////////////////////////////////
//Exit Game
void Game_Exit(void)
{
	CP_Image_Free(&m_Background_Main);
	CP_Image_Free(&m_Background_Layer1);
	CP_Image_Free(&m_Background_Layer2);
	CP_Image_Free(&m_Background_Layer3);
	CP_Image_Free(&m_Background_Layer4);
	GameManager_End();
}


//////////////////////////////////////////////////////////////////////////////
// Additional Functions
void Game_RunSpawningAlgorithm(void)
{
	if (isGamePaused) return;

	double RandX, RandY;
	//Spawning Asteroid
	if (rand() % 16 <= (1 + m_Level/10))
	{
		int temp = GameManager_SpawnOBJ(id_Asteroid);
		_List[temp]._OBJ.m_Mass = CP_Random_RangeInt(50, 150);
		_List[temp]._OBJ.m_RenderScale = _List[temp]._OBJ.m_Mass;
		_List[temp]._OBJ.m_Scale = _List[temp]._OBJ.m_Mass/2;
		if (_List[temp]._OBJ.m_Mass > 100)
			_List[temp]._OBJ.m_PNG = rand()%2==1? m_AsteroidLargePNG1 : m_AsteroidLargePNG2;
		else if (_List[temp]._OBJ.m_Mass > 65)
			_List[temp]._OBJ.m_PNG = rand() % 2 == 1 ? m_AsteroidMediumPNG1 : m_AsteroidMediumPNG2;
		else
			_List[temp]._OBJ.m_PNG = rand() % 2 == 1 ? m_AsteroidSmallPNG1 : m_AsteroidSmallPNG2;

		if (rand() % 2 == 1)
			RandX = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.x - 1100, _List[id_Player]._OBJ.m_GlobalPos.x - 1400) + 1.0f;
		else
			RandX = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.x + 1100, _List[id_Player]._OBJ.m_GlobalPos.x + 1400) + 1.0f;
		if (rand() % 2 == 1)
			RandY = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.y - 600, _List[id_Player]._OBJ.m_GlobalPos.y - 800) + 1.0f;
		else
			RandY = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.y + 600, _List[id_Player]._OBJ.m_GlobalPos.y + 800) + 1.0f;
		
		_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set((float)RandX, (float)RandY);
		_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, m_WorldCenter);
		_List[temp]._OBJ.m_Vel = CP_Vector_Scale(CP_Vector_Set(CP_Random_RangeFloat(-1.f,1.f), CP_Random_RangeFloat(-1.f,1.f)), CP_Random_RangeFloat(4.f, 10.f + (float)m_Level / 3.f));
		_List[temp]._OBJ.m_AngularVel = CP_Vector_Set(CP_Random_RangeFloat(-50, 50) * 3.0f, CP_Random_RangeFloat(-50, 50) * 3.0f);
	}
	
	//Spawning Enemy
	if (rand() % 3000 <= (1.0 + m_Level))
	{
		int temp;
		if (m_Level < 5)
		{
			temp = GameManager_SpawnOBJ(id_Enemy_Bandit);
		}
		else if (m_Level < 15)
		{
			switch (rand() % 2)
			{
			case 1:temp = GameManager_SpawnOBJ(id_Enemy_Bandit); break;
			default:temp = GameManager_SpawnOBJ(id_Enemy_Hare); break;
			}
		}
		else
		{
			switch (rand() % 8)
			{
			case 1:temp = GameManager_SpawnOBJ(id_Enemy_Bomber); break;
			case 2: case 3: case 4: temp = GameManager_SpawnOBJ(id_Enemy_Bandit); break;
			default:temp = GameManager_SpawnOBJ(id_Enemy_Hare); break;
			}
		}
		if (rand() % 2 == 1)
			RandX = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.x - 1100, _List[id_Player]._OBJ.m_GlobalPos.x - 1400) + 1.0f;
		else
			RandX = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.x + 1100, _List[id_Player]._OBJ.m_GlobalPos.x + 1400) + 1.0f;
		if (rand() % 2 == 1)
			RandY = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.y - 600, _List[id_Player]._OBJ.m_GlobalPos.y - 800) + 1.0f;
		else
			RandY = CP_Random_RangeFloat(_List[id_Player]._OBJ.m_GlobalPos.y + 600, _List[id_Player]._OBJ.m_GlobalPos.y + 800) + 1.0f;

		_List[temp]._OBJ.m_GlobalPos = CP_Vector_Set((float)RandX, (float)RandY);
		_List[temp]._OBJ.m_LocalPos = CP_Vector_Subtract(_List[temp]._OBJ.m_GlobalPos, m_WorldCenter);
		_List[temp]._OBJ.m_Vel = CP_Vector_Scale(CP_Vector_Set(CP_Random_RangeFloat(-1, 1), CP_Random_RangeFloat(-1, 1)), CP_Random_RangeFloat(1, 10));
		_List[temp]._OBJ.m_AngularVel = CP_Vector_Set(CP_Random_RangeFloat(-50, 50) * 3, CP_Random_RangeFloat(-50, 50) * 3);
		_List[temp]._OBJ.m_DamageResponseTimer = 0.5f;
	}
}