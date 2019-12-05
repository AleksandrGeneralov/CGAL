#include "PNtriangles.h"

PNtriangles::PNtriangles(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.gl_draw, SIGNAL(clicked()), this, SLOT(GL_Draw()));
	connect(ui.custom_draw, SIGNAL(clicked()), this, SLOT(Custom_Draw()));
	connect(ui.pn_map, SIGNAL(clicked()), this, SLOT(Map_Draw()));
	connect(ui.add_map, SIGNAL(clicked()), this, SLOT(Map_Add_Lvl_Draw()));
	connect(ui.fill, SIGNAL(clicked()), this, SLOT(Change_Fill()));
}

void PNtriangles::GL_Draw() {
	if (ui.fill->isChecked())
		ui.widget->fill = 1;
	else
		ui.widget->fill = 0;

	if (ui.widget->type == -1)
		ui.widget->setDefaultTriang();
	ui.widget->type = 0;
	ui.widget->repaint();
}

void PNtriangles::Custom_Draw() {
	if (ui.fill->isChecked())
		ui.widget->fill = 1;
	else
		ui.widget->fill = 0;

	int lvl = ui.txtLvl->text().toInt();
	if (lvl < 1)
		lvl = 1;

	if (ui.widget->type == -1)
		ui.widget->setLevelTriang(lvl);
	else if (ui.widget->triang[0].getLevel() != lvl)
		ui.widget->changeTriangLevel(lvl);

	ui.widget->type = 1;
	ui.widget->repaint();
}
void PNtriangles::Map_Draw() {
	if (ui.fill->isChecked())
		ui.widget->fill = 1;
	else
		ui.widget->fill = 0;

	int lvl = ui.txt_lvl_map->text().toInt();
	if (lvl > ui.widget->map_level) {
		if (lvl == 0)
			ui.widget->set_triang_map();
		else if (lvl > 0)
			ui.widget->set_triang_map(lvl);
		ui.read_lvl->setText(QString::fromStdString("Map level: " + std::to_string(ui.widget->map_level)));
	}
	else if (lvl < ui.widget->map_level) {
		ui.widget->curr_level = lvl;
	}
	else if (lvl == ui.widget->map_level) {
		ui.widget->curr_level = ui.widget->map_level;
	}

	ui.widget->type = 2;
	ui.widget->repaint();
}

void PNtriangles::Map_Add_Lvl_Draw() {
	int lvl = ui.txt_add_map->text().toInt();
	if (lvl > 0) {
		ui.widget->add_many_levels_map(lvl);
		ui.widget->curr_level = ui.widget->map_level;
		ui.read_lvl->setText(QString::fromStdString("Map level: " + std::to_string(ui.widget->map_level)));
	}

	ui.widget->type = 2;
	ui.widget->repaint();
}

void PNtriangles::Change_Fill() {
	if (ui.fill->isChecked())
		ui.widget->fill = 1;
	else
		ui.widget->fill = 0;
	ui.widget->repaint();
}
