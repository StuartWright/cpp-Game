#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>
#include <vector>
#include "Commons.h"
#include "GameScreen.h"

class GameScreen;

class GameScreenManager
{

public:
	GameScreenManager(SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
	int PlayerLives;

private:
	GameScreen* mCurrentScreen;
	GameScreen* mWinScreen;
	GameScreen* mLevel1Screen;
	GameScreen* mLevel2Screen;
	GameScreen* mMenuScreen;
	GameScreen* mLoseScreen;
};


#endif _GAMESCREENMANAGER_H