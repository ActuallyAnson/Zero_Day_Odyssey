//All content © 2023 DigiPen Institute of Technology Singapore, all rights reserved.

/*!
@file     SceneMainMenu.c
@author   Anson (anson.t)
@secondary author Aqif (muhammadnuraqif.b) - ReadHighscore
@course   csd1401
@section  B
@Project  Zero Day Odessey
@date     14/11/2023
@brief    Loading of Game Menu
*//*______________________________________________________________________*/
#include "Scene_MainMenu.h"
#include "StateManager.h"
#include "Utils_Settings.h"


//////////////////////////////////////////////////////////////////////////////
//Init Menu
void Main_Menu_Init(void)
{
	ReadMusicVolume();
	
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_MIDDLE);
	//Setting of font
	myFont = CP_Font_Load("Assets/PressStart2P-Regular.ttf");
	Clickables = CP_Font_Load("Assets/BigShouldersText.ttf");
	ScoreboardFont = CP_Font_Load("Assets/ScoreBoardFont.ttf");
	NeonFont = CP_Font_Load("Assets/NeonFont.ttf");
	
	//Pngs
	backgroundImage = CP_Image_Load("Assets/BlackBackground.png");
	customCursor = CP_Image_Load("Assets/cursor_pointerFlat.png");
	WindowsPopUp = CP_Image_Load("Assets/WindowsPopUp.png");
	Leaderboardpopup = CP_Image_Load("Assets/Leaderboard.png");
	RightArrow = CP_Image_Load("Assets/RightArrow.png");
	knobImage = CP_Image_Load("Assets/RedKnob.png");
	Credit = CP_Image_Load("Assets/Credits.png");

	
	
	//sound
	Confirm = CP_Sound_Load("Assets/confirmation_003.ogg");
	Hover = CP_Sound_Load("Assets/Hover.ogg");
	BGM = CP_Sound_LoadMusic("Assets/BGM.mp3");


	//Buttons
	ButtonWidth = 700;
	ButtonHeight = 200;

	//Mouse 
	mouseX = CP_Input_GetMouseX();
	mouseY = CP_Input_GetMouseY();


	//position of buttons
	ButtonPosX = (float) CP_System_GetWindowWidth() / 2;
	ButtonPosY = (float) CP_System_GetWindowHeight() / 2;

	//Sound Slider 
	volumeSliderWidth = 400.0f;
	volumeSliderHeight = 40.0f;
	volumeSliderX = (float)CP_System_GetWindowWidth() / 2 - volumeSliderWidth / 2;
	volumeSliderY = (float)CP_System_GetWindowHeight() / 2 - volumeSliderHeight / 2;

	//float store = ReadMusicVolume();

	volume = fmaxf(0, fminf(100, volume)); //to make sure it stays from 0 to 100

	knobPositionX = volumeSliderX + (volume / 100.0f) * (volumeSliderWidth - 20.0f); // Adjusted position calculation
	knobPositionX = fmaxf(volumeSliderX, fminf(knobPositionX, volumeSliderX + volumeSliderWidth - 20.0f));


	volumeText[0] = (volumeInt / 100) + '0'; // Hundreds digit
	volumeText[1] = ((volumeInt / 10) % 10) + '0'; // Tens digit
	volumeText[2] = (volumeInt % 10) + '0'; // Ones digit
	volumeText[3] = '\0'; // Null terminator
	
	//set enum of pop-up by default
	popUpStatus = None;
	CP_Sound_PlayAdvanced(BGM, getterSoundVolume()/100.0f, 1.0f, TRUE, CP_SOUND_GROUP_1);
}

//////////////////////////////////////////////////////////////////////////////
//Update Menu
void Main_Menu_Update(void)
{
	slider();
	Main_Menu_Render();
	CheckButtonCollision();
}

