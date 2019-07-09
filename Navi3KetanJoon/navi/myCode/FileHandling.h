/*
 * FileHandling.h
 *
 *  Created on: 08-Dec-2016
 *      Author: Ketan Joon
 */

#ifndef FILEHANDLING_H_
#define FILEHANDLING_H_

#include<string.h>
#include<stdlib.h>
#include"CPersistentStorage.h"

class FileHandling: public CPersistentStorage
{
private:
	string m_Poiname;
	string m_Waypointname;
	fstream m_WaypointFile;
	fstream m_PoiFile;

public:
	FileHandling();
	void setMediaName(std::string name);			// used to append the file names
	bool writeData(const CWpDatabase& waypointDb,const CPoiDatabase& poiDB);
	bool readData(CWpDatabase& waypointDb,CPoiDatabase& poiDB, MergeMode mode);
	bool processLatLong(string Value) const;		// check for correctness of LatLong values

};

#endif /* FILEHANDLING_H_ */
