/*
 * CWpDatabase.h
 *  Class stores Waypoint Database
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_

#include <map>
//using std::map;
//using std::pair;

#include "CWaypoint.h"
#include "CDatabaseTemplate.h"

#include <fstream>

namespace std {
class CWpDatabase: public CDatabaseTemplate<string, CWaypoint> {

public:

	/**
	 * CWpDatabase constructor
	 */
	CWpDatabase();

	/**
	 * addWaypoint function - add waypoint  to waypoint database
	 * @param wp - waypoint object that is added to database
	 */
	void addWaypoint(CWaypoint const & wp);

	/**
	 * getPointerToWaypoint - checks for Waypoint name in Waypoint database and
	 *                        returns pointer to matching Waypoint
	 * @param name - waypoint name that is to be checcked
	 * @return - returns pointer to matching Waypoint
	 */
	CWaypoint* getPointerToWaypoint(string name);

	// for testing CPoiDatabase
	void print();

	/**
	 * shareWpDBmembers - share the Waypoint map and iterator for the persistent class use
	 * @param sharetWpMap - Waypoint map
	 * @param shareIt - Waypoint map iterator
	 */
	void shareWpDBmembers(map<string, CWaypoint>& sharetWpMap,
			map<string, CWaypoint>::iterator& shareIt) const;

	/**
	 * clearWaypointMap - function to clear the Waypoint map
	 */
	void clearWaypointMap();

	map<string, CWaypoint>* getMapCWP();

private:
	map<string, CWaypoint> m_WayPointMap;  // Creating map object
	map<string, CWaypoint>::iterator m_it; // Creating an iterator

};
}
#endif /* CWPDATABASE_H_ */
