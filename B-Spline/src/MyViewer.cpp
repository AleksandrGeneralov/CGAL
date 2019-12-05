#include "MyViewer.h"

typedef std::vector<Point_3>::iterator iter;

MyViewer::MyViewer(QWidget * parent) : QGLViewer(parent)
{
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
	spline = new BSplineDraw(&points, size);
	spline->drawSplineCurve(size);
}

void MyViewer::postSelection(const QPoint & point)
{
	if (!myMouseBehavior) {
		// Вычисление вершин, находящихся на пути луча 
		qglviewer::Vec orig, dir;
		camera()->convertClickToLine(point, orig, dir);
		
		int selected = 0;
		for (int i = 0; i < points.size(); i++)
		{
			float t = (points[i].z() - orig.z) / dir.z;
			float x = orig.x + dir.x * t;
			float y = orig.y + dir.y * t;
			if (abs(points[i].y() - y) < 0.05f && abs(points[i].x() - x) < 0.05f) {
				selected = i;
				break;
			}
		}
		p = Point_3(points[selected].x(), points[selected].y(), points[selected].z());
	}
	else {
		qglviewer::Vec orig, dir, selectedPoint;
		camera()->convertClickToLine(point, orig, dir);
		float t = (p.z() - orig.z) / dir.z;
		float x = orig.x + dir.x * t;
		float y = orig.y + dir.y * t;
		*p_it = Point_3(x, y, p.z());;
	}
}

void MyViewer::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton) {
		/*if (!myMouseBehavior) {
			postSelection(e->pos());
			myMouseBehavior = true;			
		}
		else {
			p_it = std::find(points.begin(), points.end(), p);
			postSelection(e->pos());
			if (p_it != points.end()) {
				postSelection(e->pos());
				repaint();
			}
			myMouseBehavior = false;
		}*/
		postSelection(e->pos());
		p_it = std::find(points.begin(), points.end(), p);
		myMouseBehavior = true;
	}
}

void MyViewer::mouseMoveEvent(QMouseEvent * e)
{
	postSelection(e->pos());
	if (p_it != points.end()) {
		postSelection(e->pos());
		repaint();
	}
}

void MyViewer::mouseReleaseEvent(QMouseEvent * e)
{
	myMouseBehavior = false;
}

void MyViewer::init()
{
	myMouseBehavior = false;
	restoreStateFromFile();
}
