#pragma once
#include "typedefs.h"
#include <math.h>

class BSplineDraw
{
protected:
	std::vector<double*> coefs;
	int stepCount;
	Points3* points;
	double* calcSplineCoef3(double t);
	void drawSegment3(int segNum);
	double* calcSplineCoef2(double t);
	void drawSegment2(int segNum);

public:
	bool closed;

	inline int clamp(int val, int minVal, int maxVal)
	{
		return std::min(std::max(val, minVal), maxVal);
	}

	void drawSplineCurve(int size);

	BSplineDraw(Points3* _points, int size, int _stepCount = 10, bool _closed = true);
	~BSplineDraw();
};

