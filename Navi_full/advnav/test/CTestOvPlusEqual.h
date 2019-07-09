
#ifndef CTESTOVPLUSEQUAL_H_
#define CTESTOVPLUSEQUAL_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
using namespace std;

class CTestOvPlusEqual: public CppUnit::TestFixture
{
private:
	CRoute m_route;
	CWpDatabase m_WpDB;
	CPoiDatabase m_PoiDB;
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

	void testOvpPlusEqualwithDbConnected()
	{
		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		m_route += "amsterdam";
		m_route += "Hochschule Parking";
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plusEqual operator with both database connected",
				2 == (int )m_route.getRoute().size());

	}
	void testOvpPlusEqualwithWaypointDbMissing()
	{
		m_route.connectToPoiDatabase(&m_PoiDB);

		m_route += "amsterdam";
		m_route += "Hochschule Parking";
//		CPPUNIT_ASSERT_MESSAGE(
//				"Error in overloaded plusEqual operator with both database connected",
//				0 == (int )m_route.getRoute().size());
		CPPUNIT_ASSERT_EQUAL(0 , (int )m_route.getRoute().size());
	}

	void testOvpPlusEqualwithPoiDbMissing()
	{
		m_route.connectToWpDatabase(&m_WpDB);

		m_route += "amsterdam";
		m_route += "Hochschule Parking";
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plusEqual operator with both database connected",
				1 == (int )m_route.getRoute().size());

	}
	void testOvpPlusEqualwithInvalidWaypoint()
	{
		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		m_route += "amst";
		m_route += "Hochschule Parking";
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plusEqual operator with both database connected",
				1 == (int )m_route.getRoute().size());
	}
	void testOvpPlusEqualwithInvalidPOI()
	{
		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		m_route += "amsterdam";
		m_route += "Hoch";
		CPPUNIT_ASSERT_MESSAGE(
				"Error in overloaded plusEqual operator with both database connected",
				1 == (int )m_route.getRoute().size());
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite(
				"Overloaded Plus operator tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlusEqual>(
						"Overloaded Plus Equal operator with database match",
						&CTestOvPlusEqual::testOvpPlusEqualwithDbConnected));

		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlusEqual>(
						"Overloaded Plus Equal operator with waypoint database missing",
						&CTestOvPlusEqual::testOvpPlusEqualwithWaypointDbMissing));
		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlusEqual>(
						"Overloaded Plus Equal operator with POI database missing",
						&CTestOvPlusEqual::testOvpPlusEqualwithPoiDbMissing));
		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlusEqual>(
						"Overloaded Plus  Equal operator with invalid waypoint",
						&CTestOvPlusEqual::testOvpPlusEqualwithInvalidWaypoint));

		suite->addTest(
				new CppUnit::TestCaller<CTestOvPlusEqual>(
						"Overloaded Plus Equal operator with invalid POI",
						&CTestOvPlusEqual::testOvpPlusEqualwithInvalidPOI));
		return suite;
	}
};

#endif /* CTESTOVPLUSEQUAL_H_ */
