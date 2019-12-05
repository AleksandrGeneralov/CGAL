#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::vector<Point_2> Points_2ch;

void convex_hull_2_calc(Points_2ch &points, Points_2ch &res) {
	//Points points, res;

	points.push_back(Point_2(0, 0));
	points.push_back(Point_2(10, 0));
	points.push_back(Point_2(10, 10));
	points.push_back(Point_2(6, 5));
	points.push_back(Point_2(4, 1));

	CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(res));

	std::cout << res.size() << " points on the convex hull" << std::endl;
	for (int i = 0; i < res.size(); ++i)
	{
		std::cout << res[i].x() << " " << res[i].y() << std::endl;
	}
}
