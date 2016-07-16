#include "BasicTypes.h"
#include <math.h>
#include "CRenderTerrain.h"
#include "CCockpit.h"
#include "gl/glut.h"
#include "CTextureLoader.h"
#include "CSolidSphere.h"

static char s[1000];
static int frame=0,time,timebase=0;
int font=(int)GLUT_BITMAP_HELVETICA_10;

#define PI 3.14159265

int CRenderTerrain::m_counter = 0;


CRenderTerrain::CRenderTerrain()
{
	m_vertTerrain = NULL;
	CTextureLoader::getInstance()->loadTextureRaw("./texAridTerrain.bmp", ETEXTURE_ARID_TERRAIN);
	CTextureLoader::getInstance()->loadTextureRaw("./texOcean.bmp", ETEXTURE_OCEAN);
}


void 
CRenderTerrain::renderBitmapString(float x, float y, void *font,char *string)
{
    char *c;
    // set position to start drawing fonts
    glRasterPos2f(x, y);
    // loop all the characters in the string
    for (c=string; *c != '\0'; c++) {
      glutBitmapCharacter(font, *c);
    }
}

void 
CRenderTerrain::dispFPS()
{
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
	m_counter++;
    if (time - timebase > 1000) 
    {
        sprintf(s,"FpS: %4.2f X[%f] Y[%f] Alt[%f]",
			frame*1000.0/(time-timebase), 
			CCockpit::getInstance()->m_display->m_position.x,CCockpit::getInstance()->m_display->m_position.y,CCockpit::getInstance()->m_display->m_position.z);
        timebase = time;        
        frame = 0;

		if (m_counter > 10)
		{

			m_counter = 0;

			//printf("\n%s\n",s);

		}
    }

//TEXT
glMatrixMode( GL_PROJECTION ) ;
glPushMatrix() ; // save
glLoadIdentity();// and clear
glMatrixMode( GL_MODELVIEW ) ;
glPushMatrix() ;
glLoadIdentity() ;

//glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top
glViewport(0, 0, 800, 600);
glRasterPos2f( 0.0,0.9 ) ; // center of screen. (-1,0) is center left.
glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
const char * p = s ;
do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *p ); while( *(++p) ) ;


//glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on

glMatrixMode( GL_PROJECTION ) ;
glPopMatrix() ; // revert back to the matrix I had before.
glMatrixMode( GL_MODELVIEW ) ;
glPopMatrix() ;
    //setOrthographicProjection();
    //renderBitmapString(10,10,(void *)font,s);


   
    //resetPerspectiveProjection();
}


void 
CRenderTerrain::init()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glClearColor(0.09, 0.0, 0.7, 1.0); // Set background (clear) color to black

	GLuint filter;                      // Which Filter To Use
	GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
	GLuint fogfilter= 2;                    // Which Fog To Use
	GLfloat fogColor[4]= {0.09, 0.0, 0.7, 1.0};      // Fog Color

	glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.001f);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_NICEST);          // Fog Hint Value
	glFogf(GL_FOG_START, 60.0f);             // Fog Start Depth
	glFogf(GL_FOG_END, 80.0f);               // Fog End Depth
	glEnable(GL_FOG);

	glLoadIdentity(); //Reset the drawing perspective
}

void
CRenderTerrain::draw()
{

    init();

    double param1, param2, param3, param4, param5, param6, param7, param8, param9;
	CCockpit::getInstance()->m_display->getLookAtParams(param1, param2, param3, param4, param5, param6, param7, param8, param9);
	gluLookAt (
		param1, 
		param2, 
		param3, 
		param4, 
		param5, 
		param6, 
		param7, 
		param8, 
		param9);

	if (CCockpit::getInstance()->m_display->hasCameraMoved())
	{
		m_vertTerrain = CCockpit::getInstance()->m_terrainLoader->buildWorldMatrix(*CCockpit::getInstance()->m_display);
	}

	glPushMatrix();

/*
    // for debug purpose
    glBegin(GL_TRIANGLES);
	glColor3f (1.0, 0.0, 1.0);
    glVertex3f( 400, 401, 0);              // Top
	glColor3f (0.0, 1.0, 1.0);
    glVertex3f( 399,399, 0);              // Bottom Left
	glColor3f (1.0, 1.0, 0.0);
    glVertex3f( 401,399, 0); 
	glEnd();
*/
    glEnable(GL_TEXTURE_2D);
	int err = glGetError();
	if (err != 0)
	{
		printf("glError EnableTexture2D=%d\n", glGetError());
	}

	glBindTexture( GL_TEXTURE_2D, CTextureLoader::getTextureByEnum(ETEXTURE_ARID_TERRAIN) );
	if (err != 0)
	{
		printf("glError glBindTexture=%d\n", glGetError());
	}
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_TRIANGLES);

	for(int x = 0; x < m_vertTerrain->size(); x++)
	{	
		if (m_vertTerrain->at(x).m_coordA.m_z > 7.0f)
		{
            glColor3f (((m_vertTerrain->at(x).m_coordA.m_z-6) * 0.752), ((m_vertTerrain->at(x).m_coordA.m_z-6) * 0.70196), 0.55686);
		} 
		else 
		{
            glColor3f (0.443, 0.356, 0.874);
		} 
		glVertex3f(m_vertTerrain->at(x).m_coordA.m_x, m_vertTerrain->at(x).m_coordA.m_y, m_vertTerrain->at(x).m_coordA.m_z);		
		glTexCoord2f(0.0f, 0.0f);

		/*---*/

		if (m_vertTerrain->at(x).m_coordB.m_z > 7.0f)
		{
            glColor3f (((m_vertTerrain->at(x).m_coordB.m_z-6) * 0.7529), ((m_vertTerrain->at(x).m_coordB.m_z-6) * 0.7019), 0.55686);
		} 
		else 
		{
            glColor3f (0.443, 0.356, 0.874);
		} 
		glVertex3f(m_vertTerrain->at(x).m_coordB.m_x, m_vertTerrain->at(x).m_coordB.m_y, m_vertTerrain->at(x).m_coordB.m_z);
		glTexCoord2f(0.0f, 1.0f);

		/*---*/

		if (m_vertTerrain->at(x).m_coordC.m_z > 7.0f)
		{
            glColor3f (((m_vertTerrain->at(x).m_coordC.m_z-6) * 0.7529), ((m_vertTerrain->at(x).m_coordC.m_z-6) * 0.7019), 0.55686);
		} 
		else 
		{
            glColor3f (0.443, 0.356, 0.874);
		} 
		glVertex3f(m_vertTerrain->at(x).m_coordC.m_x, m_vertTerrain->at(x).m_coordC.m_y, m_vertTerrain->at(x).m_coordC.m_z);
		glTexCoord2f(1.0f, 1.0f);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
		if (err != 0)
	{
		printf("glError glDisable=%d\n", glGetError());
	}

	
	glPopMatrix();


	dispFPS();

	glTranslatef(CCockpit::getInstance()->m_display->m_position.x,CCockpit::getInstance()->m_display->m_position.y+10.0,CCockpit::getInstance()->m_display->m_position.z);
	CSolidSphere* c = new CSolidSphere(15, 15, 2);
	c->draw();
	
}
