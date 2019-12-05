#pragma once
#include <QGLViewer/qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>
#include <QtGui/qevent.h>
#include <algorithm>

typedef std::vector<Point_3>::iterator iter;

class MyViewer : public QGLViewer
{
public:
	MyViewer(QWidget* parent);
	Points3_pair points_pair;
	Points3_pair points_pair_curr;
	std::vector<bool> is_weight;
	un_map map;
	int num_of_part;
	int curr_num_of_part;
	int weight_all;
	int num_weight_all;
	int count_change_weight;
	bool flag;
	bool plus;

	void set_default_points();
	void set_null_points();
	Points3_pair get_default_points_pair();
	Points3_pair get_null_points_pair();
	void back_points();
	void draw_shape(const Points3_pair shape);
	void resize_map();
	void init_change_weights();
	std::vector<bool> init_is_weight();
	std::vector<bool> init_is_weight_false();
	bool update_is_weight(int index);
	//void calc_postSelection(const QPoint & point, Points3_pair shape);

	// CORNER CUTTING ALGORITHM
	void corner_cutting_pair();
	void corner_cutting_calc_pair(p_pair p1, p_pair p2);
	p_pair calc_point_first_1x2x1_pair(std::pair<Point_3, int> p1, std::pair<Point_3, int> p2);
	p_pair calc_point_second_1x2x1_pair(std::pair<Point_3, int> p1, std::pair<Point_3, int> p2);

protected:
	virtual void postSelection(const QPoint &point);
	virtual void draw();
	virtual void init();
};
