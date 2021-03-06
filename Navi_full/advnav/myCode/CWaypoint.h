/* Generated by Together */

/**
 * @file name: CWaypoint.h *
 * Degree, DMS for selecting POI/ waypoint print format
 * R radius of earth
 * RadDeg for radian - degree convertion *
 */

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

//#define SHOWADRESS

#define Degree 1    //best place to define, as CWaypoint is the very base building block of this navigation program
#define DMS 2       //best place to define, as CWaypoint is the very base building block of this navigation program
#define R 6378
#define RadDeg 57.2958

#include <string>
using std::string;

#include<ostream>
using std::ostream;

class CWaypoint {
public:
	/**
	 * CWaypoint Constructor
	 * @param name - Waypoint name
	 * @param latitude - Waypoint latitude
	 * @param longitude - Waypoint longitude
	 */
    CWaypoint(string name="None", double latitude=0, double longitude=0);

    /**
     * CWaypoint virtual destructor
     */
    virtual ~CWaypoint();

    /**
     * set - assigning value to class attribute
     * @param name - Waypoint name
     * @param latitude - Waypoint latitude
	 * @param longitude - Waypoint longitude
     */
    void set(string name, double latitude, double longitude);

    /**
     * getName - returns m_name attribute
     * @return m_name
     */
    string getName() const;

    /**
     * getLatitude - returns m_latititude attribute
     * @return m_latititude
     */
    double getLatitude() const;

    /**
     * getLongitude - returns m_longitude attribute
     * @return - m_longitude
     */
    double getLongitude() const;

    /**
     * getAllDataByReference - return all details related to a Waypoint - name, latitude, longitude
     * @param name - Waypoint name
     * @param latitude - Waypoint latitude
     * @param longitude - Waypoint longitude
     */
    void getAllDataByReference(string& name, double & latitude, double & longitude) const;

    /**
     * calculateDistance - calculating distance between two points
     * @param wp - distance to wp is calculated
     * @return distance between two points
     */
    double calculateDistance(const CWaypoint& wp);

    /**
     * print - Print Waypoint or POI in either Decimal or Degree-Minute-Second format
     * @param format - to decide between DMS and Degree format print
     */
    virtual void print(int format);

    /**
     * operator<< - overloaded << operator to output data directly with objects
     * @param os - cout in this program
     * @param obj - CWaypoint object
     * @return - cout in this program
     */
    friend ostream& operator<<(ostream& os, CWaypoint & obj);

protected:
    string m_name;       // Waypoint name
    double m_latitude;   // Waypoint latitude
    double m_longitude;  // Waypoint longitude

private:
    /**
     * transformLongitude2degmmss - Convert longitude to Degree-Minute-Second format
     */
    void transformLongitude2degmmss(int & deg, int & mm, double & ss);

    /**
     * transformLatiude2degmmss - Convert latitude to Degree-Minute-Second format
     */
    void transformLatiude2degmmss(int & deg, int & mm, double & ss);

};
#endif //CWAYPOINT_H
