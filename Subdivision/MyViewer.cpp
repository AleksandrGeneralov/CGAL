#include "MyViewer.h"

typedef std::vector<Point_3>::iterator iter;

MyViewer::MyViewer(QWidget * parent) : QGLViewer(parent)
{
}

void MyViewer::set_default_points()
{
	points_pair = get_default_points_pair();
	points_pair_curr = points_pair;
	num_of_part = 0;
	curr_num_of_part = 0;
	map.insert(std::pair<int, Points3_pair>(num_of_part, points_pair));
	weight_all = 0;
	count_change_weight = 1;
	num_weight_all = points_pair.size();
	plus = 1;
	flag = 1;
	is_weight = init_is_weight();
}

void MyViewer::set_null_points()
{
	points_pair.clear();
	points_pair_curr.clear();
	map.clear();
	num_of_part = 0;
	curr_num_of_part = 0;
	weight_all = 0;
	count_change_weight = 1;
	num_weight_all = points_pair.size();
	plus = 1;
	flag = 1;
	is_weight = init_is_weight();
}

Points3_pair MyViewer::get_default_points_pair()
{
	Points3_pair res_vec;

	res_vec.emplace_back(std::make_pair<Point_3, int>(Point_3(0.1, 0.1, 0), 0));
	res_vec.emplace_back(std::make_pair<Point_3, int>(Point_3(0.1, 0.6, 0), 0));
	res_vec.emplace_back(std::make_pair<Point_3, int>(Point_3(0.6, 0.6, 0), 0));
	res_vec.emplace_back(std::make_pair<Point_3, int>(Point_3(0.6, 0.1, 0), 0));

	return res_vec;
}

Points3_pair MyViewer::get_null_points_pair()
{
	Points3_pair res_vec;

	return res_vec;
}

void MyViewer::back_points()
{
	if (curr_num_of_part <= 0) {
		QMessageBox::information(this, "ERROR", "Current number of partition = 0");
	}
	else {
		curr_num_of_part--;
		points_pair_curr = map.at(curr_num_of_part);
	}
}

void MyViewer::corner_cutting_pair()
{
	if (curr_num_of_part < num_of_part) 
		resize_map();

	Points3_pair points_copy = points_pair;

	for (size_t i = 0; i < points_pair.size(); i++) {
		if (i == points_pair.size() - 1)
			corner_cutting_calc_pair(points_pair[i], points_pair[0]);
		else
			corner_cutting_calc_pair(points_pair[i], points_pair[i + 1]);
		i += 2;
	}

	for (size_t i = 0; i < points_copy.size(); i++) {
		points_pair.erase(std::find(points_pair.begin(), points_pair.end(), points_copy[i]));
	}

	num_of_part++;
	curr_num_of_part++;
	map.insert(std::pair<int, Points3_pair>(num_of_part, points_pair));
	is_weight = init_is_weight();
}

void MyViewer::corner_cutting_calc_pair(p_pair p1, p_pair p2)
{
	p_pair p = p2;
	p_pair res1 = calc_point_first_1x2x1_pair(p1, p2);
	p_pair res2 = calc_point_second_1x2x1_pair(p1, p2);
	points_pair.emplace(std::find(points_pair.begin(), points_pair.end(), p), res1);
	points_pair.emplace(std::find(points_pair.begin(), points_pair.end(), p), res2);
}

p_pair MyViewer::calc_point_first_1x2x1_pair(std::pair<Point_3, int> p1, std::pair<Point_3, int> p2)
{
	double x_diff = p2.first.x() - p1.first.x();
	double y_diff = p2.first.y() - p1.first.y();
	p_pair p_res;

	if (p1.second > weight_all) {
		int power_of_weight = std::pow(2, p1.second - weight_all) * 4;
		if (x_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x(),
				p1.first.y() + (p2.first.y() - p1.first.y()) / power_of_weight,
				0), p1.second);
		else if (y_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + (p2.first.x() - p1.first.x()) / power_of_weight,
				p1.first.y(),
				0), p1.second);
		else
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + (p2.first.x() - p1.first.x()) / power_of_weight,
				p1.first.y() + (p2.first.y() - p1.first.y()) / power_of_weight,
				0), p1.second);
	}
	else {
		if (x_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x(),
				p1.first.y() + (p2.first.y() - p1.first.y()) / 4,
				0), weight_all);
		else if (y_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + (p2.first.x() - p1.first.x()) / 4,
				p1.first.y(),
				0), weight_all);
		else
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + (p2.first.x() - p1.first.x()) / 4,
				p1.first.y() + (p2.first.y() - p1.first.y()) / 4,
				0), weight_all);
	}
	return p_res;
}

