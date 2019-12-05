#include "tridimApp.h"
#include <random>
#include <ctime>

typedef std::vector<Point_3>::iterator iter;
typedef CGAL::Random_points_in_cube_3<Point_3> rand_cube;
typedef CGAL::Random_points_in_sphere_3<Point_3> rand_sph;
typedef CGAL::Random_points_on_sphere_3<Point_3> rand_shell_sph;

// рандомные точки в шестиугольнике двумерном
// алгоритм присвоения точки фигуре, векторное произведение: отрицательное - точка справа от грани, положительное - слева, нужно слева
// рандомить точки в области прямоугольника и смотреть, принадлежат ли фигуре

tridimApp::tridimApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.add, SIGNAL(clicked()), this, SLOT(addPoint()));
	connect(ui.remove, SIGNAL(clicked()), this, SLOT(removePoint()));
	connect(ui.clear, SIGNAL(clicked()), this, SLOT(clearPoints()));
	connect(ui.grid_cube, SIGNAL(clicked()), this, SLOT(addGridCube()));
	connect(ui.rand_cube, SIGNAL(clicked()), this, SLOT(addRandCube()));
	connect(ui.rand_sphere, SIGNAL(clicked()), this, SLOT(addRandSphere()));
	connect(ui.rand_shell_sphere, SIGNAL(clicked()), this, SLOT(addRandShellSphere()));
	connect(ui.rand_hexagon, SIGNAL(clicked()), this, SLOT(addPointHexagon()));
	connect(ui.add, &QPushButton::clicked, this, &tridimApp::addPoint);
}

void tridimApp::addPoint() 
{
	float x = QString(ui.coord_x->text()).toFloat();
	float y = QString(ui.coord_y->text()).toFloat();
	float z = QString(ui.coord_z->text()).toFloat();
	ui.widget->points.push_back(Point_3(x, y, z));
	ui.widget->repaint();
}

void tridimApp::removePoint()
{
	float x = QString(ui.coord_x->text()).toFloat();
	float y = QString(ui.coord_y->text()).toFloat();
	float z = QString(ui.coord_z->text()).toFloat();
	iter it = std::find(ui.widget->points.begin(), ui.widget->points.end(), Point_3(x, y, z));
	ui.widget->points.erase(it);
	ui.widget->repaint();
}

void tridimApp::clearPoints()
{
	float x = QString(ui.coord_x->text()).toFloat();
	float y = QString(ui.coord_y->text()).toFloat();
	float z = QString(ui.coord_z->text()).toFloat();
	ui.widget->points.clear();
	ui.widget->repaint();
}

void tridimApp::addGridCube()
{
	ui.widget->points.clear();
	float x = QString(ui.coord_x->text()).toFloat();
	float y = QString(ui.coord_y->text()).toFloat();
	float z = QString(ui.coord_z->text()).toFloat();
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < 10; k++)
				ui.widget->points.push_back(Point_3(x + 0.1 * i, y + 0.1 * j, z + 0.1 * k));
	ui.widget->repaint();
}

void tridimApp::addRandCube()
{
	ui.widget->points.clear();
	rand_cube gen(0.4);
	for (unsigned int i = 0; i < 250; ++i)
		ui.widget->points.push_back(*gen++);
	ui.widget->repaint();
}

void tridimApp::addRandSphere()
{
	srand(time(0));
	ui.widget->points.clear();
	rand_sph gen(0.4);
	CGAL::cpp11::copy_n(gen, 250, std::back_inserter(ui.widget->points));
	ui.widget->repaint();
}

void tridimApp::addRandShellSphere()
{
	ui.widget->points.clear();
	rand_shell_sph gen(0.4);
	CGAL::cpp11::copy_n(gen, 250, std::back_inserter(ui.widget->points));
	ui.widget->repaint();
}

void tridimApp::addPointHexagon() {
	srand((int)time(0));
	ui.widget->flag = 1;
	ui.widget->points.clear();
	ui.widget->points.push_back(Point_3(0.2, 0.0, 0.0));
	ui.widget->points.push_back(Point_3(0.0, 0.4, 0.0));
	ui.widget->points.push_back(Point_3(0.2, 0.9, 0.0));
	ui.widget->points.push_back(Point_3(0.5, 0.9, 0.0));
	ui.widget->points.push_back(Point_3(0.7, 0.4, 0.0));
	ui.widget->points.push_back(Point_3(0.5, 0.0, 0.0));

	count = 0;
	double max_x = -10000;
	double max_y = -10000;
	double min_x = 10000;
	double min_y = 10000;
	for (int i = 0; i < ui.widget->points.size(); i++) {
		if (ui.widget->points[i].x() > max_x)
			max_x = ui.widget->points[i].x();
		if (ui.widget->points[i].y() > max_y)
			max_y = ui.widget->points[i].y();
		if (ui.widget->points[i].x() < min_x)
			min_x = ui.widget->points[i].x();
		if (ui.widget->points[i].y() < min_y)
			min_y = ui.widget->points[i].y();
	}
	while (count < 150) {
		vertexInput(Point_3((double)(rand()) / RAND_MAX * (max_x - min_x) + min_x, (double)(rand()) / RAND_MAX * (max_y - min_y) + min_y, 0.0));
	}
	
	ui.widget->repaint();
}

Point_3 tridimApp::calcVector(Point_3 start, Point_3 finish) {
	return Point_3(finish.x() - start.x(), finish.y() - start.y(), 0.0);
}

double tridimApp::calcScalarProduct(Point_3 start, Point_3 finish) {
	//return finish.x() * start.x() + finish.y() * start.y();
	return finish.y() * start.x() - finish.x() * start.y();
}

void tridimApp::vertexInput(Point_3 p) {
	int size_vec = ui.widget->points.size();
	for (int i = 0; i < 6; i++) {
		Point_3 vec1, vec2, p1;
		vec1 = calcVector(ui.widget->points[i], p);

		if (i == 5)
			vec2 = calcVector(ui.widget->points[i], ui.widget->points[0]);
		else
			vec2 = calcVector(ui.widget->points[i], ui.widget->points[i + 1]);

		if (calcScalarProduct(vec2, vec1) > 0)
			break;
		else if (i == 5) {
			ui.widget->points.push_back(p);
			count++;
		}
	}
}
