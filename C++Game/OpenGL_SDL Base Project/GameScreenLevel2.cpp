#include "GameScreenLevel2.h"
#include <time.h>
#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include "../gl/glut.h"
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "iostream"
#include "Collision.h"
#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <ctime>
#include "Object3DS.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

GameScreenLevel2::GameScreenLevel2(GameScreenManager* gsManager) : GameScreen(gsManager)
{

	Lives = 0;
	pyramid = new Pyramid();
	rotation = 30.0f;
	gameScreenManager->PlayerLives = Lives;

	GuyModel = new Object3DS(Vector3D(0.0f, 0.0f, 2.0f), "myBall.3ds", Vector3D(100.0f, 100.0f, 100.0f));
	GuyModel->rotation = Vector3D(-90, 0, -180);
	GuyModel->Scale = Vector3D(1.0f, 1.0f, 1.0f);
	GuyModel->name = "GuyModel";
	GuyModel->loadTexture("benTexturee.bmp", 512, 512);

	Ball = new Object3DS(Vector3D(GuyModel->mPosition.x, GuyModel->mPosition.y, GuyModel->mPosition.z), "DodgeBall.3ds", Vector3D(0.0f, 0.0f, -100.0f));
	Ball->loadTexture("Tiles.bmp", 512, 512);
	Ball->rotation = Vector3D(90, 0, 0);
	Ball->IsLevel1 = false;
	Ball->Scale = Vector3D(0.5f, 0.5f, 0.5f);

	Floor = new Object3DS(Vector3D(0.0f, -5.0f, -50.0f), "Floor.3ds", Vector3D(0.0f, 0.0f, 0.0f));
	Floor->rotation = Vector3D(-90, 0, 0);
	Floor->hasCollision = false;
	Floor->loadTexture("Court.bmp", 512, 512);
	Floor->Scale = Vector3D(5.0f, 3.0f, 0.5f);

	for (int i = 0; i < 10; i++)
	{
		
		float posX = (rand() % 130) + 1;
		TheBalls.push_back(new Object3DS(Vector3D(posX, 2.0f, -100), "Target.3ds", Vector3D(1, 0, 0)));
		TheBalls[i]->rotation = Vector3D(-90, 0, -180);
		TheBalls[i]->loadTexture("Blue.bmp", 1024, 1024);
		TheBalls[i]->Scale = Vector3D(0.1f, 0.1f, 0.1f);

	}
	
	m_Camera = m_Camera->GetInstance();
	srand(time(NULL));

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	gluPerspective(60.0f, aspect, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);								//Stop calculation of inside faces
	glEnable(GL_DEPTH_TEST);							//Hidden surface removal

														//clear background colour.
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);


	//enables the lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	//enable Texture
	glEnable(GL_TEXTURE_2D);


}



//--------------------------------------------------------------------------------------------------

GameScreenLevel2::~GameScreenLevel2()
{
	for (size_t i = 0; i < TheBalls.size(); i++)
	{
		delete TheBalls[i];
		TheBalls[i] = nullptr;
	}
	TheBalls.clear();
}

//--------------------------------------------------------------------------------------------------


bool GameScreenLevel2::SetUpLevel()
{
	return true;
}

void GameScreenLevel2::Render()
{
	//Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle;
	glColor3f(0.2f, 0.2f, 0.2f);
	SetLight();

	glEnable(GL_NORMALIZE);

	for (int i = 0; i < TheBalls.size(); i++)
	{
		TheBalls[i]->render();
	}


	GuyModel->render();

	Floor->render();
	
	Ball->render();
	
	
	m_Camera->Render();
	glRotatef(-50.0f, 1.0f, 0.0f, 0.0f);
	m_Camera->position.y = 100;

	std::string lives = std::to_string(Lives);
	GameScreen::ScreenText(SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, "Targets to hit: 10/ " + lives);
}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	mCurrentTime += deltaTime;
	m_Camera->position.x = GuyModel->mPosition.x;
	GuyModel->boundingSphere->SetCollided(false);
	
	
	Ball->update(deltaTime, e);
	
	for (auto i = 0; i <TheBalls.size(); i++)
	{
		TheBalls[i]->boundingSphere->SetCollided(false);
		TheBalls[i]->mPosition.x += TheBalls[i]->velocity.x;
		//TheBalls[i]->update(deltaTime, e);
		if (TheBalls[i]->mPosition.x >= 150.0f)
		{
			TheBalls[i]->velocity = Vector3D(-1.0f, 0.0f, 0.0f);
		}
		if (TheBalls[i]->mPosition.x <= -70.0f)
		{
			TheBalls[i]->velocity = Vector3D(1.0f, 0.0f, 0.0f);
		}
		if (Collision::SphereSphereCollision(TheBalls[i]->GetBoundingSphere(), Ball->GetBoundingSphere()) && TheBalls[i]->hasCollision)
		{
			Lives++;
			TheBalls[i]->mPosition.y -= 40;
			Ball->mPosition.y = 1000;
			Ball->velocity.z = 0;
			PlaySound(TEXT("Scream.wav"), NULL, SND_ASYNC);
		}

		TheBalls[i]->boundingSphere->Update(TheBalls[i]->mPosition);
	}
	Ball->boundingSphere->Update(Ball->mPosition);
	GuyModel->boundingSphere->Update(GuyModel->mPosition);

	mCurrentTime += deltaTime;
	m_Camera->Update(deltaTime, e);
	
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Ball->mPosition.x = GuyModel->mPosition.x;
			Ball->mPosition.y = GuyModel->mPosition.y;
			Ball->mPosition.z = GuyModel->mPosition.z;
			Ball->velocity = Vector3D(0.0f, 0.0f, -100);
			break;
		case SDLK_d:
			GuyModel->mPosition.x += GuyModel->velocity.x * deltaTime;

			break;
		case SDLK_a:
			GuyModel->mPosition.x -= GuyModel->velocity.x * deltaTime;

			break;
		}
	}

	if (GuyModel->mPosition.x < -100)
	{
		GuyModel->mPosition.x = -100;
	}
	if (GuyModel->mPosition.x > 120)
	{
		GuyModel->mPosition.x = 120;
	}
	if (Lives >= 10)
	{
		PlaySound(TEXT("Win.wav"), NULL, SND_ASYNC);
		gameScreenManager->ChangeScreen(SCREEN_ENDGAME);
		
		return;
	}



}

//--------------------------------------------------------------------------------------------------
void GameScreenLevel2::SetLight()
{
	lighting light =
	{
		{ 5.2f, 5.2f, 5.2f, 5.0f },
	{ 1.7f, 1.7f, 1.7f, 1.0f },
	{ 1.5f, 1.5f, 1.5f, 1.0f }
	};
	
	float light_pos[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}
void GameScreenLevel2::SetMaterial() {
	material material = {
		{ 0.80f, 0.05f, 0.05f, 1.0f },
	{ 0.80f, 0.05f, 0.05f, 1.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f },
	100.0f
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, material.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material.diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, material.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, material.shininess);
}