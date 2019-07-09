
#ifndef CTESTADDWAYPOINT_H_
#define CTESTADDWAYPOINT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
using namespace std;

class CTestAddWaypoint: public CppUnit::TestFixture
{
private:
	CRoute m_route;
	CWpDatabase m_WpDB;

public:

	void setUp()
	{
		CWaypoint berlin("berlin", 52.5167, 13.3833);
		m_WpDB.addWaypoint(berlin);
	}

	/* Test addWaypoint function with database connected
	 * precondition - Database connected
	 * Action - Try adding a valid waypoint
	 * Result - waypoint added to route
	 */
	void testAddWaypointWithDbConnected()
	{
		m_route.connectToWpDatabase(&m_WpDB);  // Precondition
		m_route.addWaypoint("berlin");          // Action

		CPPUNIT_ASSERT_MESSAGE("Error in addWaypoiint with both DB connetced",1==(int )m_route.getRoute().size()); // Verification
	}

	void testAddWaypointForDataValidation()
		{
			m_route.connectToWpDatabase(&m_WpDB);  // Precondition
			m_route.addWaypoint("berlin");          // Action

			// Verification
			CPPUNIT_ASSERT(m_WpDB.getPointerToDB("berlin")==m_route.getRoute()[0]);
		}

	/* Test addWaypoint function with database not connected
	 * precondition - Database not connected
	 * Action - Try adding a valid waypoint
	 * Result - waypoint should not be added to route
	 */
	void testAddWaypointWithoutDbConnected()
	{
		m_route.addWaypoint("berlin");          // Action

		CPPUNIT_ASSERT_MESSAGE("Error in addWaypoiint without Waypoint DB connetced",0==(int )m_route.getRoute().size()); // Verification
	}

	/* Test addWaypoint function with invalid Waypoint add
	 * precondition - Database connected
	 * Action - Try adding a invalid waypoint
	 * Result - waypoint should not be added to route
	 */
	void testAddWaypointWithInvalidWaypoint()
	{
		m_route.connectToWpDatabase(&m_WpDB);  // Precondition

		m_route.addWaypoint("ayroor");         // Action

		CPPUNIT_ASSERT_MESSAGE("Error in addWaypoiint with Invalid waypoint",0==(int )m_route.getRoute().size()); // Verification
	}


	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite(
				"addWaypoint function tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestAddWaypoint>(
						"Adding Waypoint with database Connected",
						&CTestAddWaypoint::testAddWaypointWithDbConnected));
		suite->addTest(
						new CppUnit::TestCaller<CTestAddWaypoint>(
								"Adding Waypoint with database Connected",
								&CTestAddWaypoint::testAddWaypointForDataValidation));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddWaypoint>(
						"Adding Waypoint with database not connected",
						&CTestAddWaypoint::testAddWaypointWithoutDbConnected));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddWaypoint>(
						"Adding invalid waypoint with database connected",
						&CTestAddWaypoint::testAddWaypointWithInvalidWaypoint));
		return suite;
	}
};

#endif /* CTESTADDWAYPOINT_H_ */
