#include "LoseScreen.h"



LoseScreen::LoseScreen(GameScreenManager* gsm) : GameScreen(gsm)
{

	mMenuItems.push_back("You Lose");
	mMenuItems.push_back("Main Menu");
	selected = 0;
}


LoseScreen::~LoseScreen()
{
}

void LoseScreen::Update(float deltaTime, SDL_Event e)
{
	HandleInput(e);
}
void LoseScreen::HandleInput(SDL_Event e)
{
	switch (e.type) {
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {

		case SDLK_RETURN:
			HandleSelectedItem();
			break;
		}
	}

}

void LoseScreen::HandleSelectedItem()
{
	switch (selected)
	{
	case 0:
		gameScreenManager->ChangeScreen(SCREEN_MENU);
		break;
	}


}

void LoseScreen::Render()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	//enable Texture
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_NORMALIZE);

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
		if (i == selected) {
			glColor3f(1.0f, 0.0f, 0.0f);
		}
		else {
			glColor3f(0.0, 0.0, 0.0);
		}
		OutputLine(30, 80 - 10 * i, mMenuItems[i]);
	}
	for (int j = 0; j < mInstructions.size(); j++) {
		glColor3f(0.0, 0.0, 0.0);
		OutputLine(20, 70 - 10 * j - 10 * i, mInstructions[j]);
	}

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void LoseScreen::OutputLine(float x, float y, string text)
{
	float xCenterPos = x - (text.size() / 3);
	glRasterPos2f(xCenterPos, y);//where to start drawing

	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
	}

}