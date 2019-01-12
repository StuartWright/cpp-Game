#include"MenuScreen.h"
#include "../gl/glut.h"
#include <SDL.h>
MenuScreen::MenuScreen(GameScreenManager* gsManager) : GameScreen(gsManager) {
	mMenuItems.push_back("Level 1");
	mMenuItems.push_back("Level 2");
	mMenuItems.push_back("Exit");
	if (mMenuItems.size() != 0) {
		selected = MENU_LEVEL1;
	}
	mInstructions.push_back("Use arrow keys to navigate menu");
	mInstructions.push_back("Enter to select");
}
void MenuScreen::Render() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int i;
	for (i = 0; i< mMenuItems.size(); i++)
	{
		if (i == selected) 
		{
			glColor3f(1.0f, 0.4f, 0.0f);
		}
		else 
		{
			glColor3f(0.0, 0.0, 0.0);
		}
		OutputLine(30, 80 - 10 * i, mMenuItems[i]);
	}
	for (int j = 0; j < mInstructions.size(); j++)
	{
		glColor3f(0.0, 0.0, 0.0);
		OutputLine(20, 70 - 10 * j - 10 * i, mInstructions[j]);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
void MenuScreen::Update(float deltaTime, SDL_Event e) 
{
	HandleInput(e);
}

void MenuScreen::HandleInput(SDL_Event e) 
{
	switch (e.type) 
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (selected > 0) 
			{
				selected = selected - 1;
			}
			break;
		case SDLK_DOWN:
			if (selected < mMenuItems.size() - 1)
			{
				selected++;
			}
			break;

		case SDLK_RETURN:
			HandleSelectedItem();
			break;
		}
	}
}
void MenuScreen::HandleSelectedItem()
{
	if (selected == 0)
	{
		gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
	}
	else if (selected == 1)
	{
		gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
	}
	else if (selected == 2)
	{
		SDL_Quit();
	}
	
	
	
}

void MenuScreen::OutputLine(float x, float y, string text)
{
	
	float xCenterPos = x - (text.size() / 3);
	glRasterPos2f(xCenterPos, y);//where to start drawing

	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);

	}
	
}
