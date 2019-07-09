/*
 * FileHandling.cpp
 *
 *  Created on: 19-Jan-2016
 *      Author: Ketan Joon
 */

#include <iostream>
#include <string>

#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CAddWaypoint.h"
#include "CAddPoiTest.h"

#include "../myCode/CWaypoint.h"
#include "../mycode/CGPSSensor.h"
#include "../myCode/CNavigationSystem.h"
#include "../myCode/CPOI.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CRoute.h"
#include "../myCode/CPersistentStorage.h"


//Main Function of Navigation System
int main (void)
{
	CppUnit:: TextUi:: TestRunner runner;
	runner.addTest(CAddWaypoint::suite());
	runner.addTest(CAddPoiTest::suite());
	runner.run();
	return 0;
}
