/*
 * FileHandling.cpp
 *
 *  Created on: 19-Jan-2016
 *      Author: Ketan Joon
 */

#ifndef CADDWAYPOINT_H_
#define CADDWAYPOINT_H_

#include <list>
#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "../myCode/CWaypoint.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CRoute.h"

class CAddWaypoint: public CppUnit::TestFixture

{
private:
	CPoiDatabase m_pPoiDatabase;
	CWpDatabase m_WpDatabase;
	std::list<CWaypoint*> route;
	CRoute m_route;


public:

	void setUp(){
		CWaypoint Delhi("Neu Delhi", 28.6432, 77.1157);
		CWaypoint Agra("Agra", 27.1777, 78.0093);
		CWaypoint Mumbai("Mumbai", 18.9488, 72.8305);
		CWaypoint Goa("Goa", 14.8789, 74.4400);

		m_WpDatabase.addWaypoint(Delhi);
		m_WpDatabase.addWaypoint(Agra);
		m_WpDatabase.addWaypoint(Mumbai);
		m_WpDatabase.addWaypoint(Goa);
	}

	void connectToWaypointDb(){
		m_route.connectToWpDatabase(&m_WpDatabase);
	}

	void connectToWaypointDbWithNull(){
		m_route.connectToWpDatabase(NULL);
	}

	void addWaypointTestWithoutDb(){
		m_route.addWaypoint("Delhi");
		m_route.addWaypoint("Agra");
		m_route.addWaypoint("Mumbai");
		m_route.addWaypoint("Goa");
		CPPUNIT_ASSERT_EQUAL(0, (int) m_route.getRoute().size());
	}

	void addWaypointTestWithDb(){
		connectToWaypointDb();
		m_route.addWaypoint("Delhi");
		m_route.addWaypoint("Agra");
		m_route.addWaypoint("Mumbai");
		m_route.addWaypoint("Goa");
		m_route.addWaypoint("XYZ");
		m_route.addWaypoint("Goa");
		CPPUNIT_ASSERT_EQUAL(4, (int) m_route.getRoute().size());
	}

	void addAbsentWaypoint(){
		connectToWaypointDb();
		m_route.addWaypoint("XYZ");
	}
	void addDuplicateWaypoint(){
		connectToWaypointDb();
		m_route.addWaypoint("Delhi");
		m_route.addWaypoint("Delhi");
	}
	static CppUnit::TestSuite* suite(){
		CppUnit::TestSuite* suite = new CppUnit:: TestSuite("addWaypointTest");
		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("setUp", &CAddWaypoint::setUp));
		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("connectToWaypointTest", &CAddWaypoint::connectToWaypointDb));
		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("addWaypointTest", &CAddWaypoint::addWaypointTestWithoutDb));
		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("addWaypointTest", &CAddWaypoint::addWaypointTestWithDb));

		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("addWaypointTest", &CAddWaypoint::addDuplicateWaypoint));
		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("addWaypointTest", &CAddWaypoint::addAbsentWaypoint));
		suite->addTest(new CppUnit:: TestCaller<CAddWaypoint> ("addWaypointTest", &CAddWaypoint::connectToWaypointDbWithNull));
		return suite;
	}
};

#endif /* CADDWAYPOINT_H_ */
