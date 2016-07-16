#ifndef CCAMERA_H
#define CCAMERA_H 1

#include "BasicTypes.h"
#include <windows.h>
#include "gl/Glut.h"

#define SQR(x) (x*x)
#define NULL_VECTOR F3dVector(0.0f,0.0f,0.0f)

class CCamera 
{
public:
	CCamera();
	inline bool hasCameraMoved();
	//void setCameraPosition(int x, int y, float altitude, float yaw, float pitch, float roll);
	
	void getLookAtParams(double &eyeX, 
		double &eyeY, 
		double &eyeZ, 
		double &centerX, 
		double &centerY, 
		double &centerZ, 
		double &upX, 
		double &upY, 
		double &upZ);
		
	CCamera* getCameraPosition();

	// camera position



struct SF3dVector  //Float 3d-vect, normally used
{
	float x,y,z;

static SF3dVector F3dVector ( float x, float y, float z )
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

static float GetF3dVectorLength( SF3dVector * v)
{
	return (float)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

static SF3dVector Normalize3dVector( SF3dVector v)
{
	SF3dVector res;
	float l = GetF3dVectorLength(&v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

SF3dVector operator+ (SF3dVector const &u)
{
	SF3dVector res;
	res.x = x +u.x;
	res.y = y+u.y;
	res.z = z+u.z;
	return res;
}
SF3dVector operator- (SF3dVector const &u)
{
	SF3dVector res;
	res.x = x - u.x;
	res.y = y - u.y;
	res.z = z - u.z;
	return res;
}


SF3dVector operator* (float r)
{
	SF3dVector res;
	res.x = x * r;
	res.y = y * r;
	res.z = z * r;
	return res;
}

static SF3dVector CrossProduct (SF3dVector * u, SF3dVector * v)
{
	SF3dVector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}
float operator* (SF3dVector const &u)	//dot product
{
	return x * u.x 
		+ y * u.y 
		+ z * u.z;
}

};









	SF3dVector m_viewDir;
	SF3dVector m_rightVector;	
	SF3dVector m_upVector;
	SF3dVector m_position;

    float m_rotatedX, m_rotatedY, m_rotatedZ; //just to make easier to keep control

	//SCameraPosition m_position;

	bool m_cameraHasMoved;

	void RotateX(float Angle);

	void RotateY(float Angle);

	void RotateZ(float Angle);

	void MoveForward(float Distance);

	void MoveUpward(float Distance);

	void MoveRight(float Distance);

};

inline bool
CCamera::hasCameraMoved()
{
	return m_cameraHasMoved;
}

#endif