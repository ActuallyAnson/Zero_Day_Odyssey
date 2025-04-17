//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     StateManager.c
@author   Soh Wei Jie (weijie.soh)
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief	  Functions to easily change between scenes
*//*______________________________________________________________________*/
#include "Scene_MainMenu.h"

#include "StateManager.h"

//////////////////////////////////////////////////////////////////////////////
//Initializing State Manager
//SET NEW SCENES HERE
void StateManagerInit()
{
	currStateName = 0;
	CP_System_SetWindowTitle("Zero_Day_Odyssey.exe");

	splash_screen_init();
	Main_Menu_Init();
	Game_Init();

	_SplashScreen.init = (fnPtr)splash_screen_init;
	_SplashScreen.update = (fnPtr)splash_screen_update;
	_SplashScreen.destroy = (fnPtr)splash_screen_exit;

	_Menu.init = (fnPtr)Main_Menu_Init;
	_Menu.update = (fnPtr)Main_Menu_Update;
	_Menu.destroy = (fnPtr)Main_Menu_Exit;

	_Game.init = (fnPtr)Game_Init;
	_Game.update = (fnPtr)Game_Update;
	_Game.destroy = (fnPtr)Game_Exit;

	currState = &_SplashScreen;
	currState->init();
}

//////////////////////////////////////////////////////////////////////////////
//Update Current Scene
void StateManagerUpdate(void)
{
	CP_System_ShowCursor(0);
	currState->update();
}

//////////////////////////////////////////////////////////////////////////////
//Close Program - Close all scenes
void StateManagerExit(void)
{
	splash_screen_exit();
	Main_Menu_Exit();
	Game_Exit();
}

//////////////////////////////////////////////////////////////////////////////
//Function call to change state via enum name
//CALL TO CHANGE SCENE - ADD NEW SCENES IF NEEDED
void ChangeState(int value)
{
	switch (value)
	{
	case 0:splash_screen_init(); currState = &_SplashScreen; break;
	case 1:Main_Menu_Init(); currState = &_Menu; break;
	case 2:Game_Init(); currState = &_Game; break;
	}
}