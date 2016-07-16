#include "CSolidSphere.h"
#include "math.h"

#define PI 3.14159265

CSolidSphere::CSolidSphere(int rings, int sectors, float radius)
{

        float const R = 1./(float)(rings-1);
        float const S = 1./(float)(sectors-1);
        int r, s;

        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
                float const y = sin( -(PI*PI) + PI * r * R );
                float const x = cos(2*PI * s * S) * sin( PI * r * R );
                float const z = sin(2*PI * s * S) * sin( PI * r * R );

                *t++ = s*S;
                *t++ = r*R;

                *v++ = x * radius;
                *v++ = y * radius;
                *v++ = z * radius;

                *n++ = x;
                *n++ = y;
                *n++ = z;
        }

        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
                *i++ = r * sectors + s;
                *i++ = r * sectors + (s+1);
                *i++ = (r+1) * sectors + (s+1);
                *i++ = (r+1) * sectors + s;
        }


	/*
	m_latitudes = numLatitudes;
	if (numLatitudes < 1)
	{
		m_latitudes = 1;
	}
	m_longitudes = numLongitutes;
	if (numLongitutes < 1)
	{
		m_longitudes = 1;
	}
	m_radius = radius;

	float a = cos(90.0f);
	float b = cos(45.0f);
	float c = sin(90.0f);
	float d = sin(45.0f);

	float a1 = cos(90.0f);
	float b1 = cos(45.0f);
	float c1 = sin(90.0f);
	float d1 = sin(45.0f);

	//build up the sphere

	for (int lat = 0 ; lat < m_latitudes ; lat++)
	{
		for (int lon = 0 ; lon < m_longitudes ; lon++)
		{


		}
	}
	*/
}

void
CSolidSphere::draw()
{
	//place the routine to draw

        //glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        //glTranslatef(x,y,z);

	glEnable(GL_COLOR_MATERIAL);

	GLfloat materialColor[] = {0.24725f, 0.1995f, 0.0745f, 1.0f};
	GLfloat objShininessEarth[] = { 0.4f*128 };
	GLfloat objDiffuseEarth[] = { 0.75164f, 0.60648f, 0.22648f, 0.0 };
	GLfloat objSpecularEarth[] = { 0.628281f, 0.555802f, 0.366065f, 0.5 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, objDiffuseEarth);   
	glMaterialfv(GL_FRONT, GL_SPECULAR, objSpecularEarth);
	glMaterialfv(GL_FRONT, GL_SHININESS, objShininessEarth);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();

glDisable(GL_COLOR_MATERIAL);
}
