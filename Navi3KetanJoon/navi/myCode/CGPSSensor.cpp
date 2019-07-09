/*
 * CGPSensor.cpp
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#include "CGPSSensor.h"

CGPSSensor::CGPSSensor()
{
	// No data attributes declared in class
}

CWaypoint CGPSSensor::getCurrentPosition()
{
	double latitude, longitude;
	cout<< "\nGPS Sensor \n\tEnter Latitude: ";
	cin>> latitude;
	cout<< "\tEnter Longitude: ";
	cin>> longitude;
	return CWaypoint("Current Position", latitude, longitude);
}
