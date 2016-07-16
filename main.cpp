// labOpenGl.cpp : Defines the entry point for the console application.
//

#include "CCockpit.h"
#include "gl/glut.h"


int main(int argc, char* argv[])
{
	//initialization of Open GL
	glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutGameModeString( "800ª600:32" );
	if (glutGameModeGet (GLUT_GAME_MODE_POSSIBLE)) {
		glutEnterGameMode();
	}
	//windows size 1024x1024 pixels
    glutInitWindowSize(800, 600);

	//finally, create the window where the graphics will be rendered :)
	glutCreateWindow("Sistema Solar v0.1");

	//make polygons better drawed - but consumes more memory 
	//alternativelly use GL_FLAT
	glShadeModel(GL_SMOOTH);

	glutDisplayFunc(CCockpit::getInstance()->draw);
	glutIdleFunc(CCockpit::getInstance()->draw);
	glutReshapeFunc(CCockpit::getInstance()->reshape);
	glutKeyboardFunc(CCockpit::getInstance()->inputHold);
	glutKeyboardUpFunc(CCockpit::getInstance()->inputRelease);
    glutPassiveMotionFunc(CCockpit::getInstance()->inputMouse);
    glutMouseFunc(CCockpit::getInstance()->inputMouseClick);

	//CCockpit* mainObj = new CCockpit();

	//runs forever
	CCockpit::getInstance()->run();

	return 0;
}

