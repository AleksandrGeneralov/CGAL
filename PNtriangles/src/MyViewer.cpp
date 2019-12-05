#include "MyViewer.h"

typedef std::vector<Point_3>::iterator iter;

MyViewer::MyViewer(QWidget * parent) : QGLViewer(parent)
{

}

std::vector<PNtrianglesDraw> MyViewer::getTriang(int _level)
{
	std::vector<PNtrianglesDraw> _triang;

	_triang.emplace_back(
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1), _level
	);
	_triang.emplace_back(
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1), _level
	);
	_triang.emplace_back(
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1), _level
	);
	_triang.emplace_back(
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1), _level
	);
	_triang.emplace_back(
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1), _level
	);
	_triang.emplace_back(
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1), _level
	);
	_triang.emplace_back(
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1), _level
	);
	_triang.emplace_back(
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1), _level
	);
	return _triang;
}

type_map MyViewer::getTriangMap()
{	
	type_map pn;
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(1, PNtrianglesDraw(
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(2, PNtrianglesDraw(
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(3, PNtrianglesDraw(
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, 1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(4, PNtrianglesDraw(
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, 1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(5, PNtrianglesDraw(
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(6, PNtrianglesDraw(
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1),
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, 1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(7, PNtrianglesDraw(
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, -1)
	))));
	pn.insert(std::make_pair<int, pair_pn>(0, std::make_pair(8, PNtrianglesDraw(
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1),
		Point_3(0, -1, 0), Point_3(-1, 0, 0), Point_3(0, 0, -1)
	))));
	return pn;
}

void MyViewer::set_triang_map()
{
	triang_map = getTriangMap();
	map_level = 0;
	curr_level = 0;
}

void MyViewer::set_triang_map(int num_lvl)
{
	triang_map = getTriangMap();
	map_level = 0;	
	add_many_levels_map(num_lvl);
	curr_level = map_level;
}

void MyViewer::add_level_map()
{
	int finish_el = 8 * pow(4, map_level);
	int cnt = 0;
	for (auto it = triang_map.begin(); it != triang_map.end(); it++) {
		if (cnt == finish_el)
			break;
		if (it->first == map_level) {
			it->second.second.add_element_map(triang_map, map_level, it->second.first);
			cnt++;
		}
	}
	map_level++;
}

void MyViewer::add_many_levels_map(int num_lvl)
{
	for (int i = 0; i < num_lvl; i++)
		add_level_map();
}

void MyViewer::draw_map(int lvl)
{
	auto range = triang_map.equal_range(lvl);
	for (auto it = range.first; it != range.second; it++) {
		it->second.second.drawTriangleGL();
	}
}

void MyViewer::draw_map(int lvl, int n_pn)
{
	auto range = triang_map.equal_range(lvl);
	for (auto it = range.first; it != range.second; it++) {
		if (it->second.first == n_pn || it->second.first == n_pn + 1 || it->second.first == n_pn + 4 || it->second.first == n_pn + 5)
			it->second.second.drawTriangleGL();
	}
}

void MyViewer::changeTriangLevel(int _level)
{
	for (auto& pn : triang)
		pn.setLevel(_level);
}

void MyViewer::setDefaultTriang()
{
	triang = getTriang(1);
}

void MyViewer::setLevelTriang(int _level)
{
	triang = getTriang(_level);
}

void MyViewer::draw()
{
	drawAxis();
	if (!fill)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (type == 2) {
		draw_map(curr_level);
		//draw_map(curr_level, 1);
	}

	for (auto pn : triang) {
		switch (type)	{
		case 0:
			pn.drawTriangleGL();
			break;
		case 1:
			pn.drawTriangleCustom();
			break;
		default:
			break;
		}
	}
}

void MyViewer::init()
{
	curr_level = 0;
	map_level = -1;
	type = -1;
	restoreStateFromFile();
}
