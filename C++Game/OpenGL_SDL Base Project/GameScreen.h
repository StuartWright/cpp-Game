#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <string>
class GameScreenManager;
using namespace std;
class GameScreen
{
public:
	GameScreen(GameScreenManager* gsManager);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

protected:

	GameScreenManager * gameScreenManager;
	void GameScreen::ScreenText(float x, float y, string text);
};


#endif //_GAMESCREEN_H