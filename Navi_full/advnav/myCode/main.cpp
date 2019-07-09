

#include "CNavigationSystems.h"
#include <iostream>
using namespace std;

#include "CPoiDatabase.h"
#include "CWpDatabase.h"



int main()
{

//	//================= Testing CPOI Database - begin ========================
//	CPOI oDelhiAirport(Airport, "Delhi Airport", "International  Airport", 49.8,8.65325);
//	CPOI oHochschuleParking(Parking, "Hochschule Parking", "only for students",10, 20);
//	CPOI oGeorge(Church, "St. George", "Roman catholic church", 32.9021,40.7868);
//
//	CPoiDatabase tempObject1;
//	tempObject1.addPoi(oDelhiAirport);
//	tempObject1.addPoi(oHochschuleParking);
//	tempObject1.addPoi(oGeorge);
//
//	tempObject1.print();
//
//	CPOI* temp2;
//    temp2 = tempObject1.getPointerToPoi("Hochschule Parking");
//
//    if(temp2!=NULL)
//    {
//    	temp2->print();
//    }
//
//    //================= Testing CPOI Database - end ========================
//
//
//    //================= Testing CWaypoint Database - begin ========================
//	CWaypoint amsterdam("amsterdam", 52.3667, 4.9000);
//	CWaypoint darmstadt("darmstadt", 49.8667, 8.6500);
//	CWaypoint berlin("berlin", 52.5167, 13.3833);
//	CWaypoint tokio("tokio", 35.6833, 139.6833);
//
//	CWpDatabase tempObject2;
//	tempObject2.addWaypoint(berlin);
//	tempObject2.addWaypoint(darmstadt);
//
//	tempObject2.print();
//
//	CWaypoint* temp3;
//	temp3 = tempObject2.getPointerToWaypoint("darmstadt");
//
//	if (temp3 != NULL)
//	{
//		temp3->print(2);
//	}
//
//	//================= Testing CWaypoint Database - end ========================




//	===================== Testing Navigation System V2 - begin ===================
	cout<<"Navigation System"<<endl<<"-----------------"<<endl;

	//Creating a CNavigationSystems instance  -navSys- for accessing  CNavigationSystems operations
	CNavigationSystems navSys;

	//Calling CNavigationSystems operation - run()
	navSys.run();
//	===================== Testing Navigation System V2 - end =====================

	return(0);
}




