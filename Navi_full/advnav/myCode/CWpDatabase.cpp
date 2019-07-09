/*
 * CWpDatabase.cpp
 *
 */

#include "CWpDatabase.h"

#include <iostream>
using namespace std;

CWpDatabase::CWpDatabase() {
	//Constructor
}

void CWpDatabase::addWaypoint(CWaypoint const & wp) {

	//add Waypoint to Waypoint Database
	//m_WayPointMap.insert(pair<string, CWaypoint>(wp.getName(),wp));

	addToDB(wp);
}

CWaypoint* CWpDatabase::getPointerToWaypoint(string name) {

	return getPointerToDB(name);

	// checks for Waypoint name in Waypoint database and returns pointer to matching Waypoint
	// parameter name : holds a Waypoint name which is to be checked

/*	CWaypoint* p2Waypoint;  //Creating a Pointer of type CWaypoint

	p2Waypoint=NULL;  //Pointer value to NULL, if unaltered => Waypoint not in database

	//checking Waypoint database for Waypoint - with passed parameter name -
	m_it = m_WayPointMap.find(name);

	// find function returns map-end if no Waypoint match found

	if (m_it != m_WayPointMap.end())
	{
		// Waypoint with same name present in Waypoint Database
		p2Waypoint = &(m_it->second);
	}

	else
	{
		// Code get executed if Waypoint not present in Waypoint Database
		cout << endl << "ERROR: Could not find Waypoint in the Database" << endl;
	}

	//returning pointer to the Waypoint - with passed parameter name - or NULL if Waypoint not in Waypoint data pool
	return(p2Waypoint);*/
}

void CWpDatabase::print() {

	printDB();

	/*unsigned int i = 0;
	//printing all elements in waypoint database map container
	for (m_it = m_WayPointMap.begin(); m_it != m_WayPointMap.end(); ++m_it)
	{
		cout <<endl<<++i<<endl;
		m_it->second.print(2);
	}*/
}

void CWpDatabase::shareWpDBmembers(map<string, CWaypoint>& sharetWpMap,	map<string, CWaypoint>::iterator& shareIt) const{

	//share the Waypoint map and iterator for the persistent class use
	sharetWpMap=m_WayPointMap;
	shareIt=m_it;
}

void CWpDatabase::clearWaypointMap() {

	// Clear the Waypoint map
	m_WayPointMap.clear();
}

map<string,CWaypoint>* CWpDatabase::getMapCWP() {
		return getMap();
	}
