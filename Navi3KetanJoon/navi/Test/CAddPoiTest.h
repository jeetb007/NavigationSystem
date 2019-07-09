/*
 * FileHandling.cpp
 *
 *  Created on: 19-Jan-2016
 *      Author: Ketan Joon
 */

#ifndef CADDPOITEST_H_
#define CADDPOITEST_H_

#include <list>
#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "../myCode/CWaypoint.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CRoute.h"


class CAddPoiTest: public CppUnit:: TestFixture
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

		CPOI LalQuila(FORT, "Lal Quila", "Oldest fort in Delhi", 28.6561, 77.2408);
		CPOI QutubMinar(MONUMENT, "Qutub Minar", "World's tallest sandstone tower", 28.5243, 77.1852);
		CPOI TajMahal(MONUMENT, "Taj Mahal", "Most beautiful monument", 27.1748, 78.0417);
		CPOI RadissonBlu(RESTAURANT, "Radisson Blu", "Best hotel in Agra", 28.6561, 77.2408);
		CPOI MarineDrive(SIGHTSEEING, "Marine Drive", "Seaside road with great view", 18.9282, 72.8207);
		CPOI LeopoldCafe(RESTAURANT, "Leopold Cafe", "Best bar and cafe in Mumbai", 18.9228, 72.8318);

		m_pPoiDatabase.addPoi(LalQuila);
		m_pPoiDatabase.addPoi(QutubMinar);
		m_pPoiDatabase.addPoi(TajMahal);
		m_pPoiDatabase.addPoi(RadissonBlu);
	    m_pPoiDatabase.addPoi(MarineDrive);
		m_pPoiDatabase.addPoi(LeopoldCafe);
	}

	void connectToPoiDb(){
		m_route.connectToWpDatabase(&m_WpDatabase);
		m_route.connectToPoIDatabase(&m_pPoiDatabase);
	}

	void connectToPoiDbWithNull(){
		m_route.connectToPoIDatabase(NULL);
	}

	void addPoiTestWithDb(){
		connectToPoiDb();
		m_route.addWaypoint("Delhi");
		m_route.addPoi("Delhi", "LalQuila");
		m_route.addPoi("Mumbai", "LeopoldCafe");
	}

	void addPoiWithAbsentWaypoint(){
		m_route.connectToWpDatabase(&m_WpDatabase);
		connectToPoiDb();
		m_route.addWaypoint("Agra");
		m_route.addPoi("Agra", "TajMahal");
	}

	void addPoiWithoutConnection(){
		connectToPoiDbWithNull();
		m_route.addPoi("Agra", "TajMahal");
	}

	static CppUnit:: TestSuite* suite(){
		CppUnit:: TestSuite* suite = new CppUnit:: TestSuite("addPoiTest");
		suite->addTest(new CppUnit:: TestCaller<CAddPoiTest> ("setup", &CAddPoiTest:: setUp));

		suite->addTest(new CppUnit:: TestCaller<CAddPoiTest> ("setup", &CAddPoiTest:: connectToPoiDbWithNull));

		suite->addTest(new CppUnit:: TestCaller<CAddPoiTest> ("setup", &CAddPoiTest:: connectToPoiDb));

		suite->addTest(new CppUnit:: TestCaller<CAddPoiTest> ("setup", &CAddPoiTest:: addPoiTestWithDb));
		suite->addTest(new CppUnit:: TestCaller<CAddPoiTest> ("setup", &CAddPoiTest:: addPoiWithAbsentWaypoint));
		suite->addTest(new CppUnit:: TestCaller<CAddPoiTest> ("setup", &CAddPoiTest:: addPoiWithoutConnection));
		return suite;

	}

	void run(){

	}
};

#endif /* CADDPOITEST_H_ */
