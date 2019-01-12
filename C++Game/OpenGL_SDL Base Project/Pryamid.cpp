#include <fstream>
#include <iostream>
#include "pryamid.h"
using namespace::std;

Pyramid::Pyramid()
{
	Load("Pyramid.txt");

}

Pyramid::~Pyramid() {
	delete indexedVertices;
	delete indices;
}
bool Pyramid::Load(char* path)
{
	ifstream inFile;
	inFile.open(path);

	if (!inFile.good()) {
		cerr << "Can't open model file " << path << endl;
		return false;
	}
	inFile >> numVertices;

	if (numVertices > 0) {
		indexedVertices = new vertex3D[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			inFile >> indexedVertices[i].x;
			inFile >> indexedVertices[i].y;
			inFile >> indexedVertices[i].z;
		}
	}
	//norms
	inFile >> numNormals;

	if (numNormals > 0) {
		normals = new Vector3D[numNormals];
		for (int i = 0; i < numNormals; i++)
		{
			inFile >> normals[i].x;
			inFile >> normals[i].y;
			inFile >> normals[i].z;
		}
	}
	int numTriangles;
	inFile >> numTriangles;
	indexCount = numTriangles * 3;

	if (indexCount > 0) {
		indices = new short[indexCount];
		for (int i = 0; i < indexCount; i++)
		{
			inFile >> indices[i];
		}
	}


	inFile >> numVertices;
	if (numVertices > 0) {
		texCoords = new TexCoord[numVertices];
		for (int i = 0; i < numVertices; i++)
		{
			inFile >> texCoords[i].u;
			inFile >> texCoords[i].v;
		}
	}

	inFile.close();
	return true;


}
void Pyramid::Draw() {
	for (int i = 0; i < indexCount; i += 3) {
		DrawTriangle(indices[i], indices[i + 1], indices[i + 2]);
	}
}

void Pyramid::DrawTriangle(short a, short b, short c) {
	glBegin(GL_TRIANGLES);
	glTexCoord2f(texCoords[a].u, texCoords[a].v);
	glNormal3f(normals[a].x, normals[a].y, normals[a].z);
	glVertex3f(indexedVertices[a].x, indexedVertices[a].y, indexedVertices[a].z);
	glTexCoord2f(texCoords[b].u, texCoords[b].v);
	glNormal3f(normals[b].x, normals[b].y, normals[b].z);
	glVertex3f(indexedVertices[b].x, indexedVertices[b].y, indexedVertices[b].z);
	glTexCoord2f(texCoords[c].u, texCoords[c].v);
	glNormal3f(normals[c].x, normals[c].y, normals[c].z);
	glVertex3f(indexedVertices[c].x, indexedVertices[c].y, indexedVertices[c].z);
	glEnd();

	//glBegin(GL_TRIANGLES);
	//glTexCoord2f(texCoords[a].u, texCoords[a].v);

	//glVertex3f(indexedVertices[a].x, indexedVertices[a].y, indexedVertices[a].z);


}