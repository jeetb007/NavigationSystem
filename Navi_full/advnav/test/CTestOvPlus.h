

#ifndef CTESTOVPLUS_H_
#define CTESTOVPLUS_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
using namespace std;

class CTestOvPlus: public CppUnit::TestFixture
{
private:
	CRoute m_route1, m_route2,m_route3;
	CWpDatabase m_WpDB;
	CPoiDatabase m_PoiDB;
	CWpDatabase m_WpDB2;
	CPoiDatabase m_PoiDB2;
public:
	void setUp()
	{
		CPOI oDelhiAirport(Airport, "Delhi Airport", "International  Airport",
				49.8, 8.65325);
		CPOI oHochschuleParking(Parking, "Hochschule Parking",
				"only for students", 10, 20);
		m_PoiDB.addPoi(oDelhiAirport);
		m_PoiDB.addPoi(oHochschuleParking);

		CWaypoint amsterdam("amsterdam", 52.3667, 4.9000);
		CWaypoint darmstadt("darmstadt", 49.8667, 8.6500);
		m_WpDB.addWaypoint(amsterdam);
		m_WpDB.addWaypoint(darmstadt);

	}

	void testOvpPluswithDbMatch()
	{
		m_route1.connectToWpDatabase(&m_WpDB);
		m_route1.connectToPoiDatabase(&m_PoiDB);

		m_route2.connectToWpDatabase(&m_WpDB);
		m_route2.connectToPoiDatabase(&m_PoiDB);

		m_route1.addWaypoint("amsterdam");
		m_route2.addWaypoint("darmstadt");

		m_route1.addPoi("Hochschule Parking", "amsterdam");
		m_route2.addPoi("Delhi Airport", "darmstadt");

		m_route3 = m_route2 + m_route1;

		// Verification
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plus function, with both database match",
				4 == (int )m_route3.getRoute().size());

	}

	void testOvpPluswithWaypointDbMismatch()
	{
		m_route1.connectToWpDatabase(&m_WpDB);
		m_route1.connectToPoiDatabase(&m_PoiDB);

		m_route2.connectToWpDatabase(&m_WpDB2);
		m_route2.connectToPoiDatabase(&m_PoiDB);

		m_route1.addWaypoint("amsterdam");
		m_route1.addPoi("Hochschule Parking", "amsterdam");

		m_route2.addWaypoint("darmstadt");
		m_route2.addPoi("Delhi Airport", "darmstadt");

		m_route3 = m_route1 + m_route2;

		// Verification
//		CPPUNIT_ASSERT_MESSAGE(
//				"Error in overloaded plus function, with Waypoint database mismatch",
//				0 == (int )m_route3.getRoute().size());
		CPPUNIT_ASSERT_EQUAL(0 ,(int )m_route3.getRoute().size());
	}

	void testOvpPluswithPoiDbMismatch()
	{
		m_route1.connectToWpDatabase(&m_WpDB);
		m_route1.connectToPoiDatabase(&m_PoiDB);

		m_route2.connectToWpDatabase(&m_WpDB);
		m_route2.connectToPoiDatabase(&m_PoiDB2);

		m_route1.addWaypoint("amsterdam");
		m_route2.addWaypoint("darmstadt");

		m_route1.addPoi("Hochschule Parking", "amsterdam");
		m_route2.addPoi("Delhi Airport", "darmstadt");

		m_route3 = m_route1 + m_route2;

		// Verification
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plus function, with POI database mismatch",
				0 == (int )m_route3.getRoute().size());
	}

	void testOvpPluswithWaypointDbMissing()
	{
		m_route1.connectToPoiDatabase(&m_PoiDB);

		m_route2.connectToWpDatabase(&m_WpDB);
		m_route2.connectToPoiDatabase(&m_PoiDB);

		m_route1.addWaypoint("amsterdam");
		m_route2.addWaypoint("darmstadt");

		m_route1.addPoi("Hochschule Parking", "amsterdam");
		m_route2.addPoi("Delhi Airport", "darmstadt");

		m_route3 = m_route2 + m_route1;

		// Verification
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plus function, with waypoint database missing",
				0 == (int )m_route3.getRoute().size());
	}

	void testOvpPluswithPoiDbMissing()
	{
		m_route1.connectToWpDatabase(&m_WpDB);

		m_route2.connectToWpDatabase(&m_WpDB);
		m_route2.connectToPoiDatabase(&m_PoiDB);

		m_route1.addWaypoint("amsterdam");
		m_route2.addWaypoint("darmstadt");

		m_route1.addPoi("Hochschule Parking", "amsterdam");
		m_route2.addPoi("Delhi Airport", "darmstadt");

		m_route3 = m_route2 + m_route1;

		// Verification
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plus function, with POI database missing",
				0 == (int )m_route3.getRoute().size());

	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Overloaded Plus operator tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlus>(
						"Overloaded Plus with database match",
						&CTestOvPlus::testOvpPluswithDbMatch));

		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlus>(
						"Overloaded Plus with waypoint database mismatch",
						&CTestOvPlus::testOvpPluswithWaypointDbMismatch));
		suite->addTest(
						new CppUnit::TestCaller<CTestOvPlus>(
								"Overloaded Plus with POI database mismatch",
								&CTestOvPlus::testOvpPluswithPoiDbMismatch));
		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlus>(
						"Overloaded Plus with waypoint database missing",
						&CTestOvPlus::testOvpPluswithWaypointDbMissing));

		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlus>(
						"Overloaded Plus with POI database missing",
						&CTestOvPlus::testOvpPluswithPoiDbMissing));
		return suite;
	}
};

#endif /* CTESTOVPLUS_H_ */
