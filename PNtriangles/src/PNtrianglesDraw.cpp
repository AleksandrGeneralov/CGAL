#include "PNtrianglesDraw.h"

PNtrianglesDraw::PNtrianglesDraw(Point_3 p1, Point_3 p2, Point_3 p3,
	Point_3 n1, Point_3 n2, Point_3 n3)
{
	level = 4;
	p300 = p1; p030 = p2; p003 = p3;
	n200 = n1; n020 = n2; n002 = n3;
}

PNtrianglesDraw::PNtrianglesDraw(Point_3 p1, Point_3 p2, Point_3 p3,
	Point_3 n1, Point_3 n2, Point_3 n3, int _level)
{
	level = _level;
	p300 = p1; p030 = p2; p003 = p3;
	n200 = n1; n020 = n2; n002 = n3;
}

void PNtrianglesDraw::drawTriangleGL() {
	glColor3f(1.0, 0.9, 0.5);
	glBegin(GL_TRIANGLES);
	glNormal3f(n200.x(), n200.y(), n200.z());
	glVertex3f(p300.x(), p300.y(), p300.z());
	glNormal3f(n020.x(), n020.y(), n020.z());
	glVertex3f(p030.x(), p030.y(), p030.z());
	glNormal3f(n002.x(), n002.y(), n002.z());
	glVertex3f(p003.x(), p003.y(), p003.z());
	glEnd();
}

void PNtrianglesDraw::drawTriangleCustom()
{
	if (level == 0)
		drawTriangleGL();
	else
		recursion();
}

void PNtrianglesDraw::recursion() {
	calcPNcoefs();
	double u, v, w;
	Point_3 p1, p2, p3;
	Point_3 n1, n2, n3;

	//Triangle 1
	calc(0.0, 0.0, 1.0, p1, n1);
	calc(0.5, 0.0, 0.5, p2, n2);
	calc(0.0, 0.5, 0.5, p3, n3);
	PNtrianglesDraw triang1(p1, p2, p3, n1, n2, n3, level - 1);
	triang1.drawTriangleCustom();

	//Triangle 2
	calc(1.0, 0.0, 0.0, p1, n1);
	calc(0.5, 0.5, 0.0, p2, n2);
	calc(0.5, 0.0, 0.5, p3, n3);
	PNtrianglesDraw triang2(p1, p2, p3, n1, n2, n3, level - 1);
	triang2.drawTriangleCustom();

	//Triangle 3
	calc(0.0, 1.0, 0.0, p1, n1);
	calc(0.0, 0.5, 0.5, p2, n2);
	calc(0.5, 0.5, 0.0, p3, n3);
	PNtrianglesDraw triang3(p1, p2, p3, n1, n2, n3, level - 1);
	triang3.drawTriangleCustom();

	//Triangle 4
	calc(0.5, 0.5, 0.0, p1, n1);
	calc(0.0, 0.5, 0.5, p2, n2);
	calc(0.5, 0.0, 0.5, p3, n3);
	PNtrianglesDraw triang4(p1, p2, p3, n1, n2, n3, level - 1);
	triang4.drawTriangleCustom();
}

void PNtrianglesDraw::add_element_map(type_map & map, int lvl_map, int num_triang)
{
	calcPNcoefs();
	double u, v, w;
	Point_3 p1, p2, p3;
	Point_3 n1, n2, n3;

	//Triangle 1
	calc(0.0, 0.0, 1.0, p1, n1);
	calc(0.5, 0.0, 0.5, p2, n2);
	calc(0.0, 0.5, 0.5, p3, n3);
	map.insert(std::make_pair<int, pair_pn>(lvl_map + 1, std::make_pair(num_triang, PNtrianglesDraw(p1, p2, p3, n1, n2, n3))));

	//Triangle 2
	calc(1.0, 0.0, 0.0, p1, n1);
	calc(0.5, 0.5, 0.0, p2, n2);
	calc(0.5, 0.0, 0.5, p3, n3);
	map.insert(std::make_pair<int, pair_pn>(lvl_map + 1, std::make_pair(num_triang, PNtrianglesDraw(p1, p2, p3, n1, n2, n3))));

	//Triangle 3
	calc(0.0, 1.0, 0.0, p1, n1);
	calc(0.0, 0.5, 0.5, p2, n2);
	calc(0.5, 0.5, 0.0, p3, n3);
	map.insert(std::make_pair<int, pair_pn>(lvl_map + 1, std::make_pair(num_triang, PNtrianglesDraw(p1, p2, p3, n1, n2, n3))));

	//Triangle 4
	calc(0.5, 0.5, 0.0, p1, n1);
	calc(0.0, 0.5, 0.5, p2, n2);
	calc(0.5, 0.0, 0.5, p3, n3);
	map.insert(std::make_pair<int, pair_pn>(lvl_map + 1, std::make_pair(num_triang, PNtrianglesDraw(p1, p2, p3, n1, n2, n3))));
}