//////////////////////////////////////////////////////////////////////////////
//Render Menu
void Main_Menu_Render(void) {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 0));
	CP_Image_Draw(backgroundImage, 0.0f, 0.0f, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(), 255);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	//////////////////////////////////////////////////////////////////////////////
	//Rendering of Text

	//Game Name
	CP_Font_Set(myFont);
	CP_Settings_TextSize(80.0f);
	CP_Font_DrawText("Zero", ButtonPosX - 600, ButtonPosY - 100);
	CP_Font_DrawText("Day", ButtonPosX - 600, ButtonPosY);
	CP_Font_DrawText("Odyssey", ButtonPosX - 600, ButtonPosY + 100);

	//CLickables
	CP_Font_Set(Clickables);
	CP_Settings_TextSize(100.0f);
	CP_Font_DrawText("Start Game", ButtonPosX + 200.0f, ButtonPosY - 300.0f); //Additional float values are to center the text on the button.(Play)
	CP_Font_DrawText("Options", ButtonPosX + 200.0f, ButtonPosY - 150.0f);
	CP_Font_DrawText("Leaderboard", ButtonPosX + 200.0f, ButtonPosY);
	CP_Font_DrawText("Credits", ButtonPosX + 200.0f, ButtonPosY + 150.0f); //change later
	CP_Font_DrawText("Quit Game", ButtonPosX + 200.0f, ButtonPosY + 300.0f); //Additional float values are to center the text on the button.(Exit)


	//play
	if (isTextHovered = isAreaHovered(ButtonPosX + 200.0f, ButtonPosY - 335.0f, ButtonWidth, ButtonHeight-100)) {

		arrowX = ButtonPosX + 150.0f;
		arrowY = ButtonPosY - 315.0f;
		RightArrowW = (float)CP_Image_GetWidth(RightArrow);
		RightArrowH = (float)CP_Image_GetHeight(RightArrow);
		CP_Image_Draw(RightArrow, arrowX, arrowY, RightArrowW, RightArrowH, 255);
	}

	//options
	else if (isTextHovered = isAreaHovered(ButtonPosX + 200.0f, ButtonPosY - 200.0f, ButtonWidth, ButtonHeight - 100)) {

		arrowX = ButtonPosX + 150.0f; // Position the arrow to the left of the text
		arrowY = ButtonPosY - 170.0f; // Adjust Y position as needed
		RightArrowW = (float)CP_Image_GetWidth(RightArrow);
		RightArrowH = (float)CP_Image_GetHeight(RightArrow);
		CP_Image_Draw(RightArrow, arrowX, arrowY, RightArrowW, RightArrowH, 255);
	}

	//Leaderboard
	else if (isTextHovered = isAreaHovered(ButtonPosX + 200.0f, ButtonPosY - 50.0f, ButtonWidth, ButtonHeight - 100)) {

		arrowX = ButtonPosX + 150.0f; // Position the arrow to the left of the text
		arrowY = ButtonPosY - 15.0f; // Adjust Y position as needed
		RightArrowW = (float)CP_Image_GetWidth(RightArrow);
		RightArrowH = (float)CP_Image_GetHeight(RightArrow);
		CP_Image_Draw(RightArrow, arrowX, arrowY, RightArrowW, RightArrowH, 255);
	}

	//credits
	else if (isTextHovered = isAreaHovered(ButtonPosX + 200.0f, ButtonPosY +100.0f, ButtonWidth, ButtonHeight - 100)) {

		arrowX = ButtonPosX + 150.0f; // Position the arrow to the left of the text
		arrowY = ButtonPosY + 140.0f; // Adjust Y position as needed
		RightArrowW = (float)CP_Image_GetWidth(RightArrow);
		RightArrowH = (float)CP_Image_GetHeight(RightArrow);
		CP_Image_Draw(RightArrow, arrowX, arrowY, RightArrowW, RightArrowH, 255);
	}

	//Exit
	else if (isTextHovered = isAreaHovered(ButtonPosX + 200.0f, ButtonPosY + 250.0f, ButtonWidth, ButtonHeight - 100)) {

		arrowX = ButtonPosX + 150.0f; // Position the arrow to the left of the text
		arrowY = ButtonPosY + 295.0f; // Adjust Y position as needed
		RightArrowW = (float)CP_Image_GetWidth(RightArrow);
		RightArrowH = (float)CP_Image_GetHeight(RightArrow);
		CP_Image_Draw(RightArrow, arrowX, arrowY, RightArrowW, RightArrowH, 255);
	}

		//if enum = 1 draw setting. 2 is draw leaderboard
	if (popUpStatus == Settings)
	{
		crossButtonX = (ButtonPosX / 4) + 50;
		crossButtonY = (ButtonPosY / 4) + 40;
		crossButtonWidth = 75;
		crossButtonHeight = 75;

		PopUpWidth = (float)CP_Image_GetWidth(WindowsPopUp);
		PopUpHeight = (float)CP_Image_GetHeight(WindowsPopUp);
		CP_Image_Draw(WindowsPopUp, ButtonPosX / 4 + 50.0f, ButtonPosY / 4, PopUpWidth / 1.5f + 50.0f, PopUpHeight / 1.5f, 255);

		//rectangle is able to draw
		CP_Graphics_DrawRect(volumeSliderX, volumeSliderY, volumeSliderWidth, volumeSliderHeight);
		CP_Image_Draw(knobImage, knobPositionX, volumeSliderY, 20.0f, volumeSliderHeight,255);
		
		//change size and font next 
		CP_Font_DrawText("BGM", volumeSliderX - 150, volumeSliderY);
		CP_Font_DrawText(volumeText, volumeSliderX + volumeSliderWidth + 20, volumeSliderY);
		
		//close button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {

			// Close the pop-up menu (set isPopupMenuOpen to 0)
			if (isAreaHovered(crossButtonX + 10, crossButtonY - 50, crossButtonWidth, crossButtonHeight)) {
				popUpStatus = None;
			}
		}
	}
	// pop-up for leaderboards
	else if (popUpStatus == Leaderboard)
	{

		LBcrossButtonX = (ButtonPosX / 4) + 400;
		LBcrossButtonY = (ButtonPosY / 4) - 100;
		LBcrossButtonWidth = 120;
		LBcrossButtonHeight = 120;
		
		LeaderboardW = (float)CP_Image_GetWidth(Leaderboardpopup);
		LeaderboardH = (float)CP_Image_GetHeight(Leaderboardpopup);
		CP_Image_Draw(Leaderboardpopup, ButtonPosX - 300, 50, LeaderboardW - 100, LeaderboardH - 100, 255);
			
		ReadHighScores();


		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {

			//Close the pop-up menu (set isPopupMenuOpen to 0)
			if (isAreaHovered(LBcrossButtonX, LBcrossButtonY, LBcrossButtonWidth, LBcrossButtonHeight)) {
			popUpStatus = None;
			}
		}

	}

	if (popUpStatus == Credits)
	{

		CreditWidth = (float)CP_Image_GetWidth(Credit);
		CreditHeight = (float)CP_Image_GetHeight(Credit);
		CP_Image_Draw(Credit,0,0, CreditWidth, CreditHeight,255);
		

		//close button
		if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {

			// Close the pop-up menu using the back button later (set isPopupMenuOpen to 0) 
			if (isAreaHovered(ButtonPosX - 100, ButtonPosY + 200, 200, 100)) {
				popUpStatus = None;
			}
		}
	}

	cursorWidth = (float)CP_Image_GetWidth(customCursor);
	cursorHeight = (float)CP_Image_GetHeight(customCursor);
	CP_Image_Draw(customCursor, CP_Input_GetMouseX(), CP_Input_GetMouseY(), cursorWidth, cursorHeight, 255);
}

