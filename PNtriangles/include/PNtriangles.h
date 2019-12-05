#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PNtriangles.h"

class PNtriangles : public QMainWindow
{
	Q_OBJECT

public:
	PNtriangles(QWidget *parent = Q_NULLPTR);

public slots:
	void GL_Draw();
	void Custom_Draw();
	void Map_Draw();
	void Map_Add_Lvl_Draw();
	void Change_Fill();

private:
	Ui::PNtrianglesClass ui;
};
