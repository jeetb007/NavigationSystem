/*
 * CPoiDatabase.h
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_

#include <map>
#include <string>

#include "CTemplate.h"
#include "CPOI.h"

class CPoiDatabase : public CTemplate <string, CPOI>
{
public:
	CPoiDatabase();
	void addPoi(CPOI const& poi);		// Add required POI in DB
	CPOI* getPointerToPoi(string name);	// To get address of specific POI
};

#endif /* CPOIDATABASE_H_ */
