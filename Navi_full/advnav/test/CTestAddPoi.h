
#ifndef CTESTADDPOI_H_
#define CTESTADDPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
using namespace std;

class CTestAddPoi: public CppUnit::TestFixture{
private:
	CRoute m_route;
	CWpDatabase m_WpDB;
	CPoiDatabase m_PoiDB;
public:
	void setUp()
	{
		CWaypoint berlin("berlin", 52.5167, 13.3833);
		m_WpDB.addWaypoint(berlin);

		CPOI oHochschuleParking(Parking, "Hochschule Parking","only for students", 10, 20);
		m_PoiDB.addPoi(oHochschuleParking);
	}

	void testAddPoiwithDbsConnected()
	{
		// Precondition
		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		// Action
		m_route.addWaypoint("berlin");
		m_route.addPoi("Hochschule Parking", "berlin");

		// Verification
//		CPPUNIT_ASSERT_MESSAGE("Error in addPoi with both database connected",1==(int )m_route.getRoute().size());
		CPPUNIT_ASSERT_EQUAL(2,(int )m_route.getRoute().size());
	}

	void testAddPoiForDataValidation()
		{
			// Precondition
			m_route.connectToWpDatabase(&m_WpDB);
			m_route.connectToPoiDatabase(&m_PoiDB);

			// Action
			m_route.addWaypoint("berlin");
			m_route.addPoi("Hochschule Parking", "berlin");

			// Verification
			CPPUNIT_ASSERT(m_PoiDB.getPointerToPoi("Hochschule Parking")==m_route.getRoute()[1]);
		}

	void testAddPoiwithoutPoiDB()
	{
		// Precondition - do not connect POI DB
		m_route.connectToWpDatabase(&m_WpDB);

		// Action
		m_route.addWaypoint("berlin");
		m_route.addPoi("Hochschule Parking", "berlin");

		// Verification
		CPPUNIT_ASSERT_MESSAGE("Error in addPoi with Poi DB not connected",1==(int )m_route.getRoute().size());

	}

	void testAddPoiwithoutWpDB()
	{
		// Precondition - do not connect Waypoint DB
		m_route.connectToPoiDatabase(&m_PoiDB);

		// Action
		m_route.addWaypoint("berlin");
		m_route.addPoi("Hochschule Parking", "berlin");

		// Verification
		CPPUNIT_ASSERT_MESSAGE("Error in addPoi with Waypoint DB not connected",0==(int )m_route.getRoute().size());

	}

	void testAddPoiwithinvalidWaypoint()
	{
		// Precondition
		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		// Action
		m_route.addWaypoint("berlin");
		m_route.addPoi("Hochschule Parking", "bern");

		// Verification
		CPPUNIT_ASSERT_MESSAGE("Error in addPoi with invalid waypoint",1==(int )m_route.getRoute().size());
	}

	void testAddPoiwithinvalidPoi()
	{
		// Precondition
		m_route.connectToWpDatabase(&m_WpDB);
		m_route.connectToPoiDatabase(&m_PoiDB);

		// Action
		m_route.addWaypoint("berlin");
		m_route.addPoi("Hochschule Darmstadt", "berlin");

		// Verification
		CPPUNIT_ASSERT_MESSAGE("Error in addPoi with invalid POI",1==(int )m_route.getRoute().size());
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add Poi tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Adding Poi with databases connected",
						&CTestAddPoi::testAddPoiwithDbsConnected));
		suite->addTest(
						new CppUnit::TestCaller<CTestAddPoi>(
								"Adding Poi with databases connected - check for data validation",
								&CTestAddPoi::testAddPoiForDataValidation));

		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Adding Poi without Poi Database connected",
						&CTestAddPoi::testAddPoiwithoutPoiDB));
		suite->addTest(
						new CppUnit::TestCaller<CTestAddPoi>(
								"Adding Poi without Waypoint database connected",
								&CTestAddPoi::testAddPoiwithoutWpDB));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Adding Poi with invalid waypoint",
						&CTestAddPoi::testAddPoiwithinvalidWaypoint));

		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Adding invalid Poi with valid waypoint",
						&CTestAddPoi::testAddPoiwithinvalidPoi));
		return suite;
	}

};



#endif /* CTESTADDPOI_H_ */
