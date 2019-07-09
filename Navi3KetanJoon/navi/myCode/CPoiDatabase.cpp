 /* CPoiDatabase.cpp
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#include "CPoiDatabase.h"

CPoiDatabase::CPoiDatabase()
{ }

void CPoiDatabase::addPoi(CPOI const& poi)
{
	addElement(poi);
}

CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	return getPointerToElement(name);
}
