#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/Polyhedron_3.h>
#include <vector>
#include <CGAL/draw_polyhedron.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef std::vector<Point_3> Points;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef Polyhedron_3::Vertex_iterator        Vertex_iterator;

void convex_hull_3_calc(Points &points, Points &res) {
	points.push_back(Point_3(0, 0, 0));
	points.push_back(Point_3(0, 0, 1));
	points.push_back(Point_3(0, 1, 0));
	points.push_back(Point_3(1, 0, 0));
	points.push_back(Point_3(0, 1, 1));
	points.push_back(Point_3(1, 0, 1));
	points.push_back(Point_3(1, 1, 0));
	points.push_back(Point_3(1, 1, 1));
	points.push_back(Point_3(0.6, 0.5, 0.2));
	points.push_back(Point_3(0.4, 0.1, 0.3));

	Polyhedron_3 poly;

	CGAL::convex_hull_3(points.begin(), points.end(), poly);

	for (Vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
		//std::cout << v->point() << std::endl;
		res.push_back(v->point());
}