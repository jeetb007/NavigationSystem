/*
 * CTemplate.h
 *
 *  Created on: 14-Jan-2017
 *      Author: Ketan Joon
 */

#ifndef CTEMPLATE_H_
#define CTEMPLATE_H_

#include <iostream>
using namespace std;

template <class I, class E>
class CTemplate
{
private:
	std::map<I,E> m_db;			// store elements as map objects

public:
	void addElement (E const& element);
	E* getPointerToElement(I identifier);
	map<I, E> getMap() const;					// return Element where needed (as map)
};

template<class I, class E>
inline void CTemplate<I, E>::addElement(const E& element)
{
		typename map<I,E>::iterator it = m_db.begin();

		if( !m_db.insert( pair<I,E>(element.getName(),element) ).second )
		{
			// Check if same Element already exists or not in DB
			cout<<"Sorry! The Element '" << element.getName() << "' already exists!!\n";
		}
		else
		{
			// add Element to DB
			m_db.insert( pair<I,E> (element.getName(), element) );
		}
	}

template<class I, class E>
inline E* CTemplate<I, E>::getPointerToElement(I identifier)
{
		// Return address of POI requested by user. If not found, return NULL

		if(m_db.find(identifier) == m_db.end())
			return 0;

		else
		{
			typename map<I,E>::iterator it = m_db.find(identifier);
			return &it->second;
		}
	}

template<class I, class E>
inline map<I, E> CTemplate<I, E>::getMap() const
{
		return m_db;
}

#endif /* CTEMPLATE_H_ */
