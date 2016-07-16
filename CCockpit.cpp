#include "CCockpit.h"
#include "CRenderTerrain.h"
#include "gl/glut.h"

CCockpit* CCockpit::s_instance = NULL;
CRenderTerrain* CCockpit::m_terrainRender = NULL;
CRenderSky* CCockpit::m_skyRender = NULL;
CCamera* CCockpit::m_display = NULL;
CCockpit::EKeyState CCockpit::m_arrayOfKeys[127] = { (CCockpit::EKeyState)1 };
int CCockpit::m_cursorX = -1;
int CCockpit::m_cursorY = -1;
int CCockpit::m_lastCursorX = -1;
int CCockpit::m_lastCursorY = -1;

#define PI 3.14159265


CCockpit::CCockpit()
{
	m_terrainLoader = new CTerrainLoader("./terrainoutput_1000pts.bin");
	if (!m_terrainLoader->loadDataBase())
	{
		printf("\n\n\n       Fail loading database, application will be closed!\n");
		exit(0);
	}

	for (int x = 0 ; x < 127 ; x++)
	{
		m_arrayOfKeys[x] = CCockpit::EKEYSTATE_RELEASED;
	}


	m_display = new CCamera();
    
	m_terrainRender = new CRenderTerrain();
	m_skyRender = new CRenderSky();

}

CCockpit*
CCockpit::getInstance()
{
    if (s_instance == NULL)
	{
		s_instance = new CCockpit();
	}
	return s_instance;
}

void 
CCockpit::draw()
{

	// check for pressed keys
	checkPressedKeys();

	m_terrainRender->draw();

	m_skyRender->updateSkyPosition(
		m_display->m_position.x - 100.0f,
		m_display->m_position.y - 100.0f,
		m_display->m_position.x + 100.0f,
		m_display->m_position.y + 100.0f);

	m_skyRender->draw();

	glutSwapBuffers(); //Send the 3D scene to the screen
	//glFlush(); //not necessary for double buffering
}

void 
CCockpit::reshape(int w, int h)
{

    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   100.0);                //The far z clipping coordinate

}

void 
CCockpit::inputMouseClick(int a, int b, int mouseX, int mouseY)
{

    //printf("a[%d] b[%d] mouseY[%d] mouseY[%d]\n",a, b, mouseX, mouseY);

}

void 
CCockpit::inputMouse(int mouseX, int mouseY)
{
    if (m_lastCursorX == -1)
    {
        m_lastCursorX = mouseX;
    }

    if (m_lastCursorY == -1)
    {
        m_lastCursorY = mouseY;
    }

    m_cursorX = mouseX;
    m_cursorY = mouseY;

    float deltaX = 0;
    float deltaY = 0;

    deltaX = m_lastCursorX - m_cursorX;
    deltaY = m_lastCursorY - m_cursorY;

    float angle = (int)((atan2(deltaY, deltaX)*180/PI) + 270) % 360;
        
    if ((m_lastCursorX != m_cursorX) || (m_lastCursorY != m_cursorY))
    {
        printf("angle=%f, deltaX = %f, deltaY = %f\n", 
            angle,
            deltaX,
            deltaY);

        m_lastCursorX = m_cursorX;
        m_lastCursorY = m_cursorY;

        if (deltaX > 0)
        {
            deltaX *= -1;
        }

        if (deltaY < 0)
        {
            deltaY *= -1;
        }

        m_display->RotateX( cos(angle*PI/180)*(deltaY/5) );
        m_display->RotateY( sin(angle*PI/180)*(deltaX/5) );
    }

    //printf("mouseY[%d] mouseY[%d]\n", mouseX, mouseY);

}

void 
CCockpit::checkPressedKeys()
{
	if (m_arrayOfKeys['a'] == EKEYSTATE_PUSHED)
	{
		m_display->MoveRight(-0.3f);
	}

	if (m_arrayOfKeys['d'] == EKEYSTATE_PUSHED)
	{
		m_display->MoveRight( 0.3f);
	}

	if (m_arrayOfKeys['w'] == EKEYSTATE_PUSHED)
	{
		m_display->MoveForward(-0.3f);
	}

	if (m_arrayOfKeys['s'] == EKEYSTATE_PUSHED)
	{
		m_display->MoveForward(0.3f);
	}

	if (m_arrayOfKeys['u'] == EKEYSTATE_PUSHED)
	{
        m_display->MoveUpward( 0.3f);
	}

	if (m_arrayOfKeys['j'] == EKEYSTATE_PUSHED)
	{
		m_display->MoveUpward(-0.3f);
	}

	if (m_arrayOfKeys['y'] == EKEYSTATE_PUSHED)
	{
		m_display->RotateX( 0.5f);
	}

	if (m_arrayOfKeys['h'] == EKEYSTATE_PUSHED)
	{
		m_display->RotateX(-0.5f);
	}

	if (m_arrayOfKeys['.'] == EKEYSTATE_PUSHED)
	{
		m_display->RotateY(-0.5f);		
	}

	if (m_arrayOfKeys[','] == EKEYSTATE_PUSHED)
	{
		m_display->RotateY( 0.5f);
	}

	if (m_arrayOfKeys[27] == EKEYSTATE_PUSHED)
	{		
		exit(0);
	}
	/*
	switch (key) 
	{
	case 'a':
		m_display->m_cameraHasMoved = true;
		m_display->m_position.m_posX -= 1;
		break;
	case 'd':
		m_display->m_cameraHasMoved = true;
		m_display->m_position.m_posX += 1;
		break;
	case 'w':
		m_display->m_cameraHasMoved = true;
		m_display->m_position.m_posY += 1;
		break;
	case 's':
		m_display->m_cameraHasMoved = true;
		m_display->m_position.m_posY -= 1;
		break;

	case 'u':
		m_display->m_position.m_altitude += 0.1f;
		break;
	case 'j':
		m_display->m_position.m_altitude -= 0.1f;
		break;

	case 'y':
		m_display->m_position.m_pitch += 0.5f;
		if (m_display->m_position.m_pitch > 90.0f)
		{
			m_display->m_position.m_pitch = 90.0f;
		}
		break;
	case 'h':
		m_display->m_position.m_pitch -= 0.5f;
		if (m_display->m_position.m_pitch < -90.0f)
		{
			m_display->m_position.m_pitch = -90.0f;
		}
		break;

	case 27: //Escape key
		exit(0);
		break;
	}
	*/
}

void 
CCockpit::inputHold(unsigned char key, int x, int y) 
{
	m_arrayOfKeys[key] = CCockpit::EKEYSTATE_PUSHED;
	if (key == '0')
	{
		if (glutGameModeGet (GLUT_GAME_MODE_POSSIBLE)) {
			glutEnterGameMode();
		}
	}
    //glutPostRedisplay();
}

void 
CCockpit::inputRelease(unsigned char key, int x, int y) 
{
	m_arrayOfKeys[key] = CCockpit::EKEYSTATE_RELEASED;
	//printf("soltei %s\n", key);
}

void 
CCockpit::run()
{
	
	while (true)
	{
		// end of the procedure 
		glutMainLoop();

	}
}