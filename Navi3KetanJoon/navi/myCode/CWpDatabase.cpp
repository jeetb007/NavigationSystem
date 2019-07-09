/*
 * CWpDatabase.cpp
 *
 *  Created on: 06-Dec-2016
 *      Author: Ketan Joon
 */

#include "CWpDatabase.h"

CWpDatabase::CWpDatabase()
{ }

CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	return getPointerToElement(name);
}

void CWpDatabase::addWaypoint(CWaypoint const& wp)
{
	addElement(wp);
}
