#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Subdivision.h"

class Subdivision : public QMainWindow
{
	Q_OBJECT

public:
	Subdivision(QWidget *parent = Q_NULLPTR);
	void check_descr_text(const Points3_pair shape);
	void check_resize_map();
	void check_labels();

public slots:
	void corner_cutting();
	void draw_default_points();
	void draw_null_points();
	void add();
	void back();
	void plus_btn();
	void minus_btn();
	void show_vector();

private:
	Ui::SubdivisionClass ui;
};
