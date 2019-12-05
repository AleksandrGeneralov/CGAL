#pragma once
#include <QGLViewer/qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>

class MyViewer : public QGLViewer
{
public:
	MyViewer(QWidget* parent);
	Points3 points;
	bool flag;

protected:
	virtual void postSelection(const QPoint &point);
	virtual void draw();
	virtual void init();
};
