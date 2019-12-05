#include "pch.h"
#include "Viewer_3d.h"


void Viewer_3d::draw()
{
	drawAxis();

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < result.size(); ++i)
	{
		glVertex3f(result[i].x(), result[i].y(), result[i].z());
	}
	glEnd();

	glPointSize(10.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
		for (int i = 0; i < result.size(); ++i)
		{
			glVertex3f(result[i].x(), result[i].y(), result[i].z());
		}
	glEnd();

	glPointSize(3.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); ++i)
	{
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();

}


void Viewer_3d::init()
{
	restoreStateFromFile();
}
