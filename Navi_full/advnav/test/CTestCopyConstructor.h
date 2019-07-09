

#ifndef CTESTCOPYCONSTRUCTOR_H_
#define CTESTCOPYCONSTRUCTOR_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
using namespace std;

class CTestCopyConstructor : public CppUnit::TestFixture
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
		CWaypoint amsterdam("amsterdam", 52.3667, 4.9000);
		CWaypoint darmstadt("darmstadt", 49.8667, 8.6500);

		m_PoiDB.addPoi(oDelhiAirport);
		m_PoiDB.addPoi(oHochschuleParking);
		m_WpDB.addWaypoint(amsterdam);
		m_WpDB.addWaypoint(darmstadt);

	}

	void testCopyConstructorwithDbConnected()
		{
			m_route.connectToWpDatabase(&m_WpDB);
			m_route.connectToPoiDatabase(&m_PoiDB);
			m_route.addWaypoint("amsterdam");
			m_route.addWaypoint("darmstadt");
			m_route.addPoi("Hochschule Parking", "amsterdam");
			m_route.addPoi("Delhi Airport", "darmstadt");
			CRoute m_route2(m_route);
			CPPUNIT_ASSERT_EQUAL(4, (int )m_route2.getRoute().size());
		}

		void testCopyConstructorwithDbNotConnected()
		{
			m_route.addWaypoint("amsterdam");
			m_route.addWaypoint("darmstadt");
			m_route.addPoi("Hochschule Parking", "amsterdam");
			m_route.addPoi("Delhi Airport", "darmstadt");
			CRoute m_route2(m_route);
			CPPUNIT_ASSERT_EQUAL(0, (int )m_route2.getRoute().size());
		}

		void testCopyConstructorForDataValidation()
		{
			m_route.connectToWpDatabase(&m_WpDB);
			m_route.connectToPoiDatabase(&m_PoiDB);
			m_route.addWaypoint("amsterdam");

			CRoute m_route2(m_route);
			CPPUNIT_ASSERT(m_route2.getRoute()==m_route.getRoute());
		}

		static CppUnit::TestSuite* suite()
		{
			CppUnit::TestSuite* suite = new CppUnit::TestSuite(
					"Overloaded = operator tests");
			suite->addTest(
					new CppUnit::TestCaller<CTestCopyConstructor>(
							"Printing the route - test",
							&CTestCopyConstructor::testCopyConstructorwithDbConnected));
			suite->addTest(
					new CppUnit::TestCaller<CTestCopyConstructor>(
							"Printing the route - test",
							&CTestCopyConstructor::testCopyConstructorwithDbNotConnected));
			suite->addTest(
					new CppUnit::TestCaller<CTestCopyConstructor>(
							"Printing the route - test",
							&CTestCopyConstructor::testCopyConstructorForDataValidation));

			return suite;
		}
};




#endif /* CTESTCOPYCONSTRUCTOR_H_ */
