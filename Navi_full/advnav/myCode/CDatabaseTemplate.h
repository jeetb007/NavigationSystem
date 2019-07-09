/*
 * CDatabaseTemplate.h
 *
 *  Created on: Jan 9, 2016
 *      Author: maria
 */

#ifndef MYCODE_CDATABASETEMPLATE_H_
#define MYCODE_CDATABASETEMPLATE_H_

// Base class used as template for the POI and WP databases..

#include <map>
#include <string>
#include <iostream>
#include "CPOI.h"

namespace std {

template <class I, class T>
class CDatabaseTemplate {

 std::map <I,T> mapDB;

public:

	 CDatabaseTemplate();
	 virtual ~CDatabaseTemplate();
     void addToDB(const T &p);
	 T* getPointerToDB(I name);
	 void printDB();
	 map<I,T>* getMap();
};
	template <class I,class T>
	CDatabaseTemplate<I,T>::CDatabaseTemplate() {
		// TODO Auto-generated constructor stub
	}

	template <class I,class T>
	CDatabaseTemplate<I,T>::~CDatabaseTemplate() {
		// TODO Auto-generated destructor stub
	}

	template <class I,class T>
	void CDatabaseTemplate<I,T>::addToDB(const T &p){
		mapDB.insert(std::pair<const I,const T>(p.getName(),p));

		}

	template <class I,class T>
	T* CDatabaseTemplate<I,T>::getPointerToDB(I name){

		if (mapDB.find(name) == mapDB.end()) {
			cout << "ERROR.Could not find the POI " << name
					<< ".It is not in the Pool" << endl;
			return 0;
		} else {
			typename std::map<I,T>::iterator i;
			i = mapDB.find(name);
			return &(i->second);
		}
	}

	template <class I,class T>
	void CDatabaseTemplate<I,T>::printDB(){

		typename std::map <I,T>::iterator it;

		for(it = mapDB.begin(); it != mapDB.end(); it++) {
			cout << it->second.getName();
			cout << " ";
			cout << it->second.getLatitude();
			cout << " ";
			cout << it->second.getLongitude();
			cout << "\n";

		if( dynamic_cast<CPOI*>(&(it->second)) != NULL) {

				CPOI *temp = dynamic_cast<CPOI*>(&(it->second));

				cout << temp->getType();
				cout << " ";
				cout << temp->getDescription();
				cout << " ";

		      }
			cout << "\n";
	      }
	}

	template <class I,class T> map<I,T>* CDatabaseTemplate<I,T>::getMap(){
		return &mapDB;
		}

} /* namespace std */

#endif /* MYCODE_CDATABASETEMPLATE_H_ */
