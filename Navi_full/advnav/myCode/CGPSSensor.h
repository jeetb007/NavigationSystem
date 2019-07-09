/* Generated by Together */

/*
 * @file name: CGPSSensor.h
 *
 * CGPSSensor() -  CGPSSensor class constructor
 * CWaypoint getCurrentPosition(); - takes in current lat long values from user
 */

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

class CWaypoint;

class CGPSSensor {
public:

	/**
	 * CGPSSensor constructor
	 */
	CGPSSensor();

	/**
	 * getCurrentPosition - get current position latitude, longitude values from user
	 * @return - Current position as a waypoint object
	 */
	CWaypoint getCurrentPosition();
};
#endif //CGPSSENSOR_H
