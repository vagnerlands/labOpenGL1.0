#ifndef CTERRAINLOADER_H
#define CTERRAINLOADER_H 1

#include <iostream>
#include <vector>
#include "BasicTypes.h"
#include "CCamera.h"
#include "CTriangle.h"

using namespace std;

class CTerrainLoader
{
public:

	//ctor
	CTerrainLoader(); 
	//dtctor
	~CTerrainLoader();

	CTerrainLoader(string filePath);

	void setFilePath(string filePath);

    bool loadDataBase();

	// in a matrix of 200x200 we have 40000 points
	// therefore, 10000 squares, each square is compounded by 2 triangles
	// so we have 20000 triangles at all allocated in the memory...
	TVecTriangles* buildWorldMatrix(CCamera& display);

private:

	static const int s_matrixSize = 1000;

	string m_filePath;

	SFileTerrain m_o;

	TVecTriangles m_worldMatrix;

	static const int s_coefStab = 5.0f;

	static const int s_mapDetailFactor = 5.0f;


};

inline void 
CTerrainLoader::setFilePath(string filePath)
{
	m_filePath = filePath;
}


#endif CTERRAINLOADER_H