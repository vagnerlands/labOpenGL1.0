#ifndef CSOLIDSPHERE_H
#define CSOLIDSPHERE_H 1

#include "BasicTypes.h"
#include "gl/glut.h"

using namespace std;

class CSolidSphere
{
public:
	CSolidSphere(int rings, int sectors, float radius);
	void draw();
private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
	/*
    CSphere(int numLatitudes, int numLongitutes, float radius);
    void draw();
private:
	TVecSquares m_sphere;
	float m_radius;
	int m_latitudes;
	int m_longitudes;

	*/

};

#endif