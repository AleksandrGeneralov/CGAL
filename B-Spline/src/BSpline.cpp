#include "BSpline.h"

typedef std::vector<Point_3>::iterator iter;

BSpline::BSpline(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.three_d, SIGNAL(clicked()), this, SLOT(add_3_spline()));
	connect(ui.two_d, SIGNAL(clicked()), this, SLOT(add_2_spline()));
}

void BSpline::add_3_spline()
{
	ui.widget->points.clear();
	ui.widget->size = 3;
	ui.widget->points.push_back(Point_3(0.1, 0.1, 0.1));
	ui.widget->points.push_back(Point_3(0.1, 0.4, 0.1));
	ui.widget->points.push_back(Point_3(0.2, 0.4, 0.1));
	ui.widget->points.push_back(Point_3(0.2, 0.2, 0.1));
	ui.widget->points.push_back(Point_3(0.3, 0.2, 0.1));
	ui.widget->points.push_back(Point_3(0.35, 0.3, 0.1));
	ui.widget->points.push_back(Point_3(0.4, 0.1, 0.1));
	ui.widget->repaint();

	/*ui.widget->spline = new BSplineDraw(&ui.widget->points);
	ui.widget->spline->drawSplineCurve();*/
}

void BSpline::btn_clicked()
{
	//qDebug() << "btn was clicked";
}

//void BSpline::mousePressEvent(QMouseEvent * e)
//{
//	if (e->button() == Qt::LeftButton) {
//		ui.widget->qp = e->pos();
//		qglviewer::Vec orig, dir;
//		qglviewer::Camera().convertClickToLine(ui.widget->qp, orig, dir);
//		int selected = 0;
//		for (int i = 0; i < ui.widget->points.size(); i++)
//		{
//			float t = (ui.widget->points[i].z() - orig.z) / dir.z;
//			float x = orig.x + dir.x * t;
//			float y = orig.y + dir.y * t;
//			if (abs(ui.widget->points[i].y() - y) < 0.1f && abs(ui.widget->points[i].x() - x) < 0.1f)
//				selected = i;
//		}
//
//		ui.widget->p = Point_3(ui.widget->points[selected].x(), ui.widget->points[selected].y(), ui.widget->points[selected].z());
//
//		iter iterator = std::find(ui.widget->points.begin(), ui.widget->points.end(), ui.widget->p);
//		ui.widget->points.erase(iterator);
//		e->accept();
//	}
//}
//
//void BSpline::mouseMoveEvent(QMouseEvent * e)
//{
//	if (e->button() == Qt::LeftButton)
//		e->accept();
//}
//
//void BSpline::mouseReleaseEvent(QMouseEvent * e)
//{
//	if (e->button() == Qt::LeftButton) {
//		ui.widget->qp = e->pos();
//		ui.widget->points.push_back(Point_3(e->pos().x(), e->pos().y(), ui.widget->p.z()));
//		e->accept();
//	}		
//}

void BSpline::add_2_spline()
{
	ui.widget->points.clear();
	ui.widget->size = 2;
	ui.widget->points.push_back(Point_3(0.1, 0.1, 0.1));
	ui.widget->points.push_back(Point_3(0.1, 0.4, 0.1));
	ui.widget->points.push_back(Point_3(0.2, 0.4, 0.1));
	ui.widget->points.push_back(Point_3(0.2, 0.2, 0.1));
	ui.widget->points.push_back(Point_3(0.3, 0.2, 0.1));
	ui.widget->points.push_back(Point_3(0.35, 0.3, 0.1));
	ui.widget->points.push_back(Point_3(0.4, 0.1, 0.1));
	ui.widget->repaint();

	/*ui.widget->spline = new BSplineDraw(&ui.widget->points);
	ui.widget->spline->drawSplineCurve();*/
}
