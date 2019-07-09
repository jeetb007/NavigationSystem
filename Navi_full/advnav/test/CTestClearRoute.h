

#ifndef CTESTCLEARROUTE_H_
#define CTESTCLEARROUTE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
using namespace std;

class CTestClearRoute: public CppUnit::TestFixture
{
private:
	CRoute m_route;
	CWpDatabase m_WpDB;
	CPoiDatabase m_PoiDB;
public:
	void setUp()
	{
		CPOI oDelhiAirport(Airport, "Delhi Airport", "International  Airport",49.8, 8.65325);
		CPOI oHochschuleParking(Parking, "Hochschule Parking","only for students", 10, 20);
		m_PoiDB.addPoi(oDelhiAirport);
		m_PoiDB.addPoi(oHochschuleParking);

		CWaypoint amsterdam("amsterdam", 52.3667, 4.9000);
		CWaypoint darmstadt("darmstadt", 49.8667, 8.6500);
		m_WpDB.addWaypoint(amsterdam);
		m_WpDB.addWaypoint(darmstadt);

		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		m_route.addWaypoint("amsterdam");
		m_route.addWaypoint("darmstadt");

		m_route.addPoi("Hochschule Parking", "amsterdam");
		m_route.addPoi("Delhi Airport", "darmstadt");
	}

	void testClearRoute()
	{
		m_route.clearRoute(); // Action

		CPPUNIT_ASSERT_MESSAGE("Error in clearRoute",0==(int )m_route.getRoute().size()); // Verification
//		CPPUNIT_ASSERT_EQUAL(0, (int )m_route.getRoute().size());
	}

	static CppUnit::TestSuite* suite()
		{
			CppUnit::TestSuite* suite = new CppUnit::TestSuite("Clear Route tests");
			suite->addTest(
					new CppUnit::TestCaller<CTestClearRoute>(
							"Clearing the route - test",
							&CTestClearRoute::testClearRoute));

			return suite;
		}
};

#endif /* CTESTCLEARROUTE_H_ */
