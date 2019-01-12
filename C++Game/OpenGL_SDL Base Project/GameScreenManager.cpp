#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "MenuScreen.h"
#include "WinScreen.h"
#include "LoseScreen.h"
//--------------------------------------------------------------------------------------------------

GameScreenManager::GameScreenManager(SCREENS startScreen)
{
	mCurrentScreen = NULL;
	mWinScreen = nullptr;
	mLevel1Screen = nullptr;
	mLevel2Screen = nullptr;
	mMenuScreen = nullptr;
	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
	PlayerLives = 0;
}

//--------------------------------------------------------------------------------------------------

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

//--------------------------------------------------------------------------------------------------

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	
	switch (newScreen)
	{

	case SCREEN_MENU:
		mCurrentScreen = (GameScreen*)new MenuScreen(this);
		break;

	case SCREEN_LEVEL1:
		mCurrentScreen = (GameScreen*)new GameScreenLevel1(this);
		break;

	case SCREEN_LEVEL2:
		mCurrentScreen = (GameScreen*)new GameScreenLevel2(this);
		break;
	case SCREEN_ENDGAME:
		mCurrentScreen = (GameScreen*)new WinScreen(this);
		break;

	case SCREEN_LOSE:
		mCurrentScreen = (GameScreen*)new LoseScreen(this);
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------