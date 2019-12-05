#pragma once
#include "typedefs.h"
#include <math.h>
#include <QtOpenGL\qgl.h>
//#include <c_graph.h>



class PNtrianglesDraw
{

public:
	typedef std::pair<int, PNtrianglesDraw> pair_pn; //int - number of triangle of oxahedron
	typedef std::unordered_multimap<int, pair_pn> type_map; //int - level of map

	PNtrianglesDraw() { }
	PNtrianglesDraw(Point_3 p1, Point_3 p2, Point_3 p3,
		Point_3 n1, Point_3 n2, Point_3 n3);
	PNtrianglesDraw(Point_3 p1, Point_3 p2, Point_3 p3,
		Point_3 n1, Point_3 n2, Point_3 n3, int _level);
	void setLevel(int _level) { level = _level; }
	int getLevel() { return level; }

	void drawTriangleGL();
	void drawTriangleCustom();
	void recursion();
	//void add_level_map(type_map &map, int lvl);
	void add_element_map(type_map &map, int lvl_map, int num_triang);

private:
	// Level of recursion
	int level;
	// Координаты и нормали обыкновенного треугольника
	Point_3 p300, p030, p003;
	Point_3 n200, n020, n002;	
	// Дополнительные координаты и нормали 
	Point_3 p210, p120, p201, p102, p021, p012, p111;
	Point_3 n110, n011, n101;


	double w(Point_3 i, Point_3 j, Point_3 k);
	Point_3 bb(Point_3 i, Point_3 j, Point_3 normal);
	void calcPNcoefs();
	double len(Point_3 p);
	Point_3 normalize(Point_3 p);
	Point_3 nn(Point_3 i, Point_3 j);
	Point_3 calcP(double u, double v, double w);
	Point_3 calcN(double u, double v, double w);
	void calc(double u, double v, double w, Point_3& p, Point_3& n);	
};

