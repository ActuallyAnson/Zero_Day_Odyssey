//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

#pragma once
/*!
@file     Scene_MainMenu.h
@author   Anson (anson.t)
@secondary author Aqif (muhammadnuraqif.b) - ReadHighscore
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Loading of Game Menu
*//*______________________________________________________________________*/
#include <math.h>
#include <cprocessing.h>
#include "Utils_Physics_Collision.h"
#include <stdbool.h>
#define _USE_MATH_DEFINES
#define NUM_HIGH_SCORES 5 // Change this to the number of high scores you want to display

//////////////////////////////////////////////////////
//Scene Main Menu
///////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//CREATION OF VARIABLES & FUNCTIONS


////////////////////////////////////////////////////////////////////////////////////////////
//Button dimensions
float ButtonPosX, ButtonPosY, ButtonWidth, ButtonHeight;
int isTextHovered;

////////////////////////////////////////////////////////////////////////////////////////////
// PopUpMenu Settings
enum PopUp { None, Settings, Leaderboard, Credits };
enum PopUp popUpStatus;

// settings pop-up
int isPopupMenuOpen;
float PopUpWidth;
float PopUpHeight;

float crossButtonX;
float crossButtonY;
float crossButtonWidth;
float crossButtonHeight;

//leaderboard pop-up
float LBcrossButtonX,LBcrossButtonY, LBcrossButtonWidth, LBcrossButtonHeight;
float LeaderboardW;
float LeaderboardH;
int highScores;

float CreditHeight;
float CreditWidth;

////////////////////////////////////////////////////////////////////////////////////////////
enum { MAX_LENGTH = 100 };
enum { MAX_LINES = 6 };
char buffer[];
int numbers[];
int numberCount;

////////////////////////////////////////////////////////////////////////////////////////////
//Cursor Values
float cursorWidth;
float cursorHeight;
float mouseX;
float mouseY;
int isMouseOverText;

//Hover dimensions 

float arrowX;
float arrowY;
float RightArrowW;
float RightArrowH;


//Settings
float volumeSliderX;
float volumeSliderY;
float volumeSliderWidth;
float volumeSliderHeight;
float volume;

float knobPositionX;
int volumeInt;
char volumeText[4];


//Assets loading
CP_Image customCursor;
CP_Image WindowsPopUp;
CP_Image backgroundImage;
CP_Image RightArrow;
CP_Image knobImage;
CP_Image Leaderboardpopup;
CP_Image Credit;

CP_Font myFont; 
CP_Font Clickables;
CP_Font ScoreboardFont;
CP_Font NeonFont;

CP_Sound Confirm;
CP_Sound Hover;
CP_Sound BGM;

void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Render(void);
void Main_Menu_Exit(void);

float ReadMusicVolume(void);

void ReadHighScores(void);
void slider(void);
void CheckButtonCollision(void);

//Checking if area is hovered
bool isAreaHovered(float x, float y, float width, float height);
bool isDragging;




