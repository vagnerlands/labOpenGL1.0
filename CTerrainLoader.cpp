#include "CTerrainLoader.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

CTerrainLoader::CTerrainLoader()
{

}

CTerrainLoader::CTerrainLoader(string filePath)
{
	m_filePath = filePath;
}


CTerrainLoader::~CTerrainLoader()
{
	if (m_o.m_body != NULL)
	{
		delete[] m_o.m_body;
	}
}

bool
CTerrainLoader::loadDataBase()
{
	bool retVal = false;

	printf("Allocating memory for terrain database...\n\n\n\n");

	m_o.m_body = new SMapBody*[s_matrixSize];
	for (int x = 0 ; x < s_matrixSize ; x++)
	{
		m_o.m_body[x] = new SMapBody[s_matrixSize];
	}

	if (m_o.m_body)
	{
		printf("Load successfull!\n\n\n\n");

		printf("Loading database from %s...\n", m_filePath.c_str());
		if (m_filePath.c_str())
		{
			ifstream terrainFile;
			terrainFile.open(m_filePath.c_str(), ios::in|ios::binary);
			if (terrainFile)
			{
				//Header
				terrainFile.seekg (0, ios::beg);
				terrainFile.read(reinterpret_cast<char *>(m_o.m_header), 100);
				
				//Body
				for (int x = 0 ; x < s_matrixSize ; x++)
				{
					for (int y = 0 ; y < s_matrixSize ; y++)
					{
						//char* memBlock = new char[s_matrixSize];
						//terrainFile.read(memBlock, sizeof(SMapBody));

						//m_o.m_body[x][y] = reinterpret_cast<SMapBody &>(memBlock);

						terrainFile.read(reinterpret_cast<char *>(&m_o.m_body[x][y]), sizeof(SMapBody));
					}
				}
				terrainFile.close();
				printf("Database loaded successfully!\n");

				retVal = true;
			}
		}
	}

	return retVal;
}

TVecTriangles* 
CTerrainLoader::buildWorldMatrix(CCamera& display)
{
	m_worldMatrix.clear();
	//m_worldMatrix.resize(20000);
	if (m_o.m_body)
	{
		int iterat(0);
		int devX(((int)display.m_position.x / s_mapDetailFactor) - 50);
		int devY(((int)display.m_position.y / s_mapDetailFactor) - 50);

		if (devX < 0)
		{
			devX = 0;
		}

		if (devY < 0)
		{
			devY = 0;
		}

		while (iterat < 40000)
		{
			CTriangle tObj;

			if ((devX+1 < s_matrixSize) && (devY+1 < s_matrixSize))
			{

			//Point [A]
			tObj.m_coordA.m_x = m_o.m_body[devX][devY].m_posX * s_mapDetailFactor;
			tObj.m_coordA.m_y = m_o.m_body[devX][devY].m_posY * s_mapDetailFactor;
			tObj.m_coordA.m_z = m_o.m_body[devX][devY].m_height / s_coefStab;

			//Point [B]
			tObj.m_coordB.m_x = m_o.m_body[devX+1][devY].m_posX * s_mapDetailFactor;
			tObj.m_coordB.m_y = m_o.m_body[devX+1][devY].m_posY * s_mapDetailFactor;
			tObj.m_coordB.m_z = m_o.m_body[devX+1][devY].m_height / s_coefStab;

			//Point [C]
			tObj.m_coordC.m_x = m_o.m_body[devX][devY+1].m_posX * s_mapDetailFactor;
			tObj.m_coordC.m_y = m_o.m_body[devX][devY+1].m_posY * s_mapDetailFactor;
			tObj.m_coordC.m_z = m_o.m_body[devX][devY+1].m_height / s_coefStab;

			// first triangle
			m_worldMatrix.push_back(tObj);
			iterat++;
			}

			//*-*-*-*-*-*-*-*-*-

			if ((devX+1 < s_matrixSize) && (devY+1 < s_matrixSize))
			{
			//Point [A]
			tObj.m_coordA.m_x = m_o.m_body[devX][devY+1].m_posX * s_mapDetailFactor;
			tObj.m_coordA.m_y = m_o.m_body[devX][devY+1].m_posY * s_mapDetailFactor;
			tObj.m_coordA.m_z = m_o.m_body[devX][devY+1].m_height / s_coefStab;

			//Point [B]
			tObj.m_coordB.m_x = m_o.m_body[devX+1][devY+1].m_posX * s_mapDetailFactor;
			tObj.m_coordB.m_y = m_o.m_body[devX+1][devY+1].m_posY * s_mapDetailFactor;
			tObj.m_coordB.m_z = m_o.m_body[devX+1][devY+1].m_height / s_coefStab;

			//Point [C]
			tObj.m_coordC.m_x = m_o.m_body[devX+1][devY].m_posX * s_mapDetailFactor;
			tObj.m_coordC.m_y = m_o.m_body[devX+1][devY].m_posY * s_mapDetailFactor;
			tObj.m_coordC.m_z = m_o.m_body[devX+1][devY].m_height / s_coefStab;

			//second triangle
			m_worldMatrix.push_back(tObj);
			iterat++;
			}

			//move to the next square
			devX++;

			if (devX >= ((((int)display.m_position.x / s_mapDetailFactor) + 50) - 1))
			{
				devX = ((int)display.m_position.x / s_mapDetailFactor) - 50;
				if (devX < 0)
				{
					devX = 0;
				}
				devY++;
			}

			if (devY >= ((((int)display.m_position.y / s_mapDetailFactor) + 50) - 1))
			{
				// force to quit this loop
				iterat = 40001;
			}

		}

	}

	display.m_cameraHasMoved = false;

	return &m_worldMatrix;
    
}