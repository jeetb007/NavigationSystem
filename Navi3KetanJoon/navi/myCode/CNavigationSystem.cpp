/*
 * CNavigationSystem.cpp
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */


#include "CNavigationSystem.h"

CNavigationSystem::CNavigationSystem()
{ }

void CNavigationSystem::run()
{
	enterRoute();
	printRoute();

}

void CNavigationSystem::enterRoute()
{


	//Initialize some Waypoints
	CWaypoint Delhi("Neu Delhi", 28.6432, 77.1157);
	CWaypoint Agra("Agra", 27.1777, 78.0093);
	CWaypoint Mumbai("Mumbai", 18.9488, 72.8305);
	CWaypoint Goa("Goa", 14.8789, 74.4400);

	//Initialize some POIs
	CPOI LalQuila(FORT, "Lal Quila", "Oldest fort in Delhi", 28.6561, 77.2408);
	CPOI QutubMinar(MONUMENT, "Qutub Minar", "World's tallest sandstone tower", 28.5243, 77.1852);
	CPOI TajMahal(MONUMENT, "Taj Mahal", "Most beautiful monument", 27.1748, 78.0417);
	CPOI RadissonBlu(RESTAURANT, "Radisson Blu", "Best hotel in Agra", 28.6561, 77.2408);
	CPOI MarineDrive(SIGHTSEEING, "Marine Drive", "Seaside road with great view", 18.9282, 72.8207);
	CPOI LeopoldCafe(RESTAURANT, "Leopold Cafe", "Best bar and cafe in Mumbai", 18.9228, 72.8318);

	//add Waypoints to their DB
	m_WpDatabase.addWaypoint(Delhi);
	m_WpDatabase.addWaypoint(Agra);
	m_WpDatabase.addWaypoint(Mumbai);
	m_WpDatabase.addWaypoint(Agra);
	m_WpDatabase.addWaypoint(Goa);

	//add POIs to their DB
	m_PoiDatabase.addPoi(LalQuila);
	m_PoiDatabase.addPoi(QutubMinar);
	m_PoiDatabase.addPoi(TajMahal);
	m_PoiDatabase.addPoi(TajMahal);
	m_PoiDatabase.addPoi(RadissonBlu);
	m_PoiDatabase.addPoi(MarineDrive);
	m_PoiDatabase.addPoi(LeopoldCafe);

	//connect the POIDatabase to the Route
	m_route.connectToPoIDatabase(&m_PoiDatabase);

	//connect the WpDatabase to the Route
	m_route.connectToWpDatabase(&m_WpDatabase);



	//Add WayPoints to the Route
	m_route.addWaypoint("Neu Delhi");
	m_route.addWaypoint("Agra");
	m_route.addWaypoint("Mumbai");
	m_route.addWaypoint("Pune");

	//Add POIs to the Route
	m_route.addPoi("Taj Mahal", "Agra");
	m_route.addPoi("Radisson Blu", "Agra");
	m_route.addPoi("Marine Drive", "Mumbai");

	//testcase for operator +=
	m_route+="Goa";
	m_route+="Lal Quila";

/*
	//check copy constructor of poi
	CRoute new_route(m_route);
	new_route.print();


	//create a new route with the addition of two different routes
	CRoute common_route;
		//trying to add two routes with same and different database
		common_route.connectToWpDatabase(&m_WpDatabase);
		common_route.connectToPoIDatabase(&m_PoiDatabase);
		//trying to add waypoint to the new route
		common_route += "Mumbai";
		common_route += "2Leopold Cafe";
		//calling the overloaded + and = operator
		common_route = common_route + m_route;
		common_route.print();
*/

/*	//create the waypoint and poi files
	FileHandling filetestwp;
	FileHandling filetestpoi;

	// name the files accordingly
	filetestwp.setMediaName("Urlaub");

	//passing the data from  the existing database for the file storage
	//passing both database to the file so that data is written in one method
	filetestwp.writeData(m_WpDatabase,m_PoiDatabase);

*/
/*
	// Reading from the files
	FileHandling read;

	// replace existing database
	//read.readData(m_WpDatabase, m_PoiDatabase, REPLACE);


	// merge with existing database
	read.readData(m_WpDatabase, m_PoiDatabase, MERGE);

	cout<< "Database learned from the file:\n";
	m_WpDatabase.print();
	m_route.addWaypoint("Mumbai");
*/

}

void CNavigationSystem::printRoute()
{
	m_route.print();
}
