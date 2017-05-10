#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "occupancy_grid.h"
float32 min(float32 a, float32 b, float32 c, float32 d);

void del_comments(std::string & str);

void del_spaces(std::string & str);

std::string strtok(std::string & str);

int get_value(std::string & str);
