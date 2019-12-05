#include "pch.h"
#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <convex_hull_3.h>
#include <Viewer_3d.h>
#include <Viewer.h>
#include <convex_hull_2h.h>
#include <vector>
#include <qapplication.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef std::vector<Point_3> Points_3;

int main(int argc, char* argv[])
{
	Points_3 points, res;

	convex_hull_3_calc(points, res);

	QApplication application(argc, argv);
	Viewer_3d viewer;
	viewer.points = points;
	viewer.result = res;
	viewer.setWindowTitle("simpleViewer");
	viewer.show();
	return application.exec();

	return 0;
}