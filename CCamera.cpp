#include "CCamera.h"

#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)


CCamera::CCamera() :
m_cameraHasMoved(true)
{
	//Init with standard OGL values:
	m_position = SF3dVector::F3dVector(500.0, 500.0, 30.0);
	m_viewDir = SF3dVector::F3dVector(0.0, 0.0, -1.0);
	m_rightVector = SF3dVector::F3dVector(1.0, 0.0, 0.0);
	m_upVector = SF3dVector::F3dVector(0.0, 1.0, 0.0);

    //Only to be sure:
    m_rotatedX = m_rotatedY = m_rotatedZ = 0.0;
}

void
CCamera::RotateX(float Angle)
{
	m_rotatedX += Angle;

    printf("ang=%f totalangX = %f - ", Angle, m_rotatedX);
	
	//Rotate viewdir around the right vector:
	m_viewDir = SF3dVector::Normalize3dVector(m_viewDir*cos(Angle*PIdiv180)
								+ m_upVector*sin(Angle*PIdiv180));

	//now compute the new UpVector (by cross product)
	m_upVector = SF3dVector::CrossProduct(&m_viewDir, &m_rightVector)*-1;
}

void
CCamera::RotateY(float Angle)
{
	m_rotatedY += Angle;
    printf("ang=%f totalangY = %f\n\n", Angle, m_rotatedY);
	
	//Rotate viewdir around the up vector:
	m_viewDir = SF3dVector::Normalize3dVector(m_viewDir*cos(Angle*PIdiv180)
								- m_rightVector*sin(Angle*PIdiv180));

	//now compute the new RightVector (by cross product)
	m_rightVector = SF3dVector::CrossProduct(&m_viewDir, &m_upVector);
}

void
CCamera::RotateZ(float Angle)
{
	m_rotatedZ += Angle;
	
	//Rotate viewdir around the right vector:
	m_rightVector = SF3dVector::Normalize3dVector(m_rightVector*cos(Angle*PIdiv180)
								+ m_upVector*sin(Angle*PIdiv180));

	//now compute the new UpVector (by cross product)
	m_upVector = SF3dVector::CrossProduct(&m_viewDir, &m_rightVector)*-1;
}

void
CCamera::MoveForward(float Distance)
{
	m_cameraHasMoved = true;
    m_position = m_position + (m_viewDir*-Distance);
}

void
CCamera::MoveUpward(float Distance)
{
    m_position = m_position + (m_upVector*Distance);
}

void
CCamera::MoveRight(float Distance)
{
	m_cameraHasMoved = true;
    m_position = m_position + (m_rightVector*Distance);
}


CCamera* 
CCamera::getCameraPosition()
{
	return this;
}

void 
CCamera::getLookAtParams(double &eyeX, 
		double &eyeY, 
		double &eyeZ, 
		double &centerX, 
		double &centerY, 
		double &centerZ, 
		double &upX, 
		double &upY, 
		double &upZ)
{
	//The point at which the camera looks:
	SF3dVector viewPoint = m_position + m_viewDir;
/*
	//as we know the up vector, we can easily use gluLookAt:
	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				UpVector.x,UpVector.y,UpVector.z);
*/

	eyeX = m_position.x;
	eyeY = m_position.y;
	eyeZ = m_position.z;
	centerX = viewPoint.x;
	centerY = viewPoint.y;
	centerZ = viewPoint.z;
	upX = m_upVector.x;
	upY = m_upVector.y;
	upZ = m_upVector.z;

	
}