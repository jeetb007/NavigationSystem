/*
 * CRoute.h
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include <list>
#include <vector>

class CRoute
{
private:
	unsigned int m_nextWp;			// used as counter variables
	unsigned int m_nextPoi;
	CPoiDatabase* m_pPoiDatabase;	// used for connecting to POI DB
	CWpDatabase* m_pWpDatabase;		// used for connecting to Waypoint DB

	list<CWaypoint*> my_Route;		// store the Route elements as list objects

public:
	CRoute();
	CRoute(const CRoute& origin);						// copy constructor
	virtual ~CRoute() {}
	void connectToPoIDatabase(CPoiDatabase* pPoiDB);	// link up with a DB
	void addPoi(string namePoi, string afterWp);		// add POI to Route after corresponding Waypoint (only reference
	void connectToWpDatabase(CWpDatabase* pWpDB);		// link up with a DB
	void addWaypoint(string name);						// add Waypoints to Route (only reference)
	void print();										// print the route
	void operator+=(string name);						// operator overloading for +=
	friend CRoute operator+(const CRoute& route1, const CRoute& route2);	// operator overloading for +
	CRoute operator=(const CRoute& routeAdd);			// operator overloading for =
	const vector<const CWaypoint*> getRoute();

};

#endif /* CROUTE_H_ */
