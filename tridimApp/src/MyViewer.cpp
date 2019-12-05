#include "MyViewer.h"

MyViewer::MyViewer(QWidget * parent) : QGLViewer(parent)
{
	flag = 0;
}

void MyViewer::postSelection(const QPoint & point)
{
	// Вычисление вершин, находящихся на пути луча 
	qglviewer::Vec orig, dir;
	camera()->convertClickToLine(point, orig, dir);
	std::vector<int> selected = std::vector<int>();
	for (int i = 0; i < points.size(); i++)
	{
		float t = (points[i].z() - orig.z) / dir.z;
		float x = orig.x + dir.x * t;
		float y = orig.y + dir.y * t;
		if (abs(points[i].y() - y) < 0.1f && abs(points[i].x() - x) < 0.1f)
			selected.push_back(i);
	}
	// Отображение результата в отдельном окне
	QString result;
	for (int i = 0; i < selected.size(); i++)
	{
		QString tmp = "Vertex number " + QString::number(selected[i]) + ": " +
			QString::number(points[selected[i]].x()) + " " +
			QString::number(points[selected[i]].y()) + " " +
			QString::number(points[selected[i]].z()) + "\n";
		result.append(tmp);
	}
	QMessageBox::information(this, "Selection", result);
}

void MyViewer::draw()
{
	glPointSize(3.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); ++i)
	{
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();

	if (flag) {
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 6; ++i)
		{
			glVertex3f(points[i].x(), points[i].y(), points[i].z());
		}
		glEnd();
	}
}

void MyViewer::init()
{
	restoreStateFromFile();
	points.push_back(Point_3(0.1, 0.1, 0.1));
}
