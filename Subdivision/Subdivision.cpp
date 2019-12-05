#include "Subdivision.h"

Subdivision::Subdivision(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.def_point_btn, SIGNAL(clicked()), this, SLOT(draw_default_points()));
	connect(ui.null_point_btn, SIGNAL(clicked()), this, SLOT(draw_null_points()));
	connect(ui.add_btn, SIGNAL(clicked()), this, SLOT(add()));
	connect(ui.corner_cutting_btn, SIGNAL(clicked()), this, SLOT(corner_cutting()));
	connect(ui.check_info_btn, SIGNAL(clicked()), this, SLOT(show_vector()));
	connect(ui.back_btn, SIGNAL(clicked()), this, SLOT(back()));
	connect(ui.plus_weight_btn, SIGNAL(clicked()), this, SLOT(plus_btn()));
	connect(ui.minus_weight_btn_3, SIGNAL(clicked()), this, SLOT(minus_btn()));
}

void Subdivision::check_descr_text(const Points3_pair shape) {
	std::string str_descr = "";
	for (size_t i = 0; i < shape.size(); i++) {
		str_descr += "P(" + std::to_string(shape[i].first.x()) + "," +
			std::to_string(shape[i].first.y()) + "," +
			std::to_string(shape[i].first.z()) + "): " +
			std::to_string(shape[i].second);
		if (i != shape.size() - 1)
			str_descr += "\n";
	}
	ui.descr_text->setText(QString::fromStdString(str_descr));
}

void Subdivision::check_resize_map() {
	if (ui.widget->curr_num_of_part < ui.widget->num_of_part) {
		ui.widget->resize_map();
	}
}

void Subdivision::check_labels() {
	ui.cor_cut_label->setText(QString::fromStdString("Number of partitions: " + std::to_string(ui.widget->num_of_part)));
	ui.cur_cor_cut_label->setText(QString::fromStdString("Current number of partitions: " + std::to_string(ui.widget->curr_num_of_part)));
}

void Subdivision::corner_cutting() {
	ui.widget->corner_cutting_pair();
	check_labels();
	check_descr_text(ui.widget->points_pair);
	ui.widget->repaint();
}

void Subdivision::draw_default_points() {
	ui.widget->set_default_points();
	check_labels();
	check_descr_text(ui.widget->points_pair);
	ui.widget->repaint();
}

void Subdivision::draw_null_points() {
	ui.widget->set_null_points();
	check_labels();
	check_descr_text(ui.widget->points_pair);
	ui.widget->repaint();
}

void Subdivision::add() {
	double x = QString(ui.edit_x->text()).toFloat();
	double y = QString(ui.edit_y->text()).toFloat();
	double z = QString(ui.edit_z->text()).toFloat();
	check_resize_map();
	ui.widget->points_pair.emplace_back(Point_3(x, y, z), ui.widget->weight_all);
	check_labels();
	check_descr_text(ui.widget->points_pair);
	ui.widget->repaint();
}

void Subdivision::back() {
	ui.widget->flag = 0;
	ui.widget->back_points();
	check_descr_text(ui.widget->points_pair_curr);
	ui.cur_cor_cut_label->setText(QString::fromStdString("Current number of partitions: " + std::to_string(ui.widget->curr_num_of_part)));
	ui.widget->repaint();
}

void Subdivision::plus_btn() {
	ui.widget->plus = 1;
	ui.widget->count_change_weight = ui.weight_edit->text().toInt();
	check_resize_map();
	check_labels();
	ui.widget->repaint();
}

void Subdivision::minus_btn() {
	ui.widget->plus = 0;
	ui.widget->count_change_weight = ui.weight_edit->text().toInt();
	check_resize_map();
	check_labels();
	ui.widget->repaint();
}

void Subdivision::show_vector() {
	if (ui.widget->flag)
		check_descr_text(ui.widget->points_pair);
	else
		check_descr_text(ui.widget->points_pair_curr);

	check_resize_map();
	check_labels();

	ui.widget->repaint();
}
