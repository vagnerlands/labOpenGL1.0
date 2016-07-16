#ifndef CSQUARE_H
#define CSQUARE_H 1

class CSquare
{
public:
	CSquare();

	struct SPoint
	{
		float m_x;
		float m_y;
		float m_z;
	};
	
	SPoint m_bottomLeft;
	SPoint m_bottomRight;
	SPoint m_upperLeft;
	SPoint m_upperRight;
};

#endif