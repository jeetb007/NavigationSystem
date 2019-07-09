

#ifndef MYCODE_CJSONPERSISTENCE_H_
#define MYCODE_CJSONPERSISTENCE_H_

#include "CJsonPersistence.h"
#include "CPersistentStorage.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CJsonToken.h"

namespace std {
class CJsonPersistence : public CPersistentStorage {
	string fileName;
public:
	CJsonPersistence();
	~CJsonPersistence();
	void setMediaName(string name);
	bool writeData(CWpDatabase& waypointDb,CPoiDatabase& poiDb);
	bool readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,MergeMode mode);
	template<typename T> void writeToFile(map <string,T> &mapT,fstream &File);
	t_poi getPoiType(string tagValue);
};

} /* namespace std */

#endif /* MYCODE_CJSONPERSISTENCE_H_ */
