#ifndef CTEXTURELOADER_H
#define CTEXTURELOADER_H 1

#include "BasicTypes.h"
#include "gl/glut.h"

class CTextureLoader
{
public:
	static CTextureLoader* getInstance();
	static void loadTextureRaw(const char* filename, const int textIndex);
	static GLuint getTextureByEnum(ETextureTypes textureId);
	CTextureLoader::~CTextureLoader();

private:
	CTextureLoader();
	static GLuint m_texture[ETextureTypes::ETEXTURE_TOTAL_NUM_OF_TEXTURES];
	static CTextureLoader* s_instance;

};

#endif