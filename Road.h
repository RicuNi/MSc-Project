#pragma once

#include <vector>
#include <string>
#include<glm/glm.hpp>
using namespace std;


class Road
{
public:
	Road();
	~Road();

	string id;
	vector<glm::vec3> points;
};

