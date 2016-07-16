#ifndef CRENDERTERRAIN_H
#define CRENDERTERRAIN_H 1

#include "BasicTypes.h"
#include "gl/glut.h"

class CRenderTerrain
{
public:
	CRenderTerrain();	
	~CRenderTerrain();	
	void draw();
private:
	void init();
	void loadTextureRaw(const char* filename, const int textIndex);
	void renderBitmapString(float x, float y, void *font,char *string);
	void dispFPS();
	TVecTriangles* m_vertTerrain;
	static int m_counter;
	GLuint m_texture[2];
};


#endif