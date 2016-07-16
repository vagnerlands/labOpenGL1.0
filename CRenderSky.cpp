#include "CTextureLoader.h"
#include "CRenderSky.h"
#include "CCockpit.h"
#include "gl/glut.h"

CRenderSky::CRenderSky() :
	m_bottomLeftCoor(0.0f),
	m_bottomRightCoor(0.0f),
	m_upperLeftCoor(0.0f),
	m_upperRightCoor(0.0f),
	m_thick(1.0f)
{
    CTextureLoader::getInstance()->loadTextureRaw("d:/sky.bmp", ETEXTURE_SKY);
}

void
CRenderSky::updateSkyPosition(float bl, float br, float ul, float ur)
{
	m_bottomLeftCoor = bl;
	m_bottomRightCoor = br;
	m_upperLeftCoor = ul;
	m_upperRightCoor = ur;
};

void
CRenderSky::draw()
{
    glEnable(GL_TEXTURE_2D);
	int err = glGetError();
	if (err != 0)
	{
		printf("glError2 EnableTexture2D=%d\n", glGetError());
	}

	glBindTexture( GL_TEXTURE_2D, CTextureLoader::getTextureByEnum(ETEXTURE_SKY) );
	if (err != 0)
	{
		printf("glError2 glBindTexture=%d\n", glGetError());
	}


	static float movSky = 1.000f;
	static float movSkyFactor = 0.001f;

	glPushMatrix();

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);	
	glColor4f (255/130, 255/163, 255/206, 0.9);

	//face down
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f((CCockpit::getInstance()->m_display->m_position.x-200), (CCockpit::getInstance()->m_display->m_position.y-200), 60.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f((CCockpit::getInstance()->m_display->m_position.x+200), (CCockpit::getInstance()->m_display->m_position.y-200), 60.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f((CCockpit::getInstance()->m_display->m_position.x+200), (CCockpit::getInstance()->m_display->m_position.y+200), 60.0f);
    glTexCoord2f(1.0f, 1.0f);
	glVertex3f((CCockpit::getInstance()->m_display->m_position.x-200), (CCockpit::getInstance()->m_display->m_position.y+200), 60.0f);

	glEnd();
	glPopMatrix();

glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);

	movSky += movSkyFactor;
	if ((movSky < 0.9) || (movSky > 1.0f))
	{
		movSkyFactor *= -1;
	}


};