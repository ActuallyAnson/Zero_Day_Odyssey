//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.
@file				Utils_UIGameScene.c
@primary_author		Aqif (muhammadnuraqif.b)
@secondary_author1	Mog Shi Feng (s.mog) - GunOptionScreen, ToggleGunOptionMenu and RenderWeaponMenu.
@course				csd1401
@section			B
@Project			Zero Day Odessey
@date				14/11/2023
@brief				Game UI
*//*______________________________________________________________________*/

#include "Utils_UIGameScene.h"

//////////////////////////////////////////////////////////////////////////////
//UI Basic Functions
void UI_Init(void)
{
	initialsizeshot = 25.f;
	ButtonHeight = 400.f;
	ButtonWidth = 900.f;
	sound = 0;
	try = CP_Sound_Load("Assets/tryagain.ogg");
	gameover = CP_Sound_Load("Assets/GameOver.ogg");
	close = CP_Sound_Load("Assets/Close.ogg");
	duration = 2.0f;  // Total duration in seconds
	startValueX = CP_System_GetWindowWidth() / 2.0f;  // Start from the center on the X-axis
	startValueY = CP_System_GetWindowHeight() / 2.0f; // Start from the center on the Y-axis
	endValueX = 600.f;  // X-coordinate of the final position 600 initial
	endValueY = 200.0f;  // Y-coordinate of the final position
	finalSizesquare = 750.f;   // Final size of the square 750 initial
	endValueXOver = 970.0f;
	endValueYOver = 300.0f;
	endValueXfont = 950.0f;
	endValueYfont = 450.0f;
	endValueXquit = 950.0f;
	endValueYquit = 900.0f;
	m_Pistol = CP_Image_Load("Assets/guns.png");
	m_Shotgun = CP_Image_Load("Assets/actual_shotgun.png");
	m_rifle = CP_Image_Load("Assets/rifle.png");
	m_chargerifle = CP_Image_Load("Assets/chargerifle.png");
	EnemyDeadDisplay = CP_Image_Load("Assets/barnacle_dead.png");
	m_FontPressStart2P = CP_Font_Load("Assets/PressStart2P-Regular.ttf");
	startvaluexshotbox =0.f;
	startvalueyshotbox = CP_System_GetWindowHeight() / 2.0f;
	initialsizeshot = 25.f;
	finalsizeshot = 350.f;
	endvaluexshotbox = 600.f;
	endvalueyshotbox = 200.f;
	m_Level = 1;
	CurrentHealth = 100;
	PistolAmmo = 900;
	EnemyCounter = 0;
	isGunOptionMenuOpen = false;
	cursor = CP_Image_Load("Assets/cursorpointerFlat.png");

	PlayerScore = 0;
	isGamePaused = false;
	gunMenuTimer = 2.0f;
}

void UI_Render(void)
{
	DrawHealthBar(CurrentHealth);
	DrawHighScore();
	// Rendering Weapon Icon
	switch (currWeap.type)
	{
		case Pistol:
			DrawGunIcon(CP_Vector_Set(0, CP_System_GetWindowHeight() - 100.f), m_Pistol);
			break;
		case Shotgun:
			DrawGunIcon(CP_Vector_Set(0, CP_System_GetWindowHeight() - 100.f), m_Shotgun);
			break;
		case Rifle:
			DrawGunIcon(CP_Vector_Set(0, CP_System_GetWindowHeight() - 100.f), m_rifle);
			break;
		case ChargeRifle:
			DrawGunIcon(CP_Vector_Set(0, CP_System_GetWindowHeight() - 100.f), m_chargerifle);
			break;
	}
	Level();
	GunOptionScreen();
	
	cursorWidth = (float)CP_Image_GetWidth(customCursor);
	cursorHeight = (float)CP_Image_GetHeight(customCursor);
	CP_Image_Draw(customCursor, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
}

void UI_Exit(void)
{
	CP_Image_Free(&m_Pistol);
	CP_Image_Free(&m_Shotgun);
	CP_Image_Free(&m_rifle);
	CP_Image_Free(&m_chargerifle);
	CP_Image_Free(&EnemyDeadDisplay);
}

//////////////////////////////////////////////////////////////////////////////
//Additional Function calls
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//Rendering
/*
brief Drawing of gun icons at bottom left of the screen
param CPVector m_pos and CP_Image
*/
void DrawGunIcon(CP_Vector m_pos, CP_Image image) {
	float screenwidth = (float)CP_System_GetWindowWidth();
	float screenheight = (float)CP_System_GetWindowHeight();
	CP_Image_Draw(image, m_pos.x, m_pos.y, 300.f, 100.f, 255);
}

void EnemyCounterDisplay(void) {
	EnemyDeadDisplay = CP_Image_Load("Assets/barnacle_dead.png");
	CP_Image_Draw(EnemyDeadDisplay, 10.0f, 120.0f, 51.0f, 57.0f, 255);
	char DeadString[10];
	snprintf(DeadString, sizeof(DeadString), "%d", EnemyCounter);
	CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
	CP_Font_DrawText(DeadString, 150.0f, 160.0f);

}
/*
Healthbar changes colour when being hit
params int current health
return void
*/
void DrawHealthBar(int CurrentHealth) 
{
	HealthBarWidth = 200.0f * ((float)CurrentHealth / 100.0f);
	float GrayedHealthBarWidth = 200.0f - HealthBarWidth;

	// Determine the color based on the current health
	CP_Color color;
	if (CurrentHealth >= 60) 
	{
		// Green color for health >= 60
		color = CP_Color_Create(0, 255, 0, 255);
	}
	else if (CurrentHealth >= 30) 
	{
		// Yellow color for health between 30 and 59
		color = CP_Color_Create(255, 255, 0, 255);
	}
	else 
	{
		// Red color for health between 0 and 29
		color = CP_Color_Create(255, 0, 0, 255);
	}
	if (CurrentHealth == 100)
	{
		float alpha = 255.0f - (255.0f * (2.f / 2.3f));
		if (alpha < 0.0f) alpha = 0.0f;
		color.a = (int)alpha;
	}
	CP_Settings_Fill(color);
	CP_Graphics_DrawRect(10.f, 50.f, HealthBarWidth, 50.f);

	// Draw the grayed out portion of the health bar
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));  // Gray color
	CP_Graphics_DrawRect(10+HealthBarWidth, 50.f, GrayedHealthBarWidth, 50.f);

	//Draw out text
	CP_Font_Set(m_FontPressStart2P);
	CP_Settings_TextSize(30.0f);
	CP_Settings_Fill(CP_Color_Create(173, 216, 230, 255));
	CP_Font_DrawText("Health", 100.f, 20.f);
}

//////////////////////////////////////////////////////////////////////////////
//HighScore Logic 
void DrawHighScore(void)
{
	float screenwidth = (float)CP_System_GetWindowWidth();
	CP_Settings_Fill(CP_Color_Create(255, 192, 203, 255));  // Black color
	CP_Font_DrawText("Score", screenwidth - 90, 40.f);  // Display "High Score" at (500, 40)

	// Convert the high score to a string
	char highScoreString[20];
	snprintf(highScoreString, sizeof(highScoreString), "%07d", PlayerScore);

	// Draw the high score below "High Score"
	CP_Font_DrawText(highScoreString, screenwidth - 120, 80.f);
}

void UpdatePlayerScore(int Points) {
	PlayerScore += Points;
	UpdateHighScore();
}

void ReadHighscore()
{
	//Look at header file
}

/*
brief write highscore and name into a file
params int playerscore and const char name
return void
*/
void WriteHighScore(int PlayerScore, const char* playerName) {
	FILE* file;
	fopen_s(&file, "Assets/highscore.txt", "a");
	if (file) {
		fprintf(file, "%s %d\n", playerName, PlayerScore);
		fclose(file);
	}
	else {
		printf("Error opening the file.\n");
	}
}
//void SetHighscore(void)
//{
//
//}


