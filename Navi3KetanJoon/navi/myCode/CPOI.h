/*
 * CPOI.h
 *
 *  Created on: 03.11.2016
 *      Author: stkejoon
 */

#ifndef CPOI_H_
#define CPOI_H_

#include "CWaypoint.h"

enum t_poi {RESTAURANT, SIGHTSEEING, MUSEUM, FORT, MONUMENT};

class CPOI : public CWaypoint		// Inheritance for accessing members of CWaypoint
{
private:
	t_poi m_type;
	string m_description;

public:
	CPOI(t_poi type = RESTAURANT, string name = "NoName", string description = "BLANK", double latitude = 0, double longitude = 0);
	virtual ~CPOI() {}
	virtual void print(int format);
	// Print function modified to include POI type and description
	void getAllDataByReference(string& name, double& latitude, double& longitutde, t_poi& type, string& description);
	friend ostream& operator<<(ostream& out, CPOI& CPOIobj);
	// operator overloading for <<
};

#endif /* CPOI_H_ */
