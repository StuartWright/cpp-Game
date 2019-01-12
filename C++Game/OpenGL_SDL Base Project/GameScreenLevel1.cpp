#include "GameScreenLevel1.h"
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

GameScreenLevel1::GameScreenLevel1(GameScreenManager* gsManager) : GameScreen(gsManager)
{
	
	
	Lives = 4;
	pyramid = new Pyramid();
	rotation = 30.0f;
	gameScreenManager->PlayerLives = Lives;
	
	
	GuyModel = new Object3DS(Vector3D(-210.0f, 0.0f, -30.0f), "myBall.3ds", Vector3D(100.0f, 100.0f, 100.0f));
	GuyModel->rotation = Vector3D(-90, 0, -180);
	GuyModel->Scale = Vector3D(1.0f, 1.0f, 1.0f);

	GuyModel->name = "GuyModel";
	GuyModel->loadTexture("benTexturee.bmp", 512, 512);
	

	Floor = new Object3DS(Vector3D(-150.0f, -10.0f, -172.0f), "Floor.3ds", Vector3D(0.0f, 0.0f, 0.0f));
	Floor->rotation = Vector3D(-90, 0, 0);
	Floor->hasCollision = false;
	Floor->loadTexture("Court.bmp", 512, 512);
	Floor->Scale = Vector3D(5.0f, 3.0f, 0.5f);

	Floor2 = new Object3DS(Vector3D(190.0f, -10.0f, -124.0f), "Floor.3ds", Vector3D(0.0f, 0.0f, 0.0f));
	Floor2->rotation = Vector3D(-90, 0, 180);
	Floor2->hasCollision = false;
	Floor2->loadTexture("Court.bmp", 512, 512);
	Floor2->Scale = Vector3D(5.0f, 3.0f, 0.5f);
	
	for (int i = 0; i < 40; i++)
	{
		float posY = (rand() % 20) + 5;
		float posZ = (rand() % 350) + 1;
		float posX = (rand() % 590) + -200;
		float velZ = (rand() % 30) + 1;
		float velX = (rand() % 30) + 1;
		TheBalls.push_back(new Object3DS(Vector3D(posX, 30.0f, -posZ), "DodgeBall.3ds", Vector3D(velX, posY, velZ)));
		TheBalls[i]->loadTexture("Tiles.bmp", 512, 512);
		TheBalls[i]->Scale = Vector3D(1.0f, 1.0f, 1.0f);
		
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

GameScreenLevel1::~GameScreenLevel1()
{
	
}

//--------------------------------------------------------------------------------------------------


bool GameScreenLevel1::SetUpLevel()
{
	return true;
}

void GameScreenLevel1::Render()
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
	Floor2->render();
	m_Camera->Render();
	glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);

	std::string lives = std::to_string(Lives);
	GameScreen::ScreenText(SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, "Lives Left " + lives);

}

//--------------------------------------------------------------------------------------------------

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	
	mCurrentTime += deltaTime;
	
	GuyModel->boundingSphere->SetCollided(false);

	for (auto i = 0; i <TheBalls.size(); i++)
	{
		TheBalls[i]->update(deltaTime, e);
		if (Collision::SphereSphereCollision(TheBalls[i]->GetBoundingSphere(), GuyModel->GetBoundingSphere()) && TheBalls[i]->hasCollision)
		{
			ballCaught++;
			TheBalls[i]->BallsStacked = ballCaught;
			TheBalls[i]->mPosition = GuyModel->mPosition;
			TheBalls[i]->mPosition.x = GuyModel->mPosition.x * ballCaught;
			TheBalls[i]->hasCollision = false;
			cout << TheBalls[i]->mPosition.x << endl;
			cout << GuyModel->mPosition.x << endl;
			Lives--;
			gameScreenManager->PlayerLives = Lives;
			
		}

		if (TheBalls[i]->hasCollision == false)
		{
			TheBalls[i]->mPosition.x = GuyModel->mPosition.x + -20 * TheBalls[i]->BallsStacked;
			TheBalls[i]->mPosition.z = GuyModel->mPosition.z;
			TheBalls[i]->mPosition.y = GuyModel->mPosition.y;
		}
	}

	GuyModel->boundingSphere->Update(GuyModel->mPosition);
	
	mCurrentTime += deltaTime;
	m_Camera->Update(deltaTime, e);


	
	
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			
			GuyModel->mPosition.z -= GuyModel->velocity.z * deltaTime;

			break;

		case SDLK_s:
			GuyModel->mPosition.z += GuyModel->velocity.z * deltaTime;

			break;
		case SDLK_d:
			GuyModel->mPosition.x += GuyModel->velocity.x * deltaTime;

			break;
		case SDLK_a:
			GuyModel->mPosition.x -= GuyModel->velocity.x * deltaTime;

			break;
		}
	}

	if (GuyModel->mPosition.z <= -259 && GuyModel->mPosition.x >= 226)
	{
		PlaySound(TEXT("Win.wav"), NULL, SND_ASYNC);
		gameScreenManager->ChangeScreen(SCREEN_ENDGAME);
		return;
	}
	if (Lives <= 0)
	{
		
		PlaySound(TEXT("Scream.wav"), NULL, SND_ASYNC);
		gameScreenManager->ChangeScreen(SCREEN_LOSE);
		return;
	}
	

	
}

//--------------------------------------------------------------------------------------------------
void GameScreenLevel1::SetLight()
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
void GameScreenLevel1::SetMaterial() {
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