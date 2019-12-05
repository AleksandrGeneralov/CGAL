#pragma once
#include <QGLViewer/qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>
#include <BSplineDraw.h>
#include <QtGui/qevent.h>
#include <algorithm>

typedef std::vector<Point_3>::iterator iter;

class MyViewer : public QGLViewer
{
public:
	MyViewer(QWidget* parent);
	Points3 points;
	BSplineDraw *spline;
	iter p_it;
	int size;
	Point_3 p;
	Point_3 p_end;
	bool myMouseBehavior;

protected:
	virtual void postSelection(const QPoint &point);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void draw();
	virtual void init();

signals:
	void btn_clicked();
};