//////////////////////////////////////////////////////////////////////////////
//Testing
void UpdateHighScore(void) {
	if (PlayerScore > HighScore) {
		HighScore = PlayerScore;
	}
}



/*
brief draw name at the gameover screen
params const char playername and float x and y for coord
return void
*/
void DrawNameInput(const char* playerName, float x, float y) {
	CP_Settings_TextSize(20.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Name: ", x, y);

	CP_Font_DrawText(playerName, x + 80, y);
}
enum NameEntryState {
	ENTERING_NAME,
	NAME_ENTERED
};

char playerName[5] = "____";  // Initial character for the name
int activeIndex = 0;
int underscoreIndex = 26;
// Initialize the state
enum NameEntryState entryState = ENTERING_NAME;
/*
brief handles gameover screen by showing scores and inputting of name
Use directional UP key once(starts at Z),press down key to cycle down. Vice Versa for down key but starts at A

param int playerscore
return void
*/
void GameOverScreen(int playerScore) {
	static int errorMessageTimer = 0;
	static int errorMessageDuration = 180;
	isGamePaused = true;

	if (!sound) {
		isGamePaused = true;
		CP_Sound_Play(gameover);
		sound = 1;
	}
	static float timer = 0.f;
	
	timer += CP_System_GetDt();
	
	if (timer < duration) {
		float t = timer / duration;
		easedT = EaseInOutBack(0.0f, 1.0f, t);
		easeT2 = EaseInOutElastic(0.0f, 1.0f, t);
		easeT3 = EaseInOutCubic(0.0f, 1.0f, t);
	}
	else {
		easedT = 1.0f;// Ensure it's fully eased when the timer exceeds duration
		easeT2 = 1.0f;
		easeT3 = 1.0f;
	}

	// Interpolate the position using the eased time
	float animatedValueX = Lerp(startValueX, endValueX, easedT);
	float animatedValueY = Lerp(startValueY, endValueY, easedT);
	float animatedxover = Lerp(startValueX, endValueXOver, easeT3);
	float animatedyover = Lerp(startValueY, endValueYOver, easeT3);

	float animatedxfont = Lerp(startValueX, endValueXfont, easeT2);
	float animatedyfont = Lerp(startValueY, endValueYfont, easeT2);

	float animatedxquit = Lerp(startValueX, endValueXquit, easeT2);
	float animatedyquit = Lerp(startValueY, endValueYquit, easeT2);

	// Calculate the animated size based on the timer
	float initialSize = 25.0f;
	float animatedSize = Lerp(initialSize, finalSizesquare, easedT);

	CP_Settings_Fill(CP_Color_Create(176, 216, 230, 255));  // Rectangle color
	CP_Graphics_DrawRectAdvanced(animatedValueX, animatedValueY, animatedSize, animatedSize, 0.0f, 100.0f);
	CP_Settings_TextSize(60.0f);
	CP_Settings_Fill(CP_Color_Create(220, 0, 0, 255));
	CP_Font_DrawText("GAME OVER!", animatedxover, animatedyover);

	CP_Settings_TextSize(30.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Your Score is ", animatedxfont, animatedyfont);

	char scoreString[20];
	snprintf(scoreString, sizeof(scoreString), "%d", playerScore);

	CP_Settings_TextSize(30.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText(scoreString, animatedxfont, animatedyfont + 50.f);

	DrawNameInput(playerName, animatedxfont, animatedyfont + 100.f);

	CP_Settings_TextSize(15.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Up arrow key to select to Z.", animatedxquit-100.f, animatedyquit - 200.f);
	CP_Font_DrawText("Down Arrow Key to cycle through characters.", animatedxquit+10.f, animatedyquit - 150.f);
	CP_Font_DrawText("Left and right keys to move to next underscore.", animatedxquit+40.f, animatedyquit - 100.f);
	CP_Font_DrawText("Enter Key to save name.", animatedxquit-138.f, animatedyquit - 50.f);



	CP_Settings_TextSize(25.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 150, 255));
	CP_Font_DrawText("Exit to Main Menu", animatedxquit+50.f, animatedyquit);

	if (errorMessageTimer > 0) {
		errorMessageTimer--;

		// Draw the error message if the timer is still active
		CP_Settings_TextSize(13.0f);
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));  // Red color for error message
		CP_Font_DrawText("Please fill up all 4 characters then press enter!", animatedxquit, animatedyquit - 300.f);
	}

	if (CP_Input_KeyTriggered(KEY_UP)) {
		// Cycle up through the characters
		playerName[activeIndex] = (playerName[activeIndex] == '_') ? 'Z' : (playerName[activeIndex] == 'Z') ? '_' : playerName[activeIndex] + 1;
	}
	else if (CP_Input_KeyTriggered(KEY_DOWN)) {
		// Cycle down through the characters
		playerName[activeIndex] = (playerName[activeIndex] == '_') ? 'A' : (playerName[activeIndex] == 'A') ? '_' : playerName[activeIndex] - 1;
		
	}
	else if (CP_Input_KeyTriggered(KEY_RIGHT)) {
		// Move to the next underscore
		activeIndex = (activeIndex + 1) % (int)strlen(playerName);
		
	}
	else if (CP_Input_KeyTriggered(KEY_LEFT)) {
		// Move to the previous underscore
		activeIndex = (activeIndex - 1 + (int)strlen(playerName)) % (int)strlen(playerName);
		
	}
	if (CP_Input_KeyTriggered(KEY_ENTER)) {
		
		// Check if the name is fully entered (contains no underscores)
		if (strchr(playerName, '_') == NULL) {
			// Name is fully entered, save it and transition to the desired state
			WriteHighScore(playerScore, playerName);
			entryState = NAME_ENTERED;
		
		}
		else {
			errorMessageTimer = errorMessageDuration;
		
		}
	}

	

	CP_Image_Draw(customCursor, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
	if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		{
			if (IsAreaClicked(950.0f, 900.0f, ButtonWidth - 400.0f, ButtonHeight - 350.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Sound_Play(close);
				timer = 0.0f;
				ChangeState(m_Menu);
			}
		}
	}
}

//maybe it will increment the level by points? not sure
void UpdateLevel(void)
{
	m_Level = PlayerScore % 5000;
}

//level system
void Level(void) {
	m_Level = (int)(PlayerScore / 5000) + 1;

	CP_Settings_TextSize(20);
	CP_Font_DrawText("Level: ", 90.f, 120.f);

	char counterlevel[5];
	snprintf(counterlevel, sizeof(counterlevel), "%d", m_Level);

	CP_Settings_Fill(CP_Color_Create(200, 200, 200, 255));
	CP_Font_DrawText(counterlevel, 160.f, 120.0f);
}

//////////////////////////////////////////////////////////////////////////////
//Randomised Gun Menu
/*
@brief	This function will be used to check for player inputs when selecting weapons.
@param	void
@return void
*/
void GunOptionScreen(void) 
{
	if (isGunOptionMenuOpen)
	{
		if (gunMenuTimer > 0)
			gunMenuTimer -= CP_System_GetDt();

		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_ImageMode(CP_POSITION_CENTER);

		RenderWeaponMenu(randWeap1, (float)CP_System_GetWindowWidth() / 2.f - 300.f);
		RenderWeaponMenu(randWeap2, (float)CP_System_GetWindowWidth() / 2.f + 300.f);

		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) && gunMenuTimer <= 0)
		{
			// Left Menu
			if (IsAreaClicked((float)CP_System_GetWindowWidth() / 2 - 300.f, (float)CP_System_GetWindowHeight() / 2,
				300.f, 400.f, CP_Input_GetMouseX(), CP_Input_GetMouseY()))//Click play button
			{
				ChangeWeapon((GunType)randWeap1);
				ToggleGunOptionMenu();
			}
			// Right Menu
			if (IsAreaClicked((float)CP_System_GetWindowWidth() / 2.f + 300.f, (float)CP_System_GetWindowHeight() / 2.f,
				300.f, 400.f, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				ChangeWeapon((GunType)randWeap2);
				ToggleGunOptionMenu();
			}
		}

		CP_Settings_RectMode(CP_POSITION_CORNER);
		CP_Settings_ImageMode(CP_POSITION_CORNER);
	}
}

/*
@brief	This function will be used to toggle the weapon menu and randomise the weapons available to the player.
@param	void
@return void
*/
void ToggleGunOptionMenu(void) {

	if (isGunOptionMenuOpen)
	{
		gunMenuTimer = 2.0f;
		isGunOptionMenuOpen = false;
		isGamePaused = false;
	}
	else isGunOptionMenuOpen = true;

	if (isGunOptionMenuOpen)
	{
		isGamePaused = true;
		randWeap1 = CP_Random_RangeInt(Pistol, SplitShot);
		randWeap2 = CP_Random_RangeInt(Pistol, SplitShot);

		while (randWeap1 == randWeap2)
		{
			randWeap2 = CP_Random_RangeInt(Pistol, SplitShot);
		}
	}
}

/*
@brief	This function will be used render the weapon menu based on the inputted weapon.
@param	int option, float posX
@return void
*/
void RenderWeaponMenu(int option, float posX)
{
	CP_Settings_TextSize(30);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("MAKE YOUR CHOICE", (float)CP_System_GetWindowWidth() / 2, 150);

	switch ((GunType)option)
	{
		case Pistol:
		{
			CP_Settings_TextSize(16.0f);
			CP_Settings_Fill(gunMenuTimer > 0 ? CP_Color_Create(120, 120, 120, 255) : CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(posX, (float)CP_System_GetWindowHeight() / 2, 300.f, 400.f);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Pistol", posX, (float)CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("The Classic", posX, (float)CP_System_GetWindowHeight() / 2 + 100);
			CP_Image_Draw(m_Pistol, posX, (float)CP_System_GetWindowHeight() / 2 - 100, 300.0f, 100.0f, 255);
			break;
		}
		
		case Shotgun:
		{
			CP_Settings_TextSize(16.0f);
			CP_Settings_Fill(gunMenuTimer > 0 ? CP_Color_Create(120, 120, 120, 255) : CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(posX, (float)CP_System_GetWindowHeight() / 2, 300.f, 400.f);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Shotgun", posX, (float)CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("CLOSE COMBAT BABY!", posX, (float)CP_System_GetWindowHeight() / 2 + 100);
			CP_Image_Draw(m_Shotgun, posX, (float)CP_System_GetWindowHeight() / 2 - 100, 300.0f, 100.0f, 255);
			break;
		}

		case Rifle:
		{
			CP_Settings_TextSize(16.0f);
			CP_Settings_Fill(gunMenuTimer > 0 ? CP_Color_Create(120, 120, 120, 255) : CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(posX, (float)CP_System_GetWindowHeight() / 2, 300.f, 400.f);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Rifle", posX, (float)CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("Just an automatic", posX, (float)CP_System_GetWindowHeight() / 2 + 100);
			CP_Image_Draw(m_rifle, posX, (float)CP_System_GetWindowHeight() / 2 - 100, 300.0f, 100.0f, 255);
			break;
		}

		case SplitShot:
		{
			CP_Settings_TextSize(16.0f);
			CP_Settings_Fill(gunMenuTimer > 0 ? CP_Color_Create(120, 120, 120, 255) : CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawRect(posX, (float)CP_System_GetWindowHeight() / 2, 300.f, 400.f);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Split Shot", posX, (float)CP_System_GetWindowHeight() / 2);
			CP_Font_DrawText("The most broken", posX, (float)CP_System_GetWindowHeight() / 2 + 100);
			CP_Image_Draw(m_chargerifle, posX, (float)CP_System_GetWindowHeight() / 2 - 100, 300.0f, 100.0f, 255);
			break;
		}
		
	default:
		break;
	}
}