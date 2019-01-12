#ifndef _PYRAMID_H
#define _PYRAMID_H

#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Utilities
#include "Commons.h"

class Pyramid
{
private:
	vertex3D * indexedVertices;
	short * indices;
	TexCoord * texCoords;

	int numVertices;
	int indexCount;

	int numNormals;
	Vector3D * normals;

	bool Load(char* path);
	void DrawTriangle(short a, short b, short c);

public:
	Pyramid(void);
	~Pyramid(void);

	void Draw(void);
	void Update(void);
};

#endif
