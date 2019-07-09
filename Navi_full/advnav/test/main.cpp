
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>

#include "CTestAddWaypoint.h"
#include "CTestAddPoi.h"
#include "CTestClearRoute.h"
#include "CTestGetDistance.h"
#include "CTestOvEqual.h"
#include "CTestOvPlus.h"
#include "CTestOvPlusEqual.h"
#include  "CTestPrint.h"
#include "CTestCopyConstructor.h"

using namespace CppUnit;

int main(int argc, char* argv[])
{
	TextUi::TestRunner runner;
	runner.addTest(CTestGetDistance::suite());
	runner.addTest(CTestAddWaypoint::suite());
	runner.addTest(CTestAddPoi::suite());
	runner.addTest(CTestClearRoute::suite());
	runner.addTest(CTestOvEqual::suite());
	runner.addTest(CTestOvPlus::suite());
	runner.addTest(CTestOvPlusEqual::suite());
	runner.addTest(CTestCopyConstructor::suite());
	runner.addTest(CTestPrint::suite());

	runner.run();
	return 0;
}

