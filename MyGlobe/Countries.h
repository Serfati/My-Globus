#ifndef COUNTRIES_H_
#define COUNTRIES_H_

#include "HashTable.h"
/////////////////////
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/////////////////////////
#include "KeyValuePair.h"

#define MAX_LINE_LENGTH 300
#define MAX_WORD_LENGTH 30


/* definition of a data type Country for holding Country information */
typedef struct Country_t {
	char name[MAX_WORD_LENGTH];
	struct City_t *head; // cities' list
	int  numCities;
	struct Area_t *area;
	struct Country_t *next;
}Country;

/* definition of a data type City for holding city information */
typedef struct City_t City;

typedef struct Point_t{
	int x;
	int y;
} Point;

typedef struct Area_t Area;

// Required functions signatures:
void addCountry(Country **head, Country *cot, Country *end);
// Initialize a country struct
Country* createCountry(char*, Point*, Point*);
// add new city to country's cities' list
void addCityToCountry( Country*, City*, City* );
// remove city from country's cities' list
void removeCityFromCountry(Country*, char *);
bool isPointInCountry (Point*, Country*);
void freeCountry(Country*);
Country* copyCountry(Country*);
/* this prints the details of a Country, eg, the name, area, population
must pass it the address of the Country you want to print out*/
void printCountry( Country* ); //1, 5
bool doesCityExistInCountry(Country*, char*);
// Menu:
/* this prints all Countries from the Atlas address (head) passed to it. */
void printAtlas( Country* ); //1
/* find countries that locate around a given point*/
void listPointInCountry (Point*, Country*); //4
// Clean Atlas (First, we clean every city in every country, and then - clean every country
void deleteAtlas( Country* ); //6

// Reference functions signatures:
/* this prints the details of a city, eg, the name, population, food
 must pass it the address of the city you want to print out             */
void printCity( City* ); //1
City* createCity(char*, char*, int); //2
City* searchCityByName(Country*, char *); // 2,3
/* search the list for a name, and return a pointer to the found country     */
/* accepts a name to search for, and a pointer from which to start. If    */
/* you pass the pointer as 'head', it searches from the start of the Atlas */
Country* searchCountryByName(Country*, char *); //2, 3, 5

// reader to create the globe into hashtable
hashTable ReadFile( int , int  , char[]  );

#endif
