#pragma once
#include<iostream>
#include <fstream>
#include<vector>
#include <string> 
#include <sstream>
//#include <iomanip>
#include<glm/glm.hpp>
using namespace std;
class OSMReader
{

public:
	double minlat, minlon, maxlat, maxlon;
	string file_name;
	double lat, lon;
	int id;

	vector<string> id_list;
	vector<double> lat_list;
	vector<double> lon_list;

	vector<string> wayID_list;
	vector<string> refTemp;
	vector<vector<string> >wayRef_list;

	int findRefIDIndex(string id);

	OSMReader();
	~OSMReader();

	void readfile(string OSM_File_Name);
	void recomputeBound();

};

