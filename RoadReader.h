#pragma once

#include "OSMReader.h"
#include "Road.h"

static const double RoadWidth = 0.05f;

class RoadReader
{
public:
	RoadReader();
	~RoadReader();

	void readRoad(OSMReader& osmReader);
	
	vector<Road> roads;

	float computeGLPointVal(double coord, double minGLVal, double maxGLVal, double minCoord, double maxCoord);
};

