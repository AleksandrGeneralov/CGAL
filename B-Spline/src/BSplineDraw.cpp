#include "BSplineDraw.h"
#include <QtOpenGL\qgl.h>

double* BSplineDraw::calcSplineCoef3(double t)
{
	double* coefs = new double[4];

	coefs[0] = (1.0 - t) * (1.0 - t) * (1.0 - t) / 6.0;
	coefs[1] = (3.0 * t * t * t - 6.0 * t * t + 4) / 6.0;
	coefs[2] = (-3.0 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0;
	coefs[3] = t * t * t / 6.0;

	return coefs;
}

double* BSplineDraw::calcSplineCoef2(double t)
{
	double* coefs = new double[3];

	coefs[0] = (1.0 - t) * (1.0 - t) / 2.0;
	coefs[1] = (-2.0 * t * t + 2 * t + 1) / 2.0;
	coefs[2] = t * t / 2.0;

	return coefs;
}

BSplineDraw::BSplineDraw(Points3* _points, int size, int _stepCount, bool _closed)
{
	closed = _closed;
	stepCount = _stepCount;
	points = _points;

	// Генерация коэффициентов B-сплайна 3 порядка
	if (size == 3) {
		coefs = std::vector<double*>();
		for (int i = 0; i < stepCount; i++)
		{
			double * coef = calcSplineCoef3(i / (double)stepCount);
			coefs.push_back(coef);
		}
	}
	
	if (size == 2) {
		coefs = std::vector<double*>();
		for (int i = 0; i < stepCount; i++)
		{
			double * coef = calcSplineCoef2(i / (double)stepCount);
			coefs.push_back(coef);
		}
	}
}

BSplineDraw::~BSplineDraw()
{
}

void BSplineDraw::drawSegment3(int segNum)
{
	int pNum = points->size();
	int p0, p1, p2, p3;
	//Вычисление номеров вершин для построения сплайна
	if (closed == false)
	{
		p0 = clamp(segNum - 1, 0, pNum - 1);
		p1 = clamp(segNum, 0, pNum - 1);
		p2 = clamp(segNum + 1, 0, pNum - 1);
		p3 = clamp(segNum + 2, 0, pNum - 1);
	}
	else
	{
		p0 = (segNum - 1 + pNum) % pNum;
		p1 = (segNum + pNum) % pNum;
		p2 = (segNum + 1 + pNum) % pNum;
		p3 = (segNum + 2 + pNum) % pNum;
	}
	// По заранее вычисленным коэффициентам 
	// Вычисляем промежуточные точки сплайна
	for (int i = 0; i < stepCount; i++)
	{
		double x = coefs.at(i)[0] * points->at(p0).x()
			+ coefs.at(i)[1] * points->at(p1).x()
			+ coefs.at(i)[2] * points->at(p2).x()
			+ coefs.at(i)[3] * points->at(p3).x();
		double y = coefs.at(i)[0] * points->at(p0).y()
			+ coefs.at(i)[1] * points->at(p1).y()
			+ coefs.at(i)[2] * points->at(p2).y()
			+ coefs.at(i)[3] * points->at(p3).y();
		double z = coefs.at(i)[0] * points->at(p0).z()
			+ coefs.at(i)[1] * points->at(p1).z()
			+ coefs.at(i)[2] * points->at(p2).z()
			+ coefs.at(i)[3] * points->at(p3).z();

		glVertex3f(x, y, z);
	}
}

void BSplineDraw::drawSegment2(int segNum)
{
	int pNum = points->size();
	int p0, p1, p2;
	//Вычисление номеров вершин для построения сплайна
	if (closed == false)
	{
		p0 = clamp(segNum - 1, 0, pNum - 1);
		p1 = clamp(segNum, 0, pNum - 1);
		p2 = clamp(segNum + 1, 0, pNum - 1);
	}
	else
	{
		p0 = (segNum - 1 + pNum) % pNum;
		p1 = (segNum + pNum) % pNum;
		p2 = (segNum + 1 + pNum) % pNum;
	}
	// По заранее вычисленным коэффициентам 
	// Вычисляем промежуточные точки сплайна
	for (int i = 0; i < stepCount; i++)
	{
		double x = coefs.at(i)[0] * points->at(p0).x()
			+ coefs.at(i)[1] * points->at(p1).x()
			+ coefs.at(i)[2] * points->at(p2).x();
		double y = coefs.at(i)[0] * points->at(p0).y()
			+ coefs.at(i)[1] * points->at(p1).y()
			+ coefs.at(i)[2] * points->at(p2).y();
		double z = coefs.at(i)[0] * points->at(p0).z()
			+ coefs.at(i)[1] * points->at(p1).z()
			+ coefs.at(i)[2] * points->at(p2).z();

		glVertex3f(x, y, z);
	}
}

void BSplineDraw::drawSplineCurve(int size)
{
	int segmentsCount;
	if (closed == false)
	{
		glColor3f(1.0f, 1.0f, 0.0f);
		segmentsCount = points->size() - 1;
		glBegin(GL_LINE_STRIP);
	}
	else
	{
		segmentsCount = points->size(); //Сегмент между первой и последней вершиной
		glBegin(GL_LINE_LOOP);
	}
	if (size == 2)
		glColor3f(1.0f, 1.0f, 0.0f);
	else if (size == 3)
		glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < segmentsCount; i++)
	{
		if (size == 3)
			drawSegment3(i);

		if (size == 2)
			drawSegment2(i);
	}
	glEnd();
}

