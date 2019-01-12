#pragma once
#ifndef _LOSESCREEN_H
#define _LOSTSCREEN_H

#include <SDL.h>
#include "../gl/glut.h"
#include "GameScreen.h"
#include <vector>
#include <iostream>
#include "GameScreenManager.h"
using namespace std;
class LoseScreen : GameScreen
{
public:
	LoseScreen(GameScreenManager* gsm);
	~LoseScreen();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	vector<string> mMenuItems;
	vector<string> mInstructions;
	int selected = 0;
	void HandleInput(SDL_Event e);
	void OutputLine(float x, float y, string text);
	void HandleSelectedItem();
};

#endif _LOSESCREEN_H
