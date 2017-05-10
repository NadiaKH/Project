#include "diff_func.h"

float32 min(float32 a, float32 b, float32 c, float32 d){
	std::vector<float32>v;
	if (a!=-1) v.push_back(a);
	if (b!=-1) v.push_back(b);
	if (c!=-1) v.push_back(c);
	if (d!=-1) v.push_back(d);
	std::sort(v.begin(), v.end());
	return *(v.begin());
}


void del_comments(std::string & str){
	if (str.find("#")!=std::string::npos)
		str.erase(str.find("#"), str.size());
}


void del_spaces(std::string & str){
	while(str.size()>0 && str[0]==' '){
		str.erase(0, 1);
	}
}

std::string strtok(std::string & str){
	std::string s = "";
	del_spaces(str);
	while(str.size()>0 && str[0]!=' '){
		s+=str[0];
		str.erase(0, 1);
	}
	return s;
}


int get_value(std::string & str){
	int res = 0;
	while(str.size()>0){
		res*=10;
		res +=str[0]-48;
		str.erase(0, 1);
	}
	return res;
}

