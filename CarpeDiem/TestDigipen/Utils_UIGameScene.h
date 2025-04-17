//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
@file				Utils_UIGameScene.h
@primary_author		Aqif (muhammadnuraqif.b)
@secondary_author1	Mog Shi Feng (s.mog) - GunOptionScreen, ToggleGunOptionMenu and RenderWeaponMenu.
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Game UI
*//*______________________________________________________________________*/

#include <cprocessing.h>
#include <stdio.h>
#include <stdbool.h>
#include "Utils_Physics_Collision.h"
#include "Scene_MainMenu.h"
#include "StateManager.h"
#include "Utils_EaseFunctions.h"	
#pragma once

//////////////////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS
int m_Score; //For Storing player score
CP_Image m_Pistol, m_Shotgun, m_rifle, m_chargerifle, EnemyDeadDisplay, cursor;
CP_Font m_FontPressStart2P;
CP_Sound gameover, close, try;
bool isGamePaused;
//all of these below are for animation

float duration; // Total duration in seconds
float startValueX;// Start from the center on the X-axis
float startValueY; // Start from the center on the Y-axis
float endValueX;// X-coordinate of the final position
float endValueY; // Y-coordinate of the final position
float finalSizesquare; // Final size of the square

float easedTime; //for gunoption animation
float easedTime2;//for gunoption animation

float initialsizeshot;
float finalsizeshot;

float startvaluexshotbox;
float startvalueyshotbox;
float endvaluexshotbox;
float endvalueyshotbox;

float startvaluexshotgun; //for shotgun text
float startvaluexshotgun2; //for 2nd shotgun text
float startvalueyshotgun; //for shotgun text
float startvalueyshotgun2;

float endvaluexshotgun;		//end value of shotgun text
float endvaluexshotgun2;	//end value of 2nd shotgun text
float endvalueyshotgun;		//end value of shotgun text
float endvalueyshotgun2;	//end value of 2nd shotgun text

float easedT;
float easeT2;
float easeT3;
float endValueXOver;
float endValueYOver;
float endValueXfont;
float endValueYfont;
float endValueXquit;
float endValueYquit;
//ending of animation variables
bool isGunOptionMenuOpen; // 1 means menu is open, 0 means menu is closed
int playeralive;
float HealthBarWidth;
int HighScore;
int EnemyCounter;
int PlayerScore;
int m_Level;
int damage;
float ButtonWidth;
float ButtonHeight;
static bool isLeftMouseButtonPressed;

float gunMenuTimer;

/// <summary>
/// //////////////////////////////
/// </summary>Both this can be taken from player but will need to see if can retrieve with this include system
/// <param name="damage"></param>
int CurrentHealth;
int PistolAmmo;
int sound;

//Randomised Weapons
int randWeap1, randWeap2;

void UI_Init(void);
void UI_Render(void);
void UI_Exit(void);

//////////////////////////////////////////////////////////////////////////////
//For Testing Purposes

void UpdateHighScore(void);
void UpdatePlayerScore(int Points);

//////////////////////////////////////////////////////////////////////////////
//For Rendering - Call to render onto scene
void DrawHealthBar(int CurrentHealth);
void DrawHighScore(void);
void WriteHighScore(int Playerscore, const char* playerName);
void DrawNameInput(const char* playerName, float x, float y);
void EnemyCounterDisplay(void);

void GameOverScreen(int playerScore);
void Level(void);
void UpdateLevel();

void DrawGunIcon(CP_Vector m_pos, CP_Image);




//////////////////////////////////////////////////////////////////////////////
//Randomised Gun Menu
/*
@brief	This function will be used to check for player inputs when selecting weapons.
@param	void
@return void
*/
void GunOptionScreen(void);

/*
@brief	This function will be used to toggle the weapon menu and randomise the weapons available to the player.
@param	void
@return void
*/
void ToggleGunOptionMenu(void);

/*
@brief	This function will be used render the weapon menu based on the inputted weapon.
@param	int option, float posX
@return void
*/
void RenderWeaponMenu(int option, float posX);
