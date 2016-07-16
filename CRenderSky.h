#ifndef CRENDERSKY_H
#define CRENDERSKY_H 1

class CRenderSky
{
public:
	CRenderSky();
	void draw();
	void updateSkyPosition(float bl, float br, float ul, float ur);
private:
	float m_bottomLeftCoor;
	float m_bottomRightCoor;
	float m_upperLeftCoor;
	float m_upperRightCoor;
	float m_thick;
};

#endif 