/**
 * @file name : CPoiDatabase.h *
 */

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H

#include <map>
#include "CPOI.h"
#include "CDatabaseTemplate.h"

//using std::map;
//using std::pair;

#include <fstream>
namespace std {
class CPoiDatabase: public CDatabaseTemplate<string,CPOI> {

public:

	/**
	 * CPoiDatabase constructor
	 */
	CPoiDatabase();

	/**
	 * addPoi - add POi to POI database
	 * @param poi - POI that is to be added to database
	 */
	void addPoi(CPOI const & poi);

	/**
	 * getPointerToPoi - checks for POI name in POI database and returns pointer to matching POI
	 * @param name - POI name which is to be checked in POI database
	 * @return CPOI - Pointer to matching POI in Database
	 */
	CPOI* getPointerToPoi(string name);

// for testing CPoiDatabase
	void print();

	/**
	 * sharePoiDBmembers - Sharing POI database for persistent class use
	 * @param sharetPoiMap - POI database
	 * @param ShareIt- POi map container iterator
	 */
	void sharePoiDBmembers(map<string, CPOI> & sharetPoiMap,
			map<string, CPOI>::iterator & ShareIt) const;

	/**
	 * clearPoiMap - Clear database contents
	 */
	void clearPoiMap();
	map<std::string, CPOI>* getMapPOI();

private:
	map<string, CPOI> m_PoiMap;  // Creating map object
	map<string, CPOI>::iterator m_it; // Creating an iterator
};
}
#endif //CPOIDATABASE_H