//////////////////////////////////////////////////////////////////////////////
//Exit Menu
void Main_Menu_Exit(void)
{

	UI_Exit();
	//Free Images
	CP_Image_Free(&customCursor);
	CP_Image_Free(&backgroundImage);
	CP_Image_Free(&WindowsPopUp);
	CP_Image_Free(&RightArrow);
	CP_Image_Free(&knobImage);
	CP_Image_Free(&Leaderboardpopup);

	CP_Sound_Free(&Hover);
	CP_Sound_Free(&Confirm);
	CP_Sound_Free(&BGM);
}

///ButtonCollisions 
void CheckButtonCollision(void)
{
	if (!isPopupMenuOpen) {

		if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
			//play
			if (IsAreaClicked(ButtonPosX + 500.0f, ButtonPosY - 300.0f, ButtonWidth, ButtonHeight - 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))//Click play button
			{
				CP_Sound_PlayAdvanced(Confirm, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_2);
					ChangeState(m_Game);
			}

			// Settings
			else if (IsAreaClicked(ButtonPosX + 500.0f, ButtonPosY - 150.0f, ButtonWidth, ButtonHeight - 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Sound_Play(Confirm);
				popUpStatus = Settings;
			}

			//leaderboard
			else if (IsAreaClicked(ButtonPosX + 500.0f, ButtonPosY, ButtonWidth, ButtonHeight - 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Sound_PlayAdvanced(Confirm, 1.0f, 1.0f, FALSE, CP_SOUND_GROUP_2);
				popUpStatus = Leaderboard;
			}

			//Credits 
			else if (IsAreaClicked(ButtonPosX + 500.0f, ButtonPosY + 150.0f, ButtonWidth, ButtonHeight - 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))//Click exit button
			{
				CP_Sound_Play(Confirm);
				popUpStatus = Credits;
			}

			//exit
			else if (IsAreaClicked(ButtonPosX + 500.0f, ButtonPosY + 300.0f, ButtonWidth, ButtonHeight - 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))//Click exit button
			{
				CP_Sound_Play(Confirm);
				CP_Engine_Terminate();
			}
		}
	}
}


void slider(void) {
	if (CP_Input_MouseDragged(MOUSE_BUTTON_LEFT)) {
		if (CP_Input_GetMouseX() >= knobPositionX && CP_Input_GetMouseX() <= (knobPositionX + 20.0f) &&
			CP_Input_GetMouseY() >= volumeSliderY && CP_Input_GetMouseY() <= (volumeSliderY + volumeSliderHeight)) {
			isDragging = true;
		}
	}

	if (isDragging && CP_Input_MouseReleased(MOUSE_BUTTON_LEFT)) {
		isDragging = false;
	}

	if (isDragging) {
		knobPositionX = fmaxf(volumeSliderX, fminf(CP_Input_GetMouseX() - 10.0f, volumeSliderX + volumeSliderWidth - 20.0f));
		volume = ((knobPositionX - volumeSliderX) / (volumeSliderWidth - 20.0f)) * 100.0f;
		

	}

	//Chnage back
	setVolume(volume);

	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_1, getterSoundVolume());
	volumeInt = (int)volume;

	if (volumeInt >= 100) {
		volumeText[0] = (volumeInt / 100) + '0'; // Hundreds digit
		volumeText[1] = ((volumeInt / 10) % 10) + '0'; // Tens digit
		volumeText[2] = (volumeInt % 10) + '0'; // Ones digit
		volumeText[3] = '\0'; // Null terminator
	}

	else if (volumeInt >= 10) {
		volumeText[0] = (volumeInt / 10) + '0'; // Tens digit
		volumeText[1] = (volumeInt % 10) + '0'; // Ones digit
		volumeText[2] = '\0'; // Null terminator
	}

	else {
		volumeText[0] = volumeInt + '0'; // Ones digit
		volumeText[1] = '\0'; // Null terminator
	}
	
}


bool isAreaHovered(float x, float y, float width, float height) { //can be used for crossbutton for pop-up 
	 mouseX = CP_Input_GetMouseX();
	 mouseY = CP_Input_GetMouseY();

	// Check if the cursor is within the specified area
	if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height) {
		return true; // Cursor is in the area
	}
	else {
		return false; // Cursor is not in the area
	}
}



float ReadMusicVolume(void) {
	volume = getterSoundVolume();
	FILE* configFile;
	errno_t err;
	err = fopen_s(&configFile, "Assets/config.txt", "r+");
	if (err != 0) {
		fopen_s(&configFile, "Assets/config.txt", "w");
		//check if this is volumeint or volume'
		return volume;
	}

	if (fgets(volumeText, sizeof(volumeText), configFile) != NULL) {
		volumeInt = (int)atof(volumeText); 
		fclose(configFile);
		return volume;
	}

	return 0;
}

struct ScoreEntry {
	char name[5]; 
	int score;
};

void ReadHighScores() {
	FILE* file;
	fopen_s(&file, "Assets/highscore.txt", "r");
	if (file) {
		struct ScoreEntry {
			char name[20]; 
			int score;
		};

		struct ScoreEntry scores[100] = {0}; // Assuming there are at most 100 scores in the file
		int count = 0;

		// Read names and scores from the file
		while (count < 100) {
			// Read a line from the file
			char line[256]; 
			if (fgets(line, sizeof(line), file) == NULL) {
				break; 
			}

			//  parse the name and score from the line
			if (sscanf_s(line, "%19s %d", scores[count].name, 19, &scores[count].score) == 2) {
				count++;
			}
		}

		// Close the file
		fclose(file);

		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {
				if (scores[j].score < scores[j + 1].score) {
					// Swap scores[j] and scores[j + 1]
					struct ScoreEntry temp = scores[j];
					scores[j] = scores[j + 1];
					scores[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < (count < 5 ? count : 5); i++) {
			char scoreText[20];
			sprintf_s(scoreText, sizeof(scoreText), "%s, %d", scores[i].name, scores[i].score);
			CP_Font_Set(NeonFont);
			CP_Settings_TextSize(30.0f);
			CP_Font_DrawText(scoreText, ButtonPosX - 120, 280 + (float)i * 145.0f);
		}
	}
	else {
		// Handle file open error
	}
}



