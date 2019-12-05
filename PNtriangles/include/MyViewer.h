#pragma once
#include <QGLViewer/qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>
#include <PNtrianglesDraw.h>
#include <QtGui/qevent.h>
#include <algorithm>

typedef std::pair<int, PNtrianglesDraw> pair_pn; //int - number of triangle of oxahedron
typedef std::unordered_multimap<int, pair_pn> type_map; //int - level of map

class MyViewer : public QGLViewer
{
public:
	MyViewer(QWidget* parent);
	Points3 points;
	int type;
	bool fill;

	// Vector data structure
	std::vector<PNtrianglesDraw> triang;
	std::vector<PNtrianglesDraw> getTriang(int _level);	
	void changeTriangLevel(int _level);
	void setDefaultTriang();
	void setLevelTriang(int _level);

	// Unordered_map data structure
	int map_level;
	int curr_level;
	type_map triang_map;
	type_map getTriangMap();
	void set_triang_map();
	void set_triang_map(int num_lvl);
	void add_level_map();
	void add_many_levels_map(int num_lvl);
	void draw_map(int lvl);
	void draw_map(int lvl, int n_pn);

protected:
	virtual void draw();
	virtual void init();
};
