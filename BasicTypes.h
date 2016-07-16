#ifndef BASICTYPES_H
#define BASICTYPES_H 1

#include <iostream>
#include <vector>
#include "CTriangle.h"
#include "CSquare.h"
#include <math.h>

using namespace std;

typedef vector<CTriangle> TVecTriangles;
typedef vector<CSquare> TVecSquares;

struct SMapBody
{
	int m_posX;
	int m_posY;
	float m_height;
	bool m_normalized;
};

struct SFileTerrain
{
	char m_header[100];
	SMapBody** m_body;
};

enum ETextureTypes
{
	ETEXTURE_FIRST_TEXTURE = 0,
    ETEXTURE_ARID_TERRAIN = ETEXTURE_FIRST_TEXTURE,
    ETEXTURE_OCEAN,
	ETEXTURE_SKY,
	ETEXTURE_TOTAL_NUM_OF_TEXTURES,
};

#endif