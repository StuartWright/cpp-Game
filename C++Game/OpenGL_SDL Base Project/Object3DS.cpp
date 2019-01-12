#include "object3DS.h" 
#include "../gl/glut.h" 
#include "3dsLoader.h"
#include "Collision.h"
#include "iostream"
#include "Constants.h"
#include <windows.h>
using namespace std;
int lek;
//--------------------------------------------------------------------------------------------------
Object3DS::Object3DS(Vector3D startPosition, string modelFileName, Vector3D beginVelocity)
{   mPosition = startPosition;

	velocity.y = beginVelocity.y;	
	velocity.z = beginVelocity.z;
	velocity.x = beginVelocity.x;									  //3ds file to load. 
	
	scale = 1;
	
	
	SpawnDelay = 1.0f;
	StartY = startPosition.y;

	initalPosition = startPosition;
	initalVelocity = beginVelocity;
	boundingSphere = new Sphere(mPosition, scale*8.3);
	boundingSphere->SetCollided(false);
	strcpy(fileName, modelFileName.c_str());
	loadModel();
}
													
	void Object3DS::loadModel() 
	{ 
		if (fileName[0] != '-') Load3DS(&object, fileName); 
	}
	//--------------------------------------------------------------------------------------------------
	void Object3DS::loadTexture(char* path, int width, int height)
	{ //TODO: Load a texture to map to the object. 
		
		Texture2D* texture = new Texture2D();
		texture->Load(path, width, height);
		object.id_texture = texture->GetID();
		glBindTexture(GL_TEXTURE_2D, texture->GetID());

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	}
							   //--------------------------------------------------------------------------------------------------
	void Object3DS::update(float deltaTime, SDL_Event e)
	{ //TODO: Move object here. }
		
		if (hasCollision == true && IsLevel1 == true)
		{
			float yForce = (-GRAVITY * velocity.y)* deltaTime;

			boundingSphere->SetCollided(false);

			mPosition.y += yForce;

			mPosition.z += velocity.z* deltaTime;

			if (mPosition.y < 0 && yForce < 0)
			{
				PlaySound(TEXT("Bounce.wav"), NULL, SND_ASYNC);
				velocity.y -= 1;
				StartY -= 1;
				velocity.y = -velocity.y;

			}
			if (mPosition.y > StartY && yForce > 0)
			{
				velocity.y = -velocity.y;
			}


			if (velocity.y == 0 && velocity.y == 0)
			{
				if (SpawnDelay < 0)
				{
					velocity = initalVelocity;
					mPosition = initalPosition;
					StartY = initalPosition.y;
					SpawnDelay = 1.0f;
				}
				else
				{
					SpawnDelay -= deltaTime;
				}

				velocity.x = initalVelocity.y;
				velocity.z = initalVelocity.z;

			}

			boundingSphere->Update(mPosition);
		}
		else if (hasCollision == false && IsLevel1 == true)
		{
			float yForce = (-GRAVITY * velocity.y)* deltaTime;

			mPosition.y += yForce;

			if (mPosition.y < 0 && yForce < 0)
			{
				velocity.y = 0;
			}

			if (mPosition.y > StartY && yForce >= 0)
			{
				velocity.y = -velocity.y;
			}

			boundingSphere->Update(mPosition);
			boundingSphere->SetCollided(true);
		}
		if (mPosition.z > 5 && IsLevel1 == true)
		{
			velocity = initalVelocity;
			mPosition = initalPosition;
		}
		if (mPosition.x < -250 && IsLevel1 == true)
		{
			velocity = initalVelocity;
			mPosition = initalPosition;
		}

		if (hasCollision == true && IsLevel1 == false)
		{
			mPosition.z += velocity.z* deltaTime;
			mPosition.x += velocity.x* deltaTime;
			boundingSphere->SetCollided(false);
		}
		

	}			 

	void Object3DS::render()

		{

			glPushMatrix(); 

			glTranslatef(mPosition.x, mPosition.y, mPosition.z);

			glRotatef(rotation.x, 1, 0, 0);
			glRotatef(rotation.y, 0, 1, 0);
			glRotatef(rotation.z, 0, 0, 1);

			glScalef(Scale.x, Scale.y, Scale.z);

			glBindTexture(GL_TEXTURE_2D, object.id_texture); 
			// We set the active texture
			glBegin(GL_TRIANGLES); 
			// glBegin and glEnd delimit the vertices that define a primitive (in our case triangles) 
			for (int l_index = 0; l_index < object.Triangles_qty; l_index++)
			{
				//-----------------FIRST VERTEX ----------------//
			    // Texture coordinates of the first vertex 
				glTexCoord2f( object.texcoord[ object.Triangle[l_index].a ].u,
				 object.texcoord[ object.Triangle[l_index].a ].v);
				// Coordinates of the first vertex 
				glVertex3f(object.vertex[object.Triangle[l_index].a].x,
					object.vertex[object.Triangle[l_index].a].y, 
					object.vertex[object.Triangle[l_index].a].z); 
				//Vertex definition //-----------------SECOND VERTEX -----------------
			   // Texture coordinates of the second vertex
				 glTexCoord2f( object.texcoord[ object.Triangle[l_index].b ].u,
				object.texcoord[ object.Triangle[l_index].b ].v);
				// Coordinates of the second vertex 
				glVertex3f(object.vertex[object.Triangle[l_index].b].x,
					object.vertex[object.Triangle[l_index].b].y, 
					object.vertex[object.Triangle[l_index].b].z);
				//-----------------THIRD VERTEX -----------------
				// Texture coordinates of the third vertex 
				glTexCoord2f( object.texcoord[ object.Triangle[l_index].c ].u, 
				 object.texcoord[ object.Triangle[l_index].c ].v); 
				// Coordinates of the Third vertex 
				glVertex3f(object.vertex[object.Triangle[l_index].c].x,
					object.vertex[object.Triangle[l_index].c].y, 
					object.vertex[object.Triangle[l_index].c].z);
		}

			
		if (hasCollision)
			glutWireSphere(boundingSphere->GetBoundingRadius(), 10, 10);

		glEnd();
		glPopMatrix();
	    
}
	
	Sphere* Object3DS::GetBoundingSphere()
	{
		return boundingSphere;
	}