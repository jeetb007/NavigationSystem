/*
 * CPOI.cpp
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#include "CPOI.h"

void CPOI::print(int format)
{
	if (this != NULL)
	{
	cout<< "\nPoint of Interest \n==================\n of type ";

	switch (m_type)
	{
		case RESTAURANT	:
			cout<< "RESTAURANT";
			break;
		case SIGHTSEEING :
			cout<< "SIGHTSEEING";
			break;
		case MUSEUM :
			cout<< "MUSEUM";
			break;
		case FORT :
			cout<< "FORT";
			break;
		case MONUMENT :
			cout<< "MONUMENT";
			break;
		default :
			cout<<"UNKNOWN";
	}
	cout<< " : " << m_description << endl;
	// Use print() of CWaypoint to print base class attributes
	CWaypoint::print(MMSS);
	}
}

CPOI::CPOI(t_poi type, string name, string description, double latitude,
		double longitude) : CWaypoint(name, latitude, longitude)
{
	m_type = type;
	m_description = description;
}
void CPOI::getAllDataByReference(string& name, double& latitude,
		double& longitutde, t_poi& type, string& description)
{
	type = m_type;
	description = m_description;
	CWaypoint::getAllDataByReference(name, latitude, longitutde);
}

ostream& operator <<(ostream& out, CPOI& CPOIobj)
{
	CPOIobj.print(MMSS);
	return out;
}
