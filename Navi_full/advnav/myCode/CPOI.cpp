/* Generated by Together */

#include "CPOI.h"
#include <iostream>
using namespace std;

#include "CWaypoint.h"

void CPOI::print(int format){

	// Printing POI details
	cout<<"Point of Interest : ";

	//POI type get destroyed on compilation (enumeration type) - hence switch case to print POI type
	switch(m_type)
	{
	case 0 :cout<<"of type Airport"<<" - "<<m_description<<endl;
		break;
	case 1:cout<<"of type ATM "<<" - "<<m_description<<endl;
		break;
	case 2:cout<<"of type Bank "<<" - "<<m_description<<endl;
		break;
	case 3:cout<<"of type Church "<<" - "<<m_description<<endl;
		break;
	case 4:cout<<"of type GasStation "<<" - "<<m_description<<endl;
		break;
	case 5:cout<<"of type Hospital "<<" - "<<m_description<<endl;
		break;
	case 6:cout<<"of type Hotel "<<" - "<<m_description<<endl;
		break;
	case 7:cout<<"of type Parking "<<" - "<<m_description<<endl;
		break;
	case 8:cout<<"of type Restaurant "<<" - "<<m_description<<endl;
		break;
	case 9:cout<<"of type RailwayStation "<<" - "<<m_description<<endl;
		break;
	case 10:cout<<"of type TouristSpot "<<" - "<<m_description<<endl;
		break;
	default:cout<<"undefined POI type"<<" - "<<m_description<<endl;
		break;
	}

	switch(format){
		case 1:
			CWaypoint::print(Degree);   // Call print function to print in Decimal format
			break;
		case 2:
			CWaypoint::print(DMS);   // Call print function to print in Degree Minutes seconds format
			break;
		default: cout<<"Invalid print format selected"<<endl;
		    break;
		}

}

CPOI::CPOI(t_poi type, string name, string description,double latitude,double longitude): CWaypoint(name,latitude,longitude) {

    //Initializing the member and derived variables
	m_type = type;
	m_description = description;
	CWaypoint::set(name,latitude,longitude);
}

CPOI::~CPOI() {
	//CPOI destructor
}

void CPOI::getAllDataByReference(string& name, double & latitude, double & longitude, t_poi& type, string& description) const{

	//return all details related to a POI as reference
	type = m_type;
	description = m_description;
	CWaypoint::getAllDataByReference(name,latitude,longitude);
}

t_poi CPOI::getType(){
	return m_type;
}

string CPOI::getDescription(){
	return m_description;
}

ostream& operator<<(ostream& os, CPOI & obj){

	    // Printing POI details
		os<<"Point of Interest : ";

		//POI type get destroyed on compilation (enumeration type) - hence switch case to print POI type
		switch(obj.m_type)
		{
		case 0:
			os<<"of type Airport"<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 1:
			os<<"of type ATM "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 2:
			os<<"of type Bank "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 3:
			os<<"of type Church "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 4:
			os<<"of type GasStation "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 5:
			os<<"of type Hospital "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 6:
			os<<"of type Hotel "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 7:
			os<<"of type Parking "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 8:
			os<<"of type Restaurant "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 9:
			os<<"of type RailwayStation "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		case 10:
			os<<"of type TouristSpot "<<" - "<<obj.m_description;
			cout<<endl;
			break;
		default:
			os<<"undefined POI type"<<" - "<<obj.m_description;
			cout<<endl;
			break;
		}

		obj.CWaypoint::print(DMS);

return(os);
}
