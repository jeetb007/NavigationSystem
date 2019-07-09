/*
 * CNavigationSystem.h
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_

#include "CGPSSensor.h"
#include "CRoute.h"
#include "FileHandling.h"


class CNavigationSystem
{
private:
	CGPSSensor m_GPSSensor;
	CRoute m_route;
	CPoiDatabase m_PoiDatabase;
	CWpDatabase m_WpDatabase;

public:
	CNavigationSystem();
	void run();

private:
	void enterRoute();
	void printRoute();

};

#endif /* CNAVIGATIONSYSTEM_H_ */
