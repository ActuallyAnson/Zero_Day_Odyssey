
//---------------------------------------------------------
// file:	main.c
// author:	Carpe Diem - CSD1401f23 Section B
// email:
// Muhd Nur Aqif		muhammadnuraqif.b@digipen.edu
// Soh Wei Jie			weijie.soh@digipen.edu
// Anson Teng			anson.t@digipen.edu
// Neo Hui Zong			neo.h@digipen.edu
// Mog Shi Feng			s.mog@digipen.edu
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "StateManager.h"

//////////////////////////////////////////////////////////////////////////////
// START PROGRAM
// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
// FULL SCREEN IS DISABLED FOR DEBUGGING PURPOSES - RE-ENABLE FOR GAME TESTING
int main(void)
{
	CP_Engine_SetNextGameState(StateManagerInit, StateManagerUpdate, StateManagerExit);
	CP_System_SetFrameRate(120);
	CP_System_SetWindowSize(1920, 1080);//Pre-emptive setting
	CP_System_Fullscreen();//Disable this for debugging
	CP_Engine_Run();
	return 0;
}
