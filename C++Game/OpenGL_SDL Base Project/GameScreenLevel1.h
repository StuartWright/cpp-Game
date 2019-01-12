#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

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

class GameScreenLevel1 : GameScreen
{
//--------------------------------------------------------------------------------------------------
public:
	GameScreenLevel1(GameScreenManager* gsManager);
	~GameScreenLevel1();

	bool		SetUpLevel();
	void		Render();
	void		Update(float deltaTime, SDL_Event e);
	void SetLight();
	void SetMaterial();
	int Lives;
	//Sphere * GetBoundingSphere();
//--------------------------------------------------------------------------------------------------
private:
	//vector<Object3DS *> TheBalls;
	
	Object3DS* BallModel;
	vector<Object3DS*> TheBalls;
	Object3DS* GuyModel;
	Object3DS* Floor;
	Object3DS* Floor2;
	float mCurrentTime = 0;
	Pyramid * pyramid;
	Camera* m_Camera;
	float rotation;
	int randomNum;
	void Sound();
	vector<float> BallOffset;
	Vector3D currentPos;
    Object3DS* texture;

	int ballCaught = 0;
	
	
};


#endif //_GAMESCREENLEVEL1_H