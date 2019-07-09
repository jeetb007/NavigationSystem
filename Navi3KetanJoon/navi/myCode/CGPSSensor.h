/*
 * CGPSensor.h
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#ifndef CGPSSENSOR_H_
#define CGPSSENSOR_H_

#include "CWaypoint.h"

class CGPSSensor
{
public:
	CGPSSensor();
	CWaypoint getCurrentPosition();		// Get current Lat Long in run time
};

#endif /* CGPSSENSOR_H_ */
