#include "CTextureLoader.h"
#include "BasicTypes.h"
#include <math.h>
#include "CRenderTerrain.h"
#include "CCockpit.h"
#include "gl/glut.h"


CTextureLoader* CTextureLoader::s_instance = NULL;
GLuint CTextureLoader::m_texture[] = {0};

CTextureLoader*
CTextureLoader::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new CTextureLoader();
	}

	return s_instance;
}

CTextureLoader::CTextureLoader()
{

}



void 
CTextureLoader::loadTextureRaw(const char* filename, const int textIndex)
{
// load a 256x256 RGB .RAW file as a texture

	const int wrap = 0;
    
    int width, height;
    BYTE* data;
    FILE* file;

    // open texture data
	if ((file = fopen(filename, "rb")) == NULL)
        return;


    // allocate buffer
    width = 512;
    height = 512;
    data = (BYTE*)malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );

	/*
	//for debug only
	int dataPos    = *(int*)&(data[0x0A]);
	int imageSize  = *(int*)&(data[0x22]);
	int width1      = *(int*)&(data[0x12]);
	int height1     = *(int*)&(data[0x16]);
	*/

    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &m_texture[textIndex] );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, m_texture[textIndex] );
	int err = glGetError();
	if (err != 0)
	{
		printf("glError BindTexture=%d\n", glGetError());
	}

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    //                 GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
    //                 wrap ? GL_REPEAT : GL_CLAMP );
    //glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
    //                 wrap ? GL_REPEAT : GL_CLAMP );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    // build our texture mipmaps	
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );
	err = glGetError();
	if (err != 0)
	{
		printf("glError gluBuild2DMipmaps=%d\n", glGetError());
	}

    // free buffer
    free( data );
}

GLuint 
CTextureLoader::getTextureByEnum(ETextureTypes textureId)
{
	return m_texture[textureId];
}

CTextureLoader::~CTextureLoader()
{
	for (ETextureTypes texType = ETextureTypes::ETEXTURE_FIRST_TEXTURE; 
		texType < ETextureTypes::ETEXTURE_TOTAL_NUM_OF_TEXTURES; 
		texType = (ETextureTypes)(texType+1))
	{
	    glDeleteTextures( 1, &m_texture[texType] );
	}
}