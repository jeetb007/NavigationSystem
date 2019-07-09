

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "CJsonPersistence.h"
#include "CJsonToken.h"
#include "CJsonScanner.h"

using namespace APT;

CJsonPersistence::CJsonPersistence() {
	// TODO Auto-generated constructor stub

}

CJsonPersistence::~CJsonPersistence() {
	// TODO Auto-generated destructor stub
}

void CJsonPersistence::setMediaName(string mediaName) {

	fileName = mediaName;

	fstream File;
	File.open(fileName.c_str(), fstream::app);
	File.close();

	cout << "********************************************" << endl;
	cout << "***** Created " << fileName << " *****" << endl;
	cout << "********************************************" << endl;
}

bool CJsonPersistence::writeData(CWpDatabase& waypointDb, CPoiDatabase& poiDb) {

	cout << "call template function 2 times... for poi and wp.. " << endl;

	fstream File;
	//File.open("CNavigation-wp-poi.json", fstream::app);
	File.open(fileName.c_str());

	File << "{";
	File << "\n";
	File << "  \"Waypoints\" : [\n";
	cout << "write data"; waypointDb.print();
	writeToFile(*(waypointDb.getMap()), File);

	File << "  ], \n";
	File << "  \"pois\" : [\n";
	cout << "write data: " ; poiDb.print();
	writeToFile(*(poiDb.getMapPOI()), File);

	File << "  ] \n }";

	File.close();

	cout << "********************************************" << endl;
	cout << "********** Written data to file ************" << endl;
	cout << "********************************************" << endl;

	return true;
}

template<typename DB>
void CJsonPersistence::writeToFile(map<string, DB> &mapT, fstream &File) {

	int sizeOfMap = mapT.size();

	typename std::map<string, DB>::iterator it;

	cout << "Size of list " << mapT.size();

	for (it = mapT.begin(); it != mapT.end(); it++) {

		File << "   {\n";
		File << "     \"name\" :" << "\"" << it->second.getName() << "\""
				<< ", \n";
		File << "     \"latitude\" :" << it->second.getLatitude() << ", \n";
		File << "     \"longitude\" :" << it->second.getLongitude();

		if (dynamic_cast<CPOI*>(&(it->second)) != NULL) {
			CPOI *temp = dynamic_cast<CPOI*>(&(it->second));
			File << ", \n";
			File << "     \"type\" :" << "\"" << temp->getType() << "\""
					<< ", \n";
			File << "     \"description\" :" << "\"" << temp->getDescription()
					<< "\"";
		}

		sizeOfMap--;

		if (sizeOfMap >= 1)
			File << "\n   },\n";
		else
			File << "\n   }\n";
	}
}

void printErrorMessage(int lineNo, string errorType){
	cout << "\n Error Reading from file : line No. " << lineNo << " - Expecting "<< errorType <<". Trying again ";
}

bool CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode) {

	unsigned int success = 1, objtCounter = 0;               // monitor read process
	bool status;					 				   // to check for read status

	// Clear databases if mode = REPLACE. Do nothing for MERGE mode
	if (mode == REPLACE) {
		waypointDb.clearWaypointMap();
		poiDb.clearPoiMap();
	}

	ifstream File; // Creating file object
	File.open(fileName.c_str());    					// associating file object with text file

	enum state {
		FIRST_TOKEN,
		WAITING_FOR_DB_NAME,
		WAITING_FOR_NAME_SEPARATOR,
		WAITING_FOR_BEGIN_DB,
		WAITING_FOR_BEGIN_OBJECT,
		WAITING_FOR_ATTRIBUTE_NAME,
		WAITING_FOR_SEPARATOR,
		WAITING_FOR_ATTRIBUTE_VALUE,
		WAITING_FOR_VALUE_SEPARATOR,
		WAITING_FOR_SEPARATOR_OBJECT,
		WAITING_FOR_END_DB,
		WAITING_FOR_END_FILE
	};

	state readState = FIRST_TOKEN;

	string DbName, attrName, attrValue, name, description, tpoiType;
	double value, latitude, longitude;
	t_poi type;

	//checking if stream is currently associated with file
	if (File.is_open()) {
		CJsonScanner scannner(File);
		CJsonToken* token;

		try {
			token = scannner.nextToken();      // to get next token from file
		}
		catch (string & illegalChar) {
			cout << "\n" << "Illegal character - " << illegalChar << " - found in Database file : line No. "
					<< scannner.scannedLine() << endl;
		}

		while (token != NULL) {
			switch (readState) {
			case FIRST_TOKEN:
				if (token->getType() == CJsonToken::BEGIN_OBJECT) {
					readState = WAITING_FOR_DB_NAME;
				} else {
					printErrorMessage(scannner.scannedLine(),"begin object");
		    		success++;
				}
				break;

			case WAITING_FOR_DB_NAME:
				if (token->getType() == CJsonToken::STRING) {
					readState = WAITING_FOR_NAME_SEPARATOR;  // assigning new state
					CJsonStringToken* temp = (CJsonStringToken*) token; // casting token to CJsonStringToken* type to get string value
					DbName = temp->getValue();
				} else {
					printErrorMessage(scannner.scannedLine(),"Database name");
					success++;
				}
				break;

			case WAITING_FOR_NAME_SEPARATOR:
				if (token->getType() == CJsonToken::NAME_SEPARATOR) {
					readState = WAITING_FOR_BEGIN_DB;
				} else {
					printErrorMessage(scannner.scannedLine(),"Name Separator");
					success++;
				}
				break;

			case WAITING_FOR_BEGIN_DB:
				if (token->getType() == CJsonToken::BEGIN_ARRAY) {
					readState = WAITING_FOR_BEGIN_OBJECT;
				} else {
					printErrorMessage(scannner.scannedLine(),"Begin array");
					success++;
				}
				break;

			case WAITING_FOR_BEGIN_OBJECT:
				if (token->getType() == CJsonToken::BEGIN_OBJECT) {
					readState = WAITING_FOR_ATTRIBUTE_NAME;
				} else {
					printErrorMessage(scannner.scannedLine(),"Begin object");
					success++;
				}
				break;

			case WAITING_FOR_ATTRIBUTE_NAME:
				if (token->getType() == CJsonToken::STRING) {

					readState = WAITING_FOR_SEPARATOR;
					CJsonStringToken* temp = (CJsonStringToken*) token;
					attrName = temp->getValue(); // tag holds name/ latitude/ longitude/ type/ description
				} else {
					printErrorMessage(scannner.scannedLine(),"Attribute Name");
					success++;
				}
				break;

			case WAITING_FOR_SEPARATOR:
				if (token->getType() == CJsonToken::NAME_SEPARATOR) {
					readState = WAITING_FOR_ATTRIBUTE_VALUE;
				} else {
					printErrorMessage(scannner.scannedLine(),"Separator");
					success++;
				}
				break;

			case WAITING_FOR_ATTRIBUTE_VALUE:
				if ((token->getType() == CJsonToken::NUMBER)
						|| (token->getType() == CJsonToken::STRING)) {

					readState = WAITING_FOR_VALUE_SEPARATOR;
					if (attrName == "name" || attrName == "description"
							|| attrName == "type") {

						CJsonStringToken* temp = (CJsonStringToken*) token;
						attrValue = temp->getValue();
					}
					if (attrName == "latitude" || attrName == "longitude") {
						CJsonNumberToken* temp1 = (CJsonNumberToken*) token; // casting token to CJsonNumberToken* type to get double value
						value = temp1->getValue();
					}

					if (attrName == "name") {
						name = attrValue;
					} else if (attrName == "latitude") {
						latitude = value;
					} else if (attrName == "longitude") {
						longitude = value;
					} else if (attrName == "description") {
						description = attrValue;
					} else if (attrName == "type") {
						type = CJsonPersistence::getPoiType(attrValue);
					}
				} else {
					printErrorMessage(scannner.scannedLine(),"Attribute Value");
					success++;
					readState = WAITING_FOR_VALUE_SEPARATOR;
				}
				break;

			case WAITING_FOR_VALUE_SEPARATOR:
				if (token->getType() == CJsonToken::VALUE_SEPARATOR) {
					readState = WAITING_FOR_ATTRIBUTE_NAME;
				} else if (token->getType() == CJsonToken::END_OBJECT) {
					readState = WAITING_FOR_SEPARATOR_OBJECT;
				} else {
					printErrorMessage(scannner.scannedLine(),"Separator or End object");
					success++;
				}
				break;

			case WAITING_FOR_SEPARATOR_OBJECT:
				if (objtCounter == 0) {
					if (DbName == "waypoints") {
						CWaypoint wpToAdd(name, latitude, longitude);
						waypointDb.addWaypoint(wpToAdd);
					}
					if (DbName == "pois") {
						CPOI poiToAdd(type, name, description, latitude,longitude);
						poiDb.addPoi(poiToAdd);
					}
				}
				objtCounter = 0;
				if (token->getType() == CJsonToken::VALUE_SEPARATOR) {
					readState = WAITING_FOR_BEGIN_OBJECT;
				} else if (token->getType() == CJsonToken::END_ARRAY) {
					readState = WAITING_FOR_END_DB;
				} else {
					printErrorMessage(scannner.scannedLine(),"Separator or Array End");
					success++;
				}
				break;

			case WAITING_FOR_END_DB:
				if (token->getType() == CJsonToken::VALUE_SEPARATOR) {
					readState = WAITING_FOR_DB_NAME;
				} else if (token->getType() == CJsonToken::END_OBJECT) {
					readState = WAITING_FOR_END_FILE;
				} else {
					printErrorMessage(scannner.scannedLine(),"Separator or Object End");
					success++;
				}
				break;

			case WAITING_FOR_END_FILE:
				cout << "\n" << "Read cycle completed." << "\n";
				break;

			default:
				cout << "\n" << "Error : Wrong state !!!" << "\n";
				break;
			}
			try {
				token = scannner.nextToken();      // to get next token from file
			} catch (string & illegalChar) {
				cout << "\n" << "Illegal character - " << illegalChar
						<< " - found in Database file : line No. "
						<< scannner.scannedLine() << "\n";
				if (readState == WAITING_FOR_ATTRIBUTE_NAME) {
					objtCounter = 1;
				}
			}
		}
	}

	else {
		// Error reading into file
		cout << "\n" << "Error!!! Failed to read to persistent storage " << "\n";
	}

	File.close();

	// Database write status return
	return (status = success != 1 ? false : true);
}

t_poi CJsonPersistence::getPoiType(string tagValue){
	if(tagValue == "Restaurant")
		return Restaurant;
	else if(tagValue == "Railway Station")
		return RailwayStation;
	else if(tagValue == "Airport")
		return Airport;
	else if(tagValue == "ATM")
		return ATM;
	else if(tagValue == "GasStation")
			return GasStation;
	else if(tagValue == "Parking")
			return Parking;
	else if(tagValue == "Hotel")
			return Hotel;
	else if(tagValue == "GasStation")
			return GasStation;

	return unDefined;

}


/* namespace apt */
