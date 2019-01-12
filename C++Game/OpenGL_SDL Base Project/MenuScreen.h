#pragma once
#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include <vector>
#include <string>
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "SDL.h"
using namespace std;

#define MENU_NONE -1
#define MENU_LEVEL1 0
#define MENU_LEVEL2 1
#define MENU_EXIT   2 
class MenuScreen : public GameScreen {
public:
	MenuScreen(GameScreenManager* gsManager);
	~MenuScreen() {};
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void OutputLine(float x, float y, string text);
protected:
	void HandleInput(SDL_Event e);
	vector<string> mInstructions;
	vector<string> mMenuItems;
private:
	int selected = MENU_NONE;
	void HandleSelectedItem();
	//GameScreenManager* Manager;
	
};
#endif
