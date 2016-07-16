#ifndef CCOCKPIT_H
#define CCOCKPIT_H 1

#include "CCamera.h"
#include "CTerrainLoader.h"
#include "CRenderTerrain.h"
#include "CRenderSky.h"

class CCockpit
{
public:
	void run();

	static void draw();

	static void reshape(int w, int h);

    static void inputMouseClick(int a, int b, int mouseX, int mouseY);
    static void inputMouse(int mouseX, int mouseY);

	static void inputHold(unsigned char key, int x, int y);
	static void inputRelease(unsigned char key, int x, int y);

	static CCockpit* getInstance();

	CTerrainLoader* m_terrainLoader;

	static CCamera* m_display;

private:
	CCockpit();	
    static void checkPressedKeys();
	static CCockpit* s_instance;
	static CRenderTerrain* m_terrainRender;
	static CRenderSky* m_skyRender;
	enum EKeyState
	{
		EKEYSTATE_PUSHED,
		EKEYSTATE_RELEASED
	};
	static EKeyState m_arrayOfKeys[127];

    static int m_cursorX;
    static int m_cursorY;
    static int m_lastCursorX;
    static int m_lastCursorY;
	
	static const int s_INITIAL_POSITION_X = 450;
	static const int s_INITIAL_POSITION_Y = 450;
};

#endif CCOCKPIT_H