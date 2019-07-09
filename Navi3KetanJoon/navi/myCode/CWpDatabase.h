/*
 * CWpDatabase.h
 *
 *  Created on: 06-Dec-2016
 *      Author: Ketan Joon
 */

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_

#include <map>
#include <string>

#include "CTemplate.h"
#include "CWaypoint.h"

using namespace std;

class CWpDatabase : public CTemplate <string, CWaypoint>
{
public:
	CWpDatabase();
	void addWaypoint(CWaypoint const& wp);			// Add required Waypoint in DB
	CWaypoint* getPointerToWaypoint(string name);	// To get address of specific Waypoint
};
#endif /* CWPDATABASE_H_ */
