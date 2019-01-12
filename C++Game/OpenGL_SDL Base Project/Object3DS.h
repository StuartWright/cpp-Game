#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_
#include "Commons.h"
#include <string>
#include "Texture2D.h"
#include <SDL.h>
#include "Collision.h"
using std::string;
class Sphere;
class Object3DS 
{
public: Object3DS(Vector3D startPosition, string modelFileName, Vector3D BeginVelocity);
		~Object3DS() {}
		void update(float deltaTime, SDL_Event e);
		void render();
		//Load 3ds file 
		void loadModel();
		//Load texture for this model. 
		void loadTexture(char* path, int width, int height);
		Sphere * GetBoundingSphere();
		Vector3D velocity;
		Vector3D mPosition;
		Vector3D rotation;
		Vector3D Scale = Vector3D(1, 1, 1);
		string name = "Default";
		bool hasCollided = false;
		bool hasCollision = true;
		Sphere * boundingSphere;
		bool IsLevel1 = true;
		float BallsStacked;
private: 
	
		 char fileName[20];
		 char textureName[20];
		 obj_type object;
		 float angle;
		 float StartY;
		 float scale;
		 float SpawnDelay;
		 bool isCaught;
		 Vector3D initalVelocity;
		 Vector3D initalPosition;
		 
};
#endif //_OBJECT3DS_H_
