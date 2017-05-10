#include <fstream>
#include <iostream>
#include <string.h>
#include "map.h"
#include "debug_output.h"
#include "occupancy_grid.h"

#define PI 3.14159265
using namespace std;
float64 str_to_float64(char * str){
	int i=0;
	int d = 1;
	float64 frac=0;
	float64 integ=0;
	while(str[i]<='9' && str[i]>= '0'){
		integ*=10;
		integ+=static_cast<int> (str[i]) - 48;
		i++;
	}
	if (str[i++]=='\0') return integ;
	while(str[i]<='9' && str[i]>= '0'){
		d*=10;
		frac+=static_cast<double>(static_cast<int> (str[i]) - 48)/d;
		i++;
	}
	return integ + frac;
}

float32 min(float32 a, float32 b){
	if (a==-1) return b;
	if (b==-1) return a;
	return std::min(a, b);
}

float32 max(float32 a, float32 b){
	if (a==-1) return b;
	if (b==-1) return a;
	return std::max(a, b);
}

int main(int argc, char * argv[]){
	
	if (argc<5){
		cout << "Incorrect number of arguments";
		return 0;
	}
	
	ifstream is;
	ofstream os;
	is.open(argv[1], ios::in|ios::binary);
	float64 x = str_to_float64(argv[2]);
	float64 y = str_to_float64(argv[3]);
	os.open(argv[4], ios::out|ios::binary);
	
	Header header;
	MapMetaData map_meta_data;
	header.read(is);
	map_meta_data.read(is);
	
	//header.print(cout);
	//map_meta_data.print(cout);

	Map map(is, map_meta_data, {x - map_meta_data.point_x, y - map_meta_data.point_y});
	//cout << "x: " << x - map_meta_data.point_x << " " << "y: " << y - map_meta_data.point_y << endl;
	//cout << map << endl;
	
	float32 angle_min = 0;
	float32 angle_max = 2*PI;
	float32 angle_increment = 0.5 * PI/180;
	float32 time_increment = 0;
	float32 scan_time = 0;
	float32 range_min = -1;
	float32 range_max = -1;
	
	float32 ranges[720];
	//float32[] intensities
	
	float32 angle;

	for (int i=0; i < 720; i++){
		angle = i * 0.5 * PI/180;
		ranges[i] = map.get_distance(angle);
		if (ranges[i]!=-1) ranges[i]*=map_meta_data.resolution;
		//cout << i << ": " << ranges[i] << endl;
		range_min = min(range_min, ranges[i]);
		range_max = max(range_max, ranges[i]);
	}
		
	header.print(os);
	os.write(reinterpret_cast<char *>(&angle_min), 4);
	os.write(reinterpret_cast<char *>(&angle_max), 4);
	os.write(reinterpret_cast<char *>(&angle_increment), 4);
	os.write(reinterpret_cast<char *>(&time_increment), 4);
	os.write(reinterpret_cast<char *>(&scan_time), 4);
	os.write(reinterpret_cast<char *>(&range_min), 4);
	os.write(reinterpret_cast<char *>(&range_max), 4);
	
	for (int i=0; i<720; i++){
		os.write(reinterpret_cast<char *>(&ranges[i]), 4);
	}
}
