/*
 * FileHandling.cpp
 *
 *  Created on: 08-Dec-2016
 *      Author: Ketan Joon
 */

#include "FileHandling.h"


FileHandling::FileHandling()
{
	m_Waypointname = "";
	m_Poiname = "";
}

void FileHandling::setMediaName(std::string name)
{
	m_Waypointname = name + "-wp.txt";
	m_Poiname = name + "-poi.txt";
}

bool FileHandling::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDB)
{
	string name;
	double latitude;
	double longitude;
	string description;
	t_poi type;

	//open the Waypoint file
	m_WaypointFile.open((m_Waypointname).c_str(), fstream::out);
	if(m_WaypointFile.is_open())
	{
		//create a temporary Map to store the waypoint database
		map<string, CWaypoint> temp_Waypointmap = waypointDb.getMap();
		map<string, CWaypoint>::iterator it;

		for (it = temp_Waypointmap.begin();it != temp_Waypointmap.end(); it++)
		{
			((*it).second).getAllDataByReference(name,latitude,longitude);
			m_WaypointFile << name << ";" << latitude << ";" << longitude << endl;
		}
	}
	else
	{
		cout<<"ERROR:cannot open waypoint file!!"<<endl;
		return false;
	}

	m_WaypointFile.close();

	//open the Poi file
	m_PoiFile.open((m_Poiname).c_str(), fstream::out);
	if(m_PoiFile.is_open())
	{
		//create a temporary map to store Poi database
		map<string, CPOI> temp_Poimap = poiDB.getMap();
		map<string, CPOI>::iterator it;
		for (it = temp_Poimap.begin(); it != temp_Poimap.end(); it++)
		{
			((*it).second).getAllDataByReference(name, latitude, longitude,	type, description);
			m_PoiFile << name << ";" << latitude << ";" << longitude << ";"	<< type << ";" << description << endl;
		}
	}
	else
	{
		cout << "ERROR: cannot open POI file!!" << endl;
		return false;
	}

	m_PoiFile.close();

	return true;
}

bool FileHandling::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode)
{
	string format_CSV = "";
	string value_key = "";
	int next_line = 0;
	int name_flag = 0;
	int lati_flag = 0;
	int longi_flag = 0;
	string point_name = "";
	double point_lat;
	double point_long;
	ifstream CSV_file_Waypoint, CSV_file_poi;
	CSV_file_Waypoint.open("Urlaub-wp.txt");
	CSV_file_poi.open("Urlaub-poi.txt");
	map<string, CWaypoint> map_wp = waypointDb.getMap();

	if(CSV_file_Waypoint.is_open())
	{
		if(mode==REPLACE)
		{
			map_wp.clear();

		}

		while(!CSV_file_Waypoint.eof())
		{
			getline(CSV_file_Waypoint, format_CSV);
			size_t pos = format_CSV.find(';');
			if(pos == std::string::npos)
			{
				cout<< "ERROR: no semicolon found in line " << endl;
				//return false;
			}
			else
			{
				value_key = format_CSV.substr(0,pos);
				if(value_key.empty() != true)
				{
					for(unsigned i=0; i<value_key.length(); i++)
					{
						if( !((value_key[i] >= 'a' && value_key[i] <= 'z') || (value_key[i] >= 'A' && value_key[i] <= 'Z') || value_key[i] == ' ' ))
						{
							cout<< "ERROR: incorrect name format in line " << next_line << " for the keyword "<<value_key<<endl;
							//return true;
						}
						name_flag=1;
						point_name=value_key;
					}
				}
				else
				{
					cout<<"ERROR: no characters in the "<<value_key<<endl;
					//return false;
				}
				format_CSV=format_CSV.substr(pos+1); //check in this point
				pos = format_CSV.find(';');
				if(pos==std::string::npos)
				{
					cout<<"ERROR at line "<<next_line<<" in csv text format "<<format_CSV<<endl;
					//return true;
				}
				else
				{
					value_key=format_CSV.substr(0,pos); // holds the latitude
					if(processLatLong(value_key))
					{
						lati_flag=1;
						point_lat=strtod(value_key.c_str(),NULL);
					}
					else
					{
						cout<<"latitude failure: line"<<next_line<<endl;
						//return false;
					}
					format_CSV=format_CSV.substr(pos+1); //holds the longitude

					if(processLatLong(format_CSV))
					{
						point_long=strtod(format_CSV.c_str(),NULL);
						longi_flag=1;
					}
					else
					{
						cout<<"longitude failure: line "<<next_line<<endl;
						//return false;
					}

				}
			}
			if(name_flag==1 && lati_flag==1 && longi_flag==1)
			{
				CWaypoint wayPoint;
				wayPoint.set(point_name,point_lat,point_long);
				map<string,CWaypoint>::iterator it;
				map_wp.insert(pair<string,CWaypoint>(point_name,wayPoint));
				waypointDb.addWaypoint(wayPoint);
				cout<<"Waypoint added from File: "<<point_name<<endl;
				name_flag=0; //set the flag to 0 for processing again.
				lati_flag=0;
				longi_flag=0;
				next_line=1;
			}
			else
			{
				cout<< "ERROR: check for the missing value in line" << endl;
				//return false;
			}

		}
		//return true;
	}
	else
	{
		cout << "ERROR: cannot open the File with waypoints" << endl;
	}
	CSV_file_Waypoint.close();


	return true;
}

bool FileHandling::processLatLong (string Value) const
{
	bool flag = false;		 	//flag set only when value is processed properly.
	int decimal_points = 0;		//to count the number of dots.
	if( !(Value.empty()) )		//check for empty characters.
	{
		for(unsigned i=0; i<Value.length(); i++) //check for characters other than 0-9,.,-.
		{  //check for 0-9, '.' and '-'
			if(((Value[i] >= '0' && Value[i] <= '9') || (Value[i] == '.') || (Value[i] == '-')))
			{
				if(Value[i] == '.')
				{
					decimal_points++; // for checking 2 points
				}
			}
			else
			{
				cout<<"ERROR: Invalid data encountered : " << Value << endl;
				return false;
			}
		}
		if(decimal_points > 1)
		{
			decimal_points = 0;		//print the error for more than one count.
			cout<< "ERROR: Invalid data encountered : " << Value << endl;
			return false;
		}
		else
		{
			flag=true;
		}
	}
	else
	{
		return false;
	}
	return flag; //return true for all the passing conditions

}

CPersistentStorage::~CPersistentStorage()
{
}
