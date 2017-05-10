#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
//#include <float.h>
#include "map.h"

bool Map::is_intersect(float32 angle, int x, int y) const{
	float32 w1 = (cntr_.x - x);
	float32 w2 = (cntr_.x - (x + 1));
	float32 h1 = (cntr_.y - y);
	float32 h2 = (cntr_.y - (y + 1));
	float32 tg = tan(angle);
	return ((tg * w1 - h1)*(tg * w1 - h2) <= 0 || (tg * w2 - h1) * (tg * w2 - h2) <= 0);
} 


float32 Map::get_distance(float32 angle) const{
	cell c = get_cell(angle);
	//std::cout << "c.x: " << c.x << " c.y: " << c.y << std::endl;
	if (!in_field(c.x, c.y)) return -1; 
	//std::cout << "in field" << std::endl;
	c.x = static_cast<int> (c.x);
	c.y = static_cast<int> (c.y);
	float32 w1 = (cntr_.x - c.x);
	float32 w2 = (cntr_.x - (c.x + 1));
	float32 h1 = (cntr_.y - c.y);
	float32 h2 = (cntr_.y - (c.y + 1));
	float32 tg = tan(angle);
	float32 ctg = 1/tan(angle);
	float32 l1, l2, l3, l4;
	if ((tg * w1 - h1)*(tg * w1 - h2) <=0) l1 = sqrt(w1*w1*(1 + tg*tg));
	else l1 = -1;
	if ((tg * w2 - h1) * (tg * w2 - h2) <= 0) l2 = sqrt(w2*w2*(1 + tg*tg));
	else l2 = -1;
	if ((ctg * h1 - w1)* (ctg * h1 - w2) <=0) l3 = sqrt(h1*h1*(1+ctg*ctg));
	else l3 = -1;
	if ((ctg * h2 - w1)* (ctg * h2 - w2) <=0) l4 = sqrt(h2*h2*(1+ctg*ctg));
	else l4 = -1;
	//std::cout << "min( " << l1 << ", " << l2 << ", " << l3 << ", " << l4 << ")" << std::endl;
	return min(l1, l2, l3, l4);
}


cell Map::get_cell(float32 angle) const{//angle in rad
	int dir_x;
	int dir_y;
	if (cos(angle) >=0) dir_x = 1;
	else dir_x = -1;
	if (sin(angle) >=0) dir_y = 1;
	else dir_y = -1;
	float32 x = cntr_.x;
	float32 y = cntr_.y;
	do {
		if (is_intersect(angle, x + dir_x, y)) x += dir_x;
		else y += dir_y;
	} while(in_field(x, y) && is_empty(x, y));
	//return {static_cast<int>(x), static_cast<int>(y)};
	return {x, y};
}


/*void Map::read_parameters(std::ifstream & is){
	std::string str;
	std::string s;
	std::vector<std::string> v;
	while (v.size()<4){
		std::getline(is, str);
		del_comments(str);
		while(str.size()>0){
			s = strtok(str);
			if (s.size()>0)
				v.push_back(s);
		}
	}
	width_ = get_value(v[1]);
	height_ = get_value(v[2]);
	hue_ = get_value(v[3]);
}*/


Map::Map(std::ifstream & is, MapMetaData & map_meta_data, cell cntr): cntr_(cntr){
	width_ = map_meta_data.width;
	height_ = map_meta_data.height;
	
	map_ = new char * [width_];
	
	for (int i=0; i<width_; i++)
		map_[i] = new char [width_];
	
	char byte;	
	for (int j = 0; j < height_; j++)
		for (int i = 0; i < width_; i++){
			is.read(&byte, 1);
			map_[i][j] = byte;
		}
}


Map::~Map(){
	for (int i=0; i<width_; i++)
		delete [] map_[i];
	delete [] map_;
}
