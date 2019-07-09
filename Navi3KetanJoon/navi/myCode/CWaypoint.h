
#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_
#include <iostream>
#include <math.h>
using namespace std;
//#define SHOWADRESS				// used as toggle for constructor detail print
#define DEGREE 1					// print coordinate in decimal format
#define MMSS 2						// print coordinate in °'" format
#define D2R (double) (22/7)/180		// To convert degrees to radians

class CWaypoint						// Defines a city and its location
{
private:
	string m_name;					// Name of city or location
	double m_latitude;
	double m_longitude;

public:
	CWaypoint(string name = "NoName", double latitude = 0, double longitude = 0);		// Constructor
	virtual ~CWaypoint(){}
	void set(string name, double latitude, double longitude);							// Check and initialize attributes
	virtual void print(int format);														// Print attributes as per required format
	string getName() const;																// return city name where needed
	double getLatitude() const;															// return latitude where needed
	double getLongitude() const;														// return longitude where needed
	void getAllDataByReference(string& name, double& latitude, double& longitutde);		// return attribute values by reference where needed
	//double calculateDistance(const CWaypoint& wp);										// calculate distance from city whose object is passed
	friend ostream& operator<<(ostream& out, CWaypoint& Wpobj);							// operator overloading for <<

private:

	void transformLongitude2degmmss(int& deg, int& mm, double& ss);						// convert longitude from decimal to °'"
	void transformLatitude2degmmss(int& deg, int& mm, double& ss);						// convert latitude from decimal to °'"

};

#endif /* CWAYPOINT_H_ */
