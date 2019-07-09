

#ifndef CTESTGETDISTANCE_H_
#define CTESTGETDISTANCE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
using namespace std;

class CTestGetDistance: public CppUnit::TestFixture
{
private:
	CRoute m_route;
	CWpDatabase m_WpDB;
	CPoiDatabase m_PoiDB;
public:
	void setUp()
	{

	}

	void testGetDistanceToValidPoi()
	{
		CPOI oDelhiAirport(Airport, "Delhi Airport", "International  Airport",
				49.8, 8.65325);
		CPOI oHochschuleParking(Parking, "Hochschule Parking",
				"only for students", 10, 20);
		CWaypoint amsterdam("amsterdam", 52.3667, 4.9000);
		CWaypoint darmstadt("darmstadt", 49.8667, 8.6500);

		CPOI dummyP;

		m_PoiDB.addPoi(oDelhiAirport);
		m_PoiDB.addPoi(oHochschuleParking);

		m_WpDB.addWaypoint(amsterdam);
		m_WpDB.addWaypoint(darmstadt);

		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		m_route.addWaypoint("amsterdam");
		m_route.addWaypoint("darmstadt");

		m_route.addPoi("Hochschule Parking", "amsterdam");
		m_route.addPoi("Delhi Airport", "darmstadt");

		CPPUNIT_ASSERT_MESSAGE(
				"Error in getDistanceNextPoi - testing valid POI", m_route.getDistanceNextPoi(amsterdam, dummyP) != -1);
	}

	void testGetDistanceToInvalidPoi()
	{
		CPOI oDelhiAirport(Airport, "Delhi Airport", "International  Airport",
				49.8, 8.65325);
		CPOI oHochschuleParking(Parking, "Hochschule Parking",
				"only for students", 10, 20);
		CWaypoint amsterdam("amsterdam", 52.3667, 4.9000);
		CWaypoint darmstadt("darmstadt", 49.8667, 8.6500);

		m_PoiDB.addPoi(oDelhiAirport);
		m_PoiDB.addPoi(oHochschuleParking);
		CPOI dummyPoi;

		m_WpDB.addWaypoint(amsterdam);
		m_WpDB.addWaypoint(darmstadt);

		m_route.connectToWpDatabase(&m_WpDB);

		m_route.addWaypoint("amsterdam");
		m_route.addWaypoint("darmstadt");

//		CPPUNIT_ASSERT_MESSAGE(
//				"Error in getDistanceNextPoi - testing invalid /missing POI",
//				m_route.getDistanceNextPoi(amsterdam, dummyPoi) == -1);
		CPPUNIT_ASSERT_EQUAL(-1,(int )m_route.getDistanceNextPoi(amsterdam, dummyPoi));
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite(
				"getdistance function tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestGetDistance>(
						"test get distance with valid poi",
						&CTestGetDistance::testGetDistanceToValidPoi));

		suite->addTest(
				new CppUnit::TestCaller<CTestGetDistance>(
						"test get distance with Invalid or missing poi",
						&CTestGetDistance::testGetDistanceToInvalidPoi));

		return suite;
	}
};

#endif /* CTESTGETDISTANCE_H_ */
