/* Generated by Together */

#include "CWaypoint.h"
#include<math.h>
#include <iostream>
using namespace std;

CWaypoint::CWaypoint(string name, double latitude, double longitude){
	//CWaypoint constructor

	//setting values to the class attributes
	set(name, latitude, longitude);

    #ifdef SHOWADRESS
	cout<<"Object created at: "<<this<<endl;
    cout<<" Atribute name : "<<name<<" of type string and of size "<<sizeof(name)<<" bytes at address "<<&name<<endl;
    cout<<" Atribute latitude : "<<latitude<<" of type double and of size "<<sizeof(latitude)<<" bytes at address "<<&latitude<<endl;
    cout<<" Atribute longitude : "<<longitude<<" oftypedouble and of size "<<sizeof(longitude)<<" bytes at address "<<&longitude<<endl;
    #endif
}

void CWaypoint::getAllDataByReference(string& name, double & latitude, double & longitude) const{

	//return all details related to a POI /Waypoint - name, latitude, longitude
	name=m_name;
	latitude=m_latitude;
	longitude=m_longitude;
}

string CWaypoint::getName() const{
	//returns m_name attribute
	return (m_name);
}

double CWaypoint::getLatitude() const{
	//returns m_latititude attribute
	return(m_latitude);
}


double CWaypoint::getLongitude() const{
	//returns m_longitude attribute
	return(m_longitude);
}

double CWaypoint::calculateDistance(const CWaypoint& wp){
	//calculating distance between two points

	//creating temporary variables for distance calculation as all math functions in formula takes radian values as input.
	double dist, latitude1,latitude2,longitude1,longitude2;

	//RadDeg defined in header file, for conversion usage radian - degree
	latitude1=this->m_latitude/RadDeg;
	latitude2=wp.m_latitude/RadDeg;
	longitude1=this->m_longitude/RadDeg;
	longitude2=wp.m_longitude/RadDeg;

	//formula for calculating distance between two points, R - radius of earth defined in header file
	dist = R*acos(sin(latitude1)*sin(latitude2)+cos(latitude1)*cos(latitude2)*cos(longitude2-longitude1));

	return(dist);
}

void CWaypoint::print(int format){

	// Print Waypoint or POI in either Decimal or Degree-Minute-Second format

	int deg,mm;
	double ss;

	//Printing lat long values
	switch(format)
	{
	case 1: //print in Decimal format
		    cout<<m_name<<" on latitude = "<<m_latitude<<" and longitude = "<<m_longitude<<endl;
		    break;

	case 2: // print in DMS Degree Minute Second format
		    transformLatiude2degmmss(deg, mm, ss);    //Convert latitude to DMS format
		    cout<<m_name<<" on latitude = "<<deg<<"deg "<<mm<<"mm " <<ss<<"ss ";

		    transformLongitude2degmmss(deg, mm, ss);  //Convert longitude to DMS format
		    cout<<"and longitude = "<<deg<<"deg "<<mm<<"mm " <<ss<<"ss "<<endl;
		    break;

	default: cout<<"Invalid Entry"<<endl;
	         break;
	}
}


void CWaypoint::set(string name, double latitude, double longitude){

	//setting value to attributes

	//Check if attributes are not out of bounds
	if (latitude > 90 || latitude < -90 || longitude > 180 || longitude < -180)
	{
		//assigning values to zero as some or all entries are out bounds
		m_name = "Invalid Coordinates";
		m_latitude = 0;
		m_longitude = 0;
		cout<<"Invalid coordinate entry, setting latitude and longitude values to zero "<<endl;
	}

	else
	{
		//Writing correct values to the attributes as all are in proper limits
		m_name = name;
		m_latitude = latitude;
		m_longitude = longitude;
	}
}

void CWaypoint::transformLatiude2degmmss(int & deg, int & mm, double & ss){

	// Converting latitude to Degree-Minute-Second format.

    //info 60min = 3600s = 1 deg

	double decValueDeg, decValueMM;

	//getting decimal portion for degree calculation
	deg = m_latitude;
	decValueDeg = m_latitude - deg;

	//getting decimal portion for MM calculation
	decValueMM = decValueDeg * 60;
	mm = decValueMM;
	decValueMM = decValueMM - mm;

	ss = decValueMM * 3600;
}


void CWaypoint::transformLongitude2degmmss(int & deg, int & mm, double & ss){

	// Converting longitude to Degree-Minute-Second format.

	//info 60min = 3600s = 1 deg

	double decValueDeg,decValueMM;

	//getting decimal portion for degree calculation
	deg = m_longitude;
	decValueDeg = m_longitude - deg;

	//getting decimal portion for MM calculation
	decValueMM = decValueDeg * 60;
	mm = decValueMM;
	decValueMM=decValueMM-mm;

	ss = decValueMM* 3600;
}

CWaypoint::~CWaypoint() {
}

ostream& operator<<(ostream& os, CWaypoint & obj){

	// Overloaded << operator function
	int deg,mm;
	double ss;

	obj.transformLatiude2degmmss(deg,mm,ss);    //Convert latitude to DMS format
	os << obj.m_name << " on latitude = " << deg << "deg " << mm << "mm " << ss<< "ss ";

	obj.transformLongitude2degmmss(deg, mm, ss);  //Convert longitude to DMS format
	os << "and longitude = " << deg << "deg " << mm << "mm " << ss << "ss ";
	cout<< endl;

return(os);
}