p_pair MyViewer::calc_point_second_1x2x1_pair(std::pair<Point_3, int> p1, std::pair<Point_3, int> p2)
{
	double x_diff = p2.first.x() - p1.first.x();
	double y_diff = p2.first.y() - p1.first.y();
	p_pair p_res;

	if (p2.second > weight_all) {
		int power_of_weight = std::pow(2, p2.second - weight_all) * 4;
		if (x_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x(),
				p1.first.y() + 7 * (p2.first.y() - p1.first.y()) / power_of_weight,
				0), p2.second);
		else if (y_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + (power_of_weight - 1) * (p2.first.x() - p1.first.x()) / power_of_weight,
				p1.first.y(),
				0), p2.second);
		else
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + (power_of_weight - 1) * (p2.first.x() - p1.first.x()) / power_of_weight,
				p1.first.y() + (power_of_weight - 1) * (p2.first.y() - p1.first.y()) / power_of_weight,
				0), p2.second);
	}
	else {
		if (x_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x(),
				p1.first.y() + 3 * (p2.first.y() - p1.first.y()) / 4,
				0), weight_all);
		else if (y_diff == 0)
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + 3 * (p2.first.x() - p1.first.x()) / 4,
				p1.first.y(),
				0), weight_all);
		else
			p_res = std::pair<Point_3, int>(Point_3(
				p1.first.x() + 3 * (p2.first.x() - p1.first.x()) / 4,
				p1.first.y() + 3 * (p2.first.y() - p1.first.y()) / 4,
				0), weight_all);
	}
	return p_res;
}

void MyViewer::draw()
{
	if (flag)
		draw_shape(points_pair);
	else
		draw_shape(points_pair_curr);
}

void MyViewer::draw_shape(const Points3_pair shape)
{
	if (shape.size() != 0) {
		glPointSize(3.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS);
		for (int i = 0; i < shape.size(); ++i)
		{
			glVertex3f(shape[i].first.x(), shape[i].first.y(), shape[i].first.z());
		}
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < shape.size(); ++i)
		{
			glVertex3f(shape[i].first.x(), shape[i].first.y(), shape[i].first.z());
		}
		glEnd();
	}
}

void MyViewer::resize_map()
{	
	points_pair = points_pair_curr;	
	//auto it = map.find(curr_num_of_part + 1);
	for (size_t i = curr_num_of_part; i < num_of_part; i++) {
		auto it = map.find(i + 1);
		map.erase(it);
	}
	num_of_part = curr_num_of_part;
	flag = 1;
	is_weight = init_is_weight();
}

void MyViewer::init_change_weights()
{
	is_weight = init_is_weight_false();
	for (size_t i = 0; i < points_pair.size(); i++) {
		if (points_pair[i].second == weight_all) {
			num_weight_all++;
			is_weight[i] = true;
		}
	}
}

std::vector<bool> MyViewer::init_is_weight()
{
	std::vector<bool> res;
	for (size_t i = 0; i < points_pair.size(); i++) {
		if (points_pair[i].second == weight_all)
			res.push_back(true);
		else
			res.push_back(false);
	}

	return res;
}

std::vector<bool> MyViewer::init_is_weight_false()
{
	std::vector<bool> res;
	for (size_t i = 0; i < points_pair.size(); i++) {
		res.push_back(false);
	}

	return res;
}

bool MyViewer::update_is_weight(int index)
{
	if (is_weight[index]) {
		is_weight[index] = false;
		return true;
	}
	return false;
}

void MyViewer::postSelection(const QPoint & point)
{
	if (curr_num_of_part < num_of_part)
		resize_map();
	else 
		is_weight = init_is_weight();	

	qglviewer::Vec orig, dir;
	camera()->convertClickToLine(point, orig, dir);

	for (int i = 0; i < points_pair.size(); i++)
	{
		float t = (points_pair[i].first.z() - orig.z) / dir.z;
		float x = orig.x + dir.x * t;
		float y = orig.y + dir.y * t;
		if (abs(points_pair[i].first.y() - y) < 0.05f && abs(points_pair[i].first.x() - x) < 0.05f) {
			auto it = std::find(points_pair.begin(), points_pair.end(), points_pair[i]);
			if (plus) {
				it->second += count_change_weight;
				if (update_is_weight(i))
					num_weight_all--;
				if (num_weight_all == 0) {
					weight_all++;
					init_change_weights();
					//num_weight_all = points_pair.size();
				}
			}
			else {
				if (it->second == 0)
					QMessageBox::information(this, "ERROR", "Weight = 0");
				else {
					if (it->second - count_change_weight < 0)
						QMessageBox::information(this, "ERROR", "Weight < 0");
					else {
						it->second -= count_change_weight;
						if (it->second < weight_all) {
							num_weight_all = 0;
							init_change_weights();
						}
					}
					//num_weight_all++;
				}
			}
			break;
		}
	}
}

void MyViewer::init()
{
	plus = 1;
	flag = 1;
	count_change_weight = 1;
	weight_all = 0;
	num_weight_all = 0;
	num_of_part = 0;
	curr_num_of_part = 0;
	restoreStateFromFile();
}
