#include <iostream>
#include <fstream>
#include "map.h"
std::ostream & operator<<(std::ostream & os, const Map & map){
	std::cout << "width: " << map.width() << " height: " << map.height() << std::endl;
	
	for (int j=0; j<map.height(); j++){
		for (int i=0; i<map.width(); i++){
			if (i == static_cast<int>(map.cntr().x) && j == static_cast<int>(map.cntr().y)){
				std::cout << 'X';
				continue; 
			}
			if (map.is_empty(i, j)==1) std::cout << " ";
			else if (map.is_empty(i, j)==0) std::cout << char(254);
			else std::cout << '@';
			//std::cout << static_cast<int>(static_cast<unsigned char>(map(i, j)))<< " ";
		}
		std::cout << std::endl;	
	}
	return os;
}

std::ofstream & operator<<(std::ofstream & os, const Map & map){
	std::cout << "width: " << map.width() << " height: " << map.height() << std::endl;
	
	for (int j=0; j<map.height(); j++){
		for (int i=0; i<map.width(); i++){
			if (map.is_empty(i, j)) std::cout << " ";
			else std::cout << (char)254;
		}
		std::cout << std::endl;	
	}
	return os;
}
