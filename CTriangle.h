#ifndef CTRIANGLE_H
#define CTRIANGLE_H 1

class CTriangle
{
public:
	CTriangle();

	struct SPoint
	{
		float m_x;
		float m_y;
		float m_z;
	};
	
	SPoint m_coordA;
	SPoint m_coordB;
	SPoint m_coordC;

};

#endif CTRIANGLE_H
