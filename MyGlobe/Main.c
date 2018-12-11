/*
 ============================================================================
 Name        : My Globus Atlas
 Author      : Avihai Serfati and Ricky Shama {(204520803) , (032496994)}
 Version     : 3.0
 Copyright   : BGU ,Read Only
 Description : My Globe in C, implements countries Atlas with cities for each country
 ============================================================================
 */

#include "KeyValuePair.h"
#include "Countries.h"
#include "HashTable.h"
#include "Defs.h"

/* this is the main routine where all the glue logic fits     */

						/***********************/
					    /* 	  Globus Atlas	  */
					   /***********************/

int main(int argc , char* argv[]){
	int choice;
	char countryName[MAX_WORD_LENGTH], cityName[MAX_WORD_LENGTH], food[MAX_WORD_LENGTH];
	Country *country = NULL;
	City *city = NULL;

	//arguments
	int hashNumber = atoi(argv[1]);
	int numberOfCountries = atoi(argv[2]);
	char* configuration  = argv[3];


	//create My basic Globe into Globe HASHTABLE
	hashTable Globe = ReadFile ( hashNumber , numberOfCountries , configuration ) ;


	//   ******** MENU *********

	while ( 1 ) {
		printf("‫‪please‬‬ ‫‪choose‬‬ ‫‪one‬‬ ‫‪of‬‬ ‫‪the‬‬ ‫‪following‬‬ ‫‪numbers:‬‬\n");
		printf("‫‪1‬‬ ‫‪:‬‬ ‫‪print‬‬ ‫‪Countries\n‬‬");
		printf("2 : add country\n");
		printf("‫‪3‬‬ ‫‪:‬‬ ‫‪add‬‬ ‫‪city‬‬ ‫‪to‬‬ ‫‪country‬‬\n‬‬");
		printf("4 : delete city from country\n");
		printf("‫‪5‬‬ ‫‪:‬‬ ‫‪print‬‬ ‫‪country‬‬ ‫‪by‬‬ ‫‪name‬‬\n‬‬");
		printf("6 : delete country\n");
		printf("7 : is country in area\n");
		printf("8‬‬ ‫‪:‬‬ ‫‪exit\n‬‬‬‬");
		scanf("%d", &choice );
		switch( choice )
		{

		case 1:	/*	print GLOBE		*/
			displayHashElements(Globe);
			break;

		case 2:	/*	add country		*/
			printf( "please enter a new country name\n" );
			scanf("%s", countryName );

			country = lookupInHashTable( Globe , countryName);
			if( NULL != country ) {
				printf( "country with this name already exist\n" );
				break;
			}
			else{
				int  x1, y1, x2, y2;
				printf( "please enter two x and y coordinates :x1,y1,x2,y2\n" );
				scanf( "%d,%d,%d,%d",&x1,&y1,&x2,&y2 );
				Point* p1 = (Point*) malloc (sizeof (Point));
				Point* p2 = (Point*) malloc (sizeof (Point));

				p1->x=x1;
				p1->y=y1;
				p2->x=x2;
				p2->y=y2;

				Country* countryToadd = createCountry(countryName, p1, p2);

				addToHashTable(Globe, countryToadd->name , countryToadd);
			}
			break;

		case 3:   /*	add‬‬ ‫‪city‬‬ ‫‪to‬‬ ‫‪country‬‬	*/
			printf( "please enter a country name\n" );
			scanf("%s", countryName );
			country = lookupInHashTable( Globe , countryName);
			if( NULL == country ) {
				printf( "country not exist\n" );
				break;
			}
			else{
				printf( "please enter a city name\n" );
				scanf("%s", cityName);
				bool flag = doesCityExistInCountry(country, cityName);
				if( flag == true){
					printf("this city already exist in this country\n");
				}
				else{
					int  res;
					printf("‫‪please enter the city favorite food\n");
					scanf("%s", food );
					printf("‫‪please enter number of residents in city\n");
					scanf("%d", &res);
					while (res<=0){
						printf("please choose a valid number\n");
						scanf("%d", &res );
					}
					city = createCity(cityName, food, res);
					addCityToCountry(country, city , NULL); //TODO
				}
			}
			break;

		case 4:		/*	remove city from country	*/
			printf("please enter a country name\n");
			scanf("%s", countryName );
			country = lookupInHashTable( Globe , countryName );
			if( NULL == country ) {
				printf("country name not exist.\n" );
				break;
			}
			else{
				printf("please enter a city name\n");
				scanf("%s", cityName );
				if (searchCityByName(country, cityName) == NULL){
					printf("the city not exist in this country\n");
					break;
				} else {
					removeCityFromCountry(country, cityName);
					break;
				}
			}
			break;

		case 5:		 /*		print country by name	 */
			printf("please enter a country name\n");
			scanf("%s", countryName );
			country= lookupInHashTable( Globe , countryName);
			if( NULL == country ) {
				printf("country name not exist.\n" );
				break;
			}else
				printCountry(country);
			break;

		case 6:		/*	remove country from GLOBE	*/
			printf("please enter a country name\n");
			scanf("%s", countryName );
			country = lookupInHashTable( Globe , countryName);
			if( NULL == country ) {
				printf("can't delete the country\n" );
				break;
			}
			else{
				removeFromHashTable( Globe , countryName );
				printf("country deleted\n");
			}
			break;

		case 7: 	 /* 	find country in area	 */
			printf("please enter a country name\n");
			scanf("%s", countryName );
			country = lookupInHashTable( Globe , countryName);
			if( NULL == country ) {
				printf("country name not exist.\n" );
				break;
			}
			int  x1, y1;
			printf("please enter x and y coordinations:x,y\n");
			scanf("%d , %d",&x1,&y1);
			Point* p3 = (Point*) malloc (sizeof (Point));
			p3->x=x1;
			p3->y=y1;
			if (isPointInCountry(p3, country))
				printf("the coordinate in the country\n");
			else
				printf("the coordinate not in the country\n");
			free(p3);
			break;

		case 8:		/*		exit the app and delete all memory		*/
			destroyHashTable(Globe);
			printf("all the memory cleaned and the program is safely closed \n");

			return 0; //add // to check memory leak

		default:
			printf("please choose a valid number\n");
		}
	}
}
