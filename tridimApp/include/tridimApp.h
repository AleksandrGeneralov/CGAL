#pragma once

#include <QtWidgets/QMainWindow>
#include <qobject.h>
#include "ui_tridimApp.h"
#include <CGAL/point_generators_3.h>
#include <CGAL/algorithm.h>
#include <time.h>

class tridimApp : public QMainWindow
{
	Q_OBJECT

public:
	int count;

public:
	tridimApp(QWidget *parent = Q_NULLPTR);
	Point_3 calcVector(Point_3 start, Point_3 finish);
	double calcScalarProduct(Point_3 start, Point_3 finish);
	void vertexInput(Point_3 p);

public slots:
	void addPoint();
	void removePoint();
	void clearPoints();
	void addGridCube();
	void addRandCube();
	void addRandSphere();
	void addRandShellSphere();
	void addPointHexagon();

private:
	Ui::tridimAppClass ui;
};
