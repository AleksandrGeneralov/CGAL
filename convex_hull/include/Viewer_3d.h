#pragma once
#include <Viewer.h>
//#include <QGLViewer/qglviewer.h>
//#include <qstring.h>
//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef std::vector<Point_3> Points_3d;

class Viewer_3d : public Viewer
{
public:
	Points_3d points, result;
protected:
	void draw();
	void init();
};


