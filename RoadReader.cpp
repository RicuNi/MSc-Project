#include "RoadReader.h"



RoadReader::RoadReader()
{
}


RoadReader::~RoadReader()
{
}

void RoadReader::readRoad(OSMReader & osmReader)
{
	double minGLX = -200, maxGLX = 200;
	double minGLY = -200, maxGLY = 200;

	double latMin = osmReader.minlat, latMax = osmReader.maxlat;
	double lonMin = osmReader.minlon, lonMax = osmReader.maxlon;

	double latMinus = latMax - latMin;
	double lonMinus = lonMax - lonMin;
	if (lonMinus > latMinus)
	{
		minGLX *= latMinus / lonMinus;
		maxGLX *= latMinus / lonMinus;
	}
	else
	{
		minGLY *= lonMinus / latMinus;
		maxGLY *= lonMinus / latMinus;
	}

	glm::vec3 prePoint(0, 0, 0);
	for (int i = 0 ; i < osmReader.wayID_list.size() ; ++i)
	{
		Road road;
		road.id = osmReader.wayID_list[i];

		for (int ref_i = 0; ref_i < osmReader.wayRef_list[i].size(); ++ref_i)
		{
			int refIDIndex = osmReader.findRefIDIndex(osmReader.wayRef_list[i][ref_i]);
			double lat = osmReader.lat_list[refIDIndex];
			double lon = osmReader.lon_list[refIDIndex];

			double x = computeGLPointVal(lat, minGLX, maxGLX, latMin, latMax);
			double y = computeGLPointVal(lon, minGLY, maxGLY, lonMin, lonMax);
			glm::vec3 currentPoint(x,
				0,
				y);

			glm::vec3 dir(currentPoint.z - prePoint.z,
				0,
				prePoint.x - currentPoint.x);
			dir = (float)RoadWidth * glm::normalize(dir);
			
			if (ref_i != 0)
			{
				road.points.push_back(glm::vec3(currentPoint.x, 0.1, currentPoint.z));
				road.points.push_back(glm::vec3(currentPoint.x, 0.1, currentPoint.z) + dir);
				road.points.push_back(glm::vec3(currentPoint.x, 0.1, currentPoint.z) - dir);
				road.points.push_back(glm::vec3(prePoint.x, 0.1, prePoint.z) - dir);
				road.points.push_back(glm::vec3(prePoint.x, 0.1, prePoint.z) + dir);

			}

			prePoint = currentPoint;
		}
		roads.push_back(road);
	}
}

float RoadReader::computeGLPointVal(double coord, double minGLVal, double maxGLVal, double minCoord, double maxCoord)
{
	float t = (coord - minCoord) / (maxCoord - minCoord);
	return t * (maxGLVal - minGLVal) + minGLVal;
}
