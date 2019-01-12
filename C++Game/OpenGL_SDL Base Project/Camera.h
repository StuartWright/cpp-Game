#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include "Commons.h"
#include <SDL.h>
class Camera 
{
	
public: Camera();
		~Camera();
		static Camera* GetInstance(); 
		void Update(float deltaTime, SDL_Event e);
		void Render();
		Vector3D position = Vector3D(15, 350, 9);
private:
	
	Vector3D forward = Vector3D();
	Vector3D up = Vector3D();
	Vector3D right = Vector3D();
	float yaw = 3.14f;
	float pitch = -1.1;
};
#endif //_CAMERA_H