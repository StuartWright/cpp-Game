#include "GameScreen.h"
#include "../gl/glut.h"
#include <SDL.h>
#include "Constants.h"
//--------------------------------------------------------------------------------------------------

GameScreen::GameScreen(GameScreenManager* gsManager)
{
	gameScreenManager = gsManager;
}

//--------------------------------------------------------------------------------------------------

GameScreen::~GameScreen()
{
}

void GameScreen::ScreenText(float x, float y, string text)
{
	glColor3f(0, 0, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);


	glRasterPos2f(x, y);

	for (unsigned int i = 0; i < text.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
}
//--------------------------------------------------------------------------------------------------

void GameScreen::Render()
{
}

//--------------------------------------------------------------------------------------------------

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}

//--------------------------------------------------------------------------------------------------