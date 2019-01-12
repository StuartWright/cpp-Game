#pragma once
#ifndef _WINSCREEN_H
#define _WINSCREEN_H

#include <SDL.h>
#include "../gl/glut.h"
#include "GameScreen.h"
#include <vector>
#include <iostream>
#include "GameScreenManager.h"
#include "GameScreenLevel1.h"
using namespace std;
class WinScreen : GameScreen
{
public:
	WinScreen(GameScreenManager* gsm);
	~WinScreen();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	vector<string> mMenuItems;
	vector<string> mInstructions;
	GameScreenLevel1* GS;
	int selected = 0;
	void HandleInput(SDL_Event e);
	void OutputLine(float x, float y, string text);
	void HandleSelectedItem();
};

#endif _WINSCREEN_H

