#pragma once

#include <QtWidgets/QMainWindow>
#include <QGLViewer/qglviewer.h>
#include <QtGui/qevent.h>
#include "ui_BSpline.h"
#include <qobject.h>
#include <algorithm>

class BSpline : public QMainWindow
{
	Q_OBJECT

public:
	BSpline(QWidget *parent = Q_NULLPTR);
	/*virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);*/

public slots:
	void add_3_spline();
	void add_2_spline();
	void btn_clicked();

private:
	Ui::BSplineClass ui;
};
