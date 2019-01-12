#include "Camera.h"
#include "Constants.h"
#include <math.h>
#include "../gl/glut.h"
#include"GameScreenLevel1.h"
static Camera* instance = 0;
static float moveSpeed = 0.2f;
static float lookSpeed = 0.2f;
Camera::Camera()
{

}
Camera::~Camera()
{

}
Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}
	return instance;
}
void Camera::Update(float deltaTime, SDL_Event e)
{
	
	forward = Vector3D(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw));
	// Right vector
	right = Vector3D(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));
	
	up = Vector3D((right.y*forward.z) - (right.z*forward.y),
		(right.z*forward.x) - (right.x*forward.z),
		(right.x*forward.y) - (right.y*forward.x));
	
}
void Camera::Render()
{
	Vector3D lookatPos = position + forward;
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y,
		lookatPos.z, up.x, up.y, up.z);

}