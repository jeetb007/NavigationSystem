/*
 * CRoute.cpp
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#include "CRoute.h"

CRoute::CRoute()
{
	m_nextWp = 0;
	m_nextPoi = 0;

	//allocate new memory for the pointers
	m_pWpDatabase = new CWpDatabase;
	m_pWpDatabase = NULL;

	m_pPoiDatabase = new CPoiDatabase;
	m_pPoiDatabase = NULL;
}

CRoute::CRoute(const CRoute& origin)
{
	m_nextWp = origin.m_nextWp;
	m_nextPoi = origin.m_nextPoi;

	m_pPoiDatabase = origin.m_pPoiDatabase;
	m_pWpDatabase = origin.m_pWpDatabase;

	for(list<CWaypoint*>::const_iterator it = origin.my_Route.begin(); it!=origin.my_Route.end(); it++)
	{
		my_Route.push_back(*it);
	}
}

void CRoute::connectToPoIDatabase(CPoiDatabase* pPoiDB)
{
	if (pPoiDB == NULL)
	{
		m_pPoiDatabase = NULL;
		cout<< "ERROR: The POI Database is empty!!\n";
	}
	else
		m_pPoiDatabase = pPoiDB;
}

void CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{
	if (pWpDB == NULL)
	{
		m_pWpDatabase = NULL;
		cout<< "ERROR: The Waypoint Database is empty!!\n";
	}
	else
		m_pWpDatabase = pWpDB;
}

void CRoute::addWaypoint(string name)
{
	//check for conditions and append the Waypoint
	if(m_pWpDatabase == NULL)
		cout<< "No database connected!!" << endl;
	else
	{
		if(m_pWpDatabase -> getPointerToWaypoint(name))
		{
			my_Route.push_back(m_pWpDatabase -> getPointerToWaypoint(name));
			m_nextWp++;
			cout<< "The Waypoint '" << name << "' added successfully." << endl;
		}
		else
		{
			//Error handling in case the specified POI is not found
			cout<<"ERROR: Could not find Waypoint '" << name << "' in Database." << endl;
		}
	}
}


void CRoute::addPoi(string namePoi, string afterWp)
{
	//check for conditions and append or insert the POI
	if(m_pPoiDatabase == NULL)
	{
		cout<< "No database connected!!" << endl;
	}

	else if(m_nextWp == 0)
	{
		cout<< "Cannot add POI! No Waypoints defined in the route." << endl;
	}
	else if(m_pPoiDatabase -> getPointerToPoi(namePoi))
	{
		list<CWaypoint*>::iterator it = my_Route.end();

		while(it != my_Route.begin())
		{
			it--;

			if( ((*it)->getName() == afterWp) && (dynamic_cast<CPOI*>(*it) == NULL) )
			{
				if((++it) != my_Route.end())
				{
					my_Route.insert(it,m_pPoiDatabase -> getPointerToPoi(namePoi));
				}
				else
				{
					my_Route.push_back(m_pPoiDatabase -> getPointerToPoi(namePoi));
				}

				--it;
				m_nextPoi++;
				cout<< "The POI '" << namePoi << "' added successfully." << endl;
				break;
			}
			else if(it == my_Route.begin())
			{
				//Error handling when the specified afterWp is not found
				cout<<"ERROR: Could not find related Waypoint '" << afterWp << "' in Database." << endl;
				break;
			}
		}
	}

	else
	{
		//Error handling when the specified POI is not found
		cout<<"ERROR: Could not find POI '" << namePoi << "' in Database." << endl;
	}
}

void CRoute::print()
{
	//Check for availability and call respective print() functions to print Waypoints or POIs
	cout<< "\n\nOur route has " << m_nextWp << " Waypoints and " << m_nextPoi << " Points of Interest\n";

	for(list<CWaypoint*>::iterator it = my_Route.begin(); it!=my_Route.end(); it++)
	{
		if ( dynamic_cast<CPOI*>(*it) != NULL)
		{
			cout<< *(dynamic_cast<CPOI*>(*it));
		}
		else
		{
			cout<< "\nWaypoint \n==================\n";
			cout<< **it;
		}
	}
}

void CRoute::operator +=(string name)
{
	//add waypoint
	addWaypoint(name);

	//add poi
	if(m_pPoiDatabase==NULL)
	{
		cout<< "No database connected" << endl;
	}
	else
	{
		if(m_pPoiDatabase -> getPointerToPoi(name))
		{
			my_Route.push_back(m_pPoiDatabase -> getPointerToPoi(name));
			m_nextPoi++;
			cout<<"The POI '" << name << "' added successfully."<<endl;
		}
		else
		{
			//Error handling when the specified POI is not found
			cout<<"ERROR: Could not find POI '" << name << "' in Database." << endl;
		}
	}
}


CRoute operator+(const CRoute& route1, const CRoute& route2)
{
	CRoute routeAdd;
	// check if both using same DB
	if( (route1.m_pPoiDatabase == route2.m_pPoiDatabase) && (route1.m_pWpDatabase == route2.m_pWpDatabase) )
	{
		routeAdd.m_nextPoi = route1.m_nextPoi + route2.m_nextPoi;
		routeAdd.m_nextWp = route1.m_nextWp + route2.m_nextWp;

		for(list<CWaypoint*>::const_iterator it = route1.my_Route.begin(); it!=route1.my_Route.end(); it++)
		{
			(routeAdd.my_Route).push_back(*it);
		}

		for(list<CWaypoint*>::const_iterator it = route2.my_Route.begin(); it!=route2.my_Route.end(); it++)
		{
			(routeAdd.my_Route).push_back(*it);
		}

	}
	// else put all values as NULL
	else
	{
		routeAdd.m_nextPoi = 0;
		routeAdd.m_nextWp = 0;
		cout<< "Database mismatch" << endl;
	}
	return routeAdd;
}


CRoute CRoute::operator=(const CRoute& origin)
{
	// similar to a copy constructor
	m_nextWp = origin.m_nextWp;
	m_nextPoi = origin.m_nextPoi;

	m_pPoiDatabase = origin.m_pPoiDatabase;

	m_pWpDatabase = origin.m_pWpDatabase;

	for(list<CWaypoint*>::const_iterator it = origin.my_Route.begin(); it!=origin.my_Route.end(); it++)
	{
		my_Route.push_back(*it);
	}

	return *this;
}

const vector<const CWaypoint*> CRoute::getRoute()
{
	vector<const CWaypoint*> rvec;
	for(list<CWaypoint*>::iterator it = my_Route.begin(); it!=my_Route.end(); it++)
		{
			rvec.push_back( *it);
		}
	return rvec;
}
