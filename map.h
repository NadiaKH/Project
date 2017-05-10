#include <iostream>
#include <fstream>
#include "diff_func.h"
#include "occupancy_grid.h"
typedef struct cell{
	float32 x;
	float32 y;
}cell;


class Map{
	public:
		Map(std::ifstream & is, MapMetaData & map_meta_data, cell cntr);
		~Map();
		
		char operator()(int i, int j) const{
			return map_[i][j];
		}
		
		int width() const{
			return width_;
		}
		
		int height() const{
			return height_;
		}
		
		int is_empty(int i, int j) const {
			if (map_[i][j] == 0 )
				return 1;
			else if (map_[i][j] == 100)
				return 0;
			else return -1;
		}
		
		cell cntr() const{
			return cntr_;
		}
		
		float32 get_distance(float32 angle) const;
		
	private:
		Map & operator=(Map &);
		Map( Map &);
		
		int width_;
		int height_;
		
		cell cntr_;
		char ** map_;
		
		bool is_intersect(float32 angle, int x, int y)const;//
		cell get_cell(float32 angle)const;//возвращает первую непустую клетку или первую клетку за пределами поля
		
		bool in_field(float32 x, float32 y)const{
			return (x>=0 && x < width_) && (y>=0 && y < height_);
		}
		void read_parameters(std::ifstream & is);
		
};
