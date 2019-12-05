#pragma once
#include <QGLViewer/qglviewer.h>
#include <qstring.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::vector<Point_2> Points_2d;

class Viewer : public QGLViewer
{
public:
	Points_2d points, result;
protected:
	virtual void draw();
	virtual void init();
};