double PNtrianglesDraw::w(Point_3 i, Point_3 j, Point_3 n)
{
	Point_3 dv = Point_3(j.x() - i.x(), j.y() - i.y(), j.z() - i.z());
	return (dv.x()* n.x() + dv.y() * n.y() + dv.z() * n.z()); //dot
}

Point_3 PNtrianglesDraw::bb(Point_3 i, Point_3 j, Point_3 normal)
{
	double w2 = w(i, j, normal);
	return Point_3(
		(2.0 * i.x() + j.x() - w2 * normal.x()) / 3.0,
		(2.0 * i.y() + j.y() - w2 * normal.y()) / 3.0,
		(2.0 * i.z() + j.z() - w2 * normal.z()) / 3.0);
}

void PNtrianglesDraw::calcPNcoefs()
{
	//Вычисление промежуточных нормалей
	n110 = nn(n200, n020);
	n101 = nn(n200, n002);
	n011 = nn(n020, n002);

	//Вычисление промежуточных вершин
	p210 = bb(p300, p030, n200);
	p120 = bb(p030, p300, n020);
	p021 = bb(p030, p003, n020);
	p012 = bb(p003, p030, n002);
	p201 = bb(p300, p003, n200);
	p102 = bb(p003, p300, n002);

	double Ex = (p210.x() + p120.x() + p021.x()
		+ p012.x() + p201.x() + p102.x()) / 6.0;
	double Ey = (p210.y() + p120.y() + p021.y()
		+ p012.y() + p201.y() + p102.y()) / 6.0;
	double Ez = (p210.z() + p120.z() + p021.z()
		+ p012.z() + p201.z() + p102.z()) / 6.0;

	double Vx = (p300.x() + p030.x() + p003.x()) / 3.0;
	double Vy = (p300.y() + p030.y() + p003.y()) / 3.0;
	double Vz = (p300.z() + p030.z() + p003.z()) / 3.0;

	p111 = Point_3(1.5 * Ex - 0.5 * Vx,
		1.5 * Ey - 0.5 * Vy,
		1.5 * Ez - 0.5 * Vz);
}

double PNtrianglesDraw::len(Point_3 p)
{
	return sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z());
}

Point_3 PNtrianglesDraw::normalize(Point_3 p)
{
	double len = sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z());
	return Point_3(p.x() / len, p.y() / len, p.z() / len);
}

Point_3 PNtrianglesDraw::nn(Point_3 i, Point_3 j)
{
	Point_3 dv = Point_3(j.x() - i.x(), j.y() - i.y(), j.z() - i.z());
	Point_3 vij = Point_3(
		2.0 * (dv.x() * (i.x() + j.x())) / len(dv) / len(dv),
		2.0 * (dv.y() * (i.y() + j.y())) / len(dv) / len(dv),
		2.0 * (dv.z() * (i.z() + j.z())) / len(dv) / len(dv));
	Point_3 nij = Point_3(
		i.x() + j.x() - vij.x() * dv.x(),
		i.y() + j.y() - vij.y() * dv.y(),
		i.z() + j.z() - vij.z() * dv.z());

	return normalize(nij);
}

Point_3 PNtrianglesDraw::calcP(double u, double v, double w)
{
	return Point_3(
		(p300.x() * u + 3 * p210.x() * v + 3 * p201.x() * w) * u * u +
		(p030.x() * v + 3 * p120.x() * u + 3 * p021.x() * w) * v * v +
		(p003.x() * w + 3 * p012.x() * v + 3 * p102.x() * u) * w * w +
		6 * p111.x() * u * v * w,
		(p300.y() * u + 3 * p210.y() * v + 3 * p201.y() * w) * u * u +
		(p030.y() * v + 3 * p120.y() * u + 3 * p021.y() * w) * v * v +
		(p003.y() * w + 3 * p012.y() * v + 3 * p102.y() * u) * w * w +
		6 * p111.y() * u * v * w,
		(p300.z() * u + 3 * p210.z() * v + 3 * p201.z() * w) * u * u +
		(p030.z() * v + 3 * p120.z() * u + 3 * p021.z() * w) * v * v +
		(p003.z() * w + 3 * p012.z() * v + 3 * p102.z() * u) * w * w +
		6 * p111.z() * u * v * w

	);
}

Point_3 PNtrianglesDraw::calcN(double u, double v, double w)
{
	return Point_3(
		n200.x() * u * u + n020.x() * v * v + n002.x() * w * w +
		2 * n110.x() * u * v + 2 * n011.x() * v * w + 2 * n101.x() * u * w,
		n200.y() * u * u + n020.y() * v * v + n002.y() * w * w +
		2 * n110.y() * u * v + 2 * n011.y() * v * w + 2 * n101.y() * u * w,
		n200.z() * u * u + n020.z() * v * v + n002.z() * w * w +
		2 * n110.z() * u * v + 2 * n011.z() * v * w + 2 * n101.z() * u * w
	);
}

void PNtrianglesDraw::calc(double u, double v, double w, Point_3& p, Point_3& n)
{
	p = calcP(u, v, w);
	n = calcN(u, v, w);
}
