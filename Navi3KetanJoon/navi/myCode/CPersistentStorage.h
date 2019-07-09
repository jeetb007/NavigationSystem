/*
 * CPersistentStorage.h
 *
 *  Created on: 08-Dec-2016
 *      Author: Ketan Joon
 */

#ifndef CPERSISTENTSTORAGE_H_
#define CPERSISTENTSTORAGE_H_

#include <fstream>

#include "CPoiDatabase.h"
#include "CWpDatabase.h"

enum MergeMode{MERGE,REPLACE};		// used for DB Merge

class CPersistentStorage
{
public:

virtual void setMediaName(std::string name)=0;		// used to append the file names
virtual bool writeData(const CWpDatabase& waypointDb,const CPoiDatabase& poiDB)=0;
virtual bool readData(CWpDatabase& waypointDb,CPoiDatabase& poiDB, MergeMode mode)=0;
virtual ~CPersistentStorage();
};


#endif /* CPERSISTENTSTORAGE_H_ */
