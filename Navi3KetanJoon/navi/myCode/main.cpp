
//#include "CWaypoint.h"
//#include "CPOI.h"
//#include "CPoiDatabase.h"
//#include "CGPSSensor.h"
//#include "CRoute.h"
#include "CNavigationSystem.h"

int main (void)
{
	cout<< "<====== GPS ======>\n";

	CNavigationSystem navi;
	navi.run();

    return 0;
}
