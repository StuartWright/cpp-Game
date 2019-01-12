#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include <SDL.h>
#include "GameScreen.h"
#include "pryamid.h"
#include "Object3DS.h"
#include "Camera.h"
#include "Collision.h"
#include "GameScreenManager.h"
#include <vector>
using namespace std;

class Object3DS;
class Sphere;

class GameScreenLevel2 : GameScreen
{
	//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel2(GameScreenManager* gsManager);
	~GameScreenLevel2();

	bool	SetUpLevel();
	void	Render();
	void	Update(float deltaTime, SDL_Event e);
	void SetLight();
	void SetMaterial();
	int Lives;
	//--------------------------------------------------------------------------------------------------
private:
	
	Object3DS * BallModel;
	vector<Object3DS*> TheBalls;
	Object3DS* GuyModel;
	Object3DS* Ball;
	Object3DS* Floor;
	float mCurrentTime = 0;
	Pyramid * pyramid;
	Camera* m_Camera;
	float rotation;
	int randomNum;
	float Turn;
	void Sound();
	vector<float> BallOffset;
	Vector3D currentPos;
	Object3DS* texture;

	int ballCaught = 0;

};


#endif //_GAMESCREENLEVEL2_H