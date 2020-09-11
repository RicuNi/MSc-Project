#include "OSMReader.h"

int OSMReader::findRefIDIndex(string id) 
{
	for (int i = 0 ; i < id_list.size() ; ++i)
	{
		if (id == id_list[i])
		{
			return i;
		}
	}
	return 0;
}

OSMReader::OSMReader()
{

}

OSMReader::~OSMReader()
{

}

void OSMReader::readfile(string OSM_File_Name)
{
	string line;

	file_name=OSM_File_Name;
	ifstream file(file_name.c_str());

	if (!file.good())
	{
		std::cout << "ERROR!!!!" << std::endl;
		exit(0);
	}
	while (!file.eof())
	{
		getline(file, line);
		//cout << line << endl;

		for(int i = 1;i< line.size();i++)
		{
			string temp;
			istringstream iss(line);
			//get bound
			if (line[2] == 'b' && line[3] == 'o' && line[4] == 'u')
			{
				//get minlat
				if (line[i - 1] == 'm' && line[i] == 'i' && line[i + 1] == 'n' && line[i + 2] == 'l' && line[i + 3] == 'a')
				{
					int l = i + 7;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					double tmp = stod(temp);
					minlat = tmp;
					//cout << "minlat:" << tmp << endl;
				}
				//get minlon
				else if (line[i - 1] == 'm' && line[i] == 'i' && line[i + 1] == 'n' && line[i + 2] == 'l' && line[i + 3] == 'o')
				{
					int l = i + 7;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					double tmp = stod(temp);
					minlon = tmp;
					//cout << "minlon:" << temp << endl;
				}
				//get maxlat
				else if (line[i - 1] == 'm' && line[i] == 'a' && line[i + 1] == 'x' && line[i + 2] == 'l' && line[i + 3] == 'a')
				{
					int l = i + 7;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					double tmp = stod(temp);
					maxlat = tmp;
					//cout << "maxlat:" << temp << endl;
				}
				//get maxlon
				else if (line[i - 1] == 'm' && line[i] == 'a' && line[i + 1] == 'x' && line[i + 2] == 'l' && line[i + 3] == 'o')
				{
					int l = i + 7;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					double tmp = stod(temp);
					maxlon = tmp;
					//cout << "maxlon:" << temp << endl;
				}
			}

			//get node
			if(line[1]=='<' && line[2] == 'n'&& line[3] == 'o')
			{ 
				//get id
				if (line[i - 1]==' ' && line[ i ] == 'i' && line[i + 1] == 'd')
				{
					int l = i + 4;
					int count = 0;
					while (count!=1)
					{
						temp = temp+line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					//long tmp = stol(temp);
					id_list.push_back(temp);
					//cout << "Id:" << temp << endl;
				}
				//get lat
				if (line[i] == 'l' && line[i + 1] == 'a' && line[i + 2] == 't')
				{
					int l = i + 5;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					double tmp = stod(temp);
					lat_list.push_back(tmp);
					//cout << "Lat:" << temp << endl;
				}
				//get lon	
				if (line[i] == 'l' && line[i + 1] == 'o' && line[i + 2] == 'n')
				{
					int l = i + 5;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					double tmp = stod(temp);
					lon_list.push_back(tmp);
					//cout << "Lon:" << temp << endl;
					//cout << " " << endl;
				}
			}
			//get way id
			if (line[1] == '<' && line[2] == 'w' && line[3] == 'a')
			{
				if (line[i - 1] == ' ' && line[i] == 'i' && line[i + 1] == 'd')
				{
					int l = i + 4;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
					wayID_list.push_back(temp);
				}
			}
			//get way ref
			if (line[1] == ' ' && line[2] == '<' && line[3] == 'n')
			{
				if (line[i - 1] == ' ' && line[i] == 'r' && line[i + 1] == 'e')
				{
					int l = i + 5;
					int count = 0;
					while (count != 1)
					{
						temp = temp + line[l];
						l++;

						if (line[l] == '"')
						{
							count++;
						}
					}
				refTemp.push_back(temp);
				//cout << temp << endl;
				}
			}
			
;
			if (line[1] == '<' && line[2] == '/' && line[3] == 'w' && line[4] == 'a' && line[5] == 'y')
			{
				wayRef_list.push_back(refTemp);
				refTemp.clear();
				break;
			}
		}

	}
	/*-----------------test--------------------------*/
	//for (int i = 0; i < lat_list.size(); i++)
	//{
	//	cout << setprecision(8) <<lat_list[i] << endl;
	//}
	//for (int i = 0; i < lon_list.size(); i++)
	//{
	//	cout << setprecision(12) << lon_list[i] << endl;
	//}
	file.close();
	
}

void OSMReader::recomputeBound()
{
	minlat = 9999999.0; maxlat = -9999999.0;
	minlon = 9999999.0; maxlon = -9999999.0;

	for (int lat_i = 0 ; lat_i < lat_list.size() ; ++lat_i)
	{
		double val = lat_list[lat_i];
		if (val > maxlat)
		{
			maxlat = val;
		}

		if (val < minlat)
		{
			minlat = val;
		}
	}

	for (int lon_i = 0; lon_i< lon_list.size(); ++lon_i)
	{
		double val = lon_list[lon_i];
		if (val > maxlon)
		{
			maxlon = val;
		}

		if (val < minlon)
		{
			minlon = val;
		}
	}
}
