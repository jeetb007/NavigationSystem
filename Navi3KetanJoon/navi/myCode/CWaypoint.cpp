/*
 * CWaypoint.cpp
 *
 *  Created on: 28.10.2016
 *      Author: stkejoon
 */

#include "CWaypoint.h"

CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	//m_type = WAYPOINT;
	set(name, latitude, longitude);
		#ifdef SHOWADRESS
	// Print this part of code only when SHOWADRESS defined
	cout<< m_name << " stored at " << this;
	cout<< "\nAttributes' values, sizes and location =>\n";
	cout<< m_name << " " << sizeof(m_name) << " " << &m_name << endl;
	cout<< m_latitude << " " << sizeof(m_latitude) << " " << &m_latitude << endl;
	cout<< m_longitude << " " << sizeof(m_longitude) << " " << &m_longitude << endl;
	// The attributes use 8 bytes of memory each
		#endif
}

void CWaypoint::set(string name, double latitude, double longitude)
{
	m_name = name;
	// If the values are not within permissible limit, they are set to null
	if((latitude >= -90) && (latitude <= 90))
		m_latitude = latitude;
	else
	{
		cout<< "Invalid Latitude entered! Setting to NULL...\n";
		m_latitude = 0;
	}
	if((longitude >= -180) && (longitude <= 180))
		m_longitude = longitude;
	else
	{
		cout<< "Invalid Longitude entered! Setting to NULL...\n";
		m_longitude = 0;
	}
}

void CWaypoint::print(int format)
{
	// Print the values as per desired format "Decimal/Degree"
	if(this != NULL)
	{
		//cout<< "\nWaypoint \n==================\n";
		switch (format)
		{
		case DEGREE:
			cout<< m_name << " on\n\tLat  : " << m_latitude << "\n\tLong : " << m_longitude  << endl;
			break;
		case MMSS:
			int deg, mm;
			double ss;
			transformLatitude2degmmss(deg, mm, ss);
			cout<< m_name << " on\n\tLat  : " << deg << "° " << mm << "' " << ss << "''\n";
			transformLongitude2degmmss(deg, mm, ss);
			cout<< "\tLong : " << deg << "° " << mm << "' " << ss << "''\n";
			break;
		default:
			// If correct format not selected, display a warning and use Decimal format
			cout<< "INVALID Print type! Switching to decimal format...\n";
			cout<< m_name << " on\n\tLat  : " << m_latitude << "\n\tLong : " << m_longitude  << endl;
		}
	}
}

void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss)
{
	deg = (int) m_longitude;
	mm = (int) ((m_longitude - deg)*60);
	ss = ((m_longitude - deg)*60 - mm)*60;
}

void CWaypoint::getAllDataByReference(string& name, double& latitude,
		double& longitude)
{
	//cout<< &name << &latitude << &longitude;	// Used as a testcase for Ex 1.1
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
}

/*
double CWaypoint::calculateDistance(const CWaypoint& wp)
{
	double distance;
	//Radius of Earth = 6378 km
	distance = 6378 * acos( sin(D2R*m_latitude)*sin(D2R*wp.m_latitude) +
			cos(D2R*m_latitude)*cos(D2R*wp.m_latitude) *
			cos( D2R*(wp.m_longitude - m_longitude) ));
	return distance;
}
*/

void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss)
{
	deg = (int) m_latitude;
	mm = (int) ((m_latitude - deg)*60);
	ss = ((m_latitude - deg)*60 - mm)*60;
}

//These functions can be used to access private attributes outside the scope of class
string CWaypoint::getName() const
{
	return m_name;
}

double CWaypoint::getLatitude() const
{
	return m_latitude;
}

double CWaypoint::getLongitude() const
{
	return m_longitude;
}

ostream& operator <<(ostream &out, CWaypoint & Wpobj)
{
	Wpobj.print(MMSS);
	return out;

}

