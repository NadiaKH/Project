#include <fstream>
#include <iostream>
#pragma once

typedef float float32;
typedef uint32_t uint32;
typedef double float64;
typedef char int8;
typedef unsigned char uint8;
 

typedef struct Header{
	uint32 seq;
	uint32 sec;
	uint32 nsec;
	char frame_id[2];
	void read(std::ifstream & is);
	void print(std::ostream & os);
	void print(std::ofstream & os);
}Header;


typedef struct MapMetaData{
	uint32 sec;
	uint32 nsec;
	float32 resolution;
	uint32 width;
	uint32 height;
	float64 point_x, point_y, point_z;
	float64 orient_x, orient_y, orient_z, orient_w;
	void read(std::ifstream & is);
	void print(std::ostream & os);
}MapMetaData;


