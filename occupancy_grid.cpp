#include "occupancy_grid.h"

void Header::read(std::ifstream & is){
	is.read(reinterpret_cast<char *>(&seq), 4);
	is.read(reinterpret_cast<char *>(&sec), 4);
	is.read(reinterpret_cast<char *>(&nsec), 4);
	is.read(reinterpret_cast<char *>(frame_id), 2);
}

void MapMetaData::read(std::ifstream & is){
	is.read(reinterpret_cast<char *>(&sec), 4);
	is.read(reinterpret_cast<char *>(&nsec), 4);
	
	is.read(reinterpret_cast<char *>(&resolution),4);
	
	is.read(reinterpret_cast<char *>(&width), 4);
	is.read(reinterpret_cast<char *>(&height), 4);
	
	is.read(reinterpret_cast<char *>(&point_x), 8);
	is.read(reinterpret_cast<char *>(&point_y), 8);
	is.read(reinterpret_cast<char *>(&point_z), 8);
	
	is.read(reinterpret_cast<char *>(&orient_x), 8);
	is.read(reinterpret_cast<char *>(&orient_y), 8);
	is.read(reinterpret_cast<char *>(&orient_z), 8);
	is.read(reinterpret_cast<char *>(&orient_w), 8);
}

void Header::print(std::ostream & os){
	os << "Header" << std::endl;
	os << "seq: " << seq << std::endl;
	os << "sec: " << sec << std::endl;
	os << "nsec: " << nsec << std::endl;
	os << "frame_id: " << frame_id << std::endl;
}

void Header::print(std::ofstream & os){
	os.write(reinterpret_cast<char *>(&seq), 4);
	os.write(reinterpret_cast<char *>(&sec), 4);
	os.write(reinterpret_cast<char *>(&nsec), 4);
	os.write(reinterpret_cast<char *>(frame_id), 2);
}

void MapMetaData::print(std::ostream & os){
	os << "MapMetaData" << std::endl;
	os << "sec: " << sec << std::endl;
	os << "nsec: " << nsec << std::endl;
	os << "resolution: " << resolution << std::endl;
	os << "width: " << width << std::endl;
	os << "height: " << height << std::endl;
	os << "point_x: " << point_x << std::endl;
	os << "point_y: " << point_y << std::endl;
	os << "point_z: " << point_z  << std::endl;
	os << "orient_x: " << orient_x << std::endl;
	os << "orient_y: " << orient_y << std::endl;
	os << "orient_z: " << orient_z << std::endl;
	os << "orient_w: " << orient_w << std::endl;
}
