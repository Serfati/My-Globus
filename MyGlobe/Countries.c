#include "Countries.h"


struct City_t
{
	char name[MAX_WORD_LENGTH];
	char food[MAX_WORD_LENGTH];
	int  numResidents;
	struct City_t *next;
};

struct Area_t
{
	struct Point_t *topLeft;
	struct Point_t *bottomRight;
};



Country* createCountry( char *countryName, Point *pl, Point *pr){
	if(countryName == NULL) return NULL;

	Country *cot = (Country*) malloc(sizeof (struct Country_t) );
	if (cot == NULL)
		free(cot);
	Area *ar = (Area*) malloc(sizeof (struct Area_t) );
	if (ar == NULL)
		free(ar);
	strcpy(cot->name, countryName);
	ar->topLeft=pl;
	ar->bottomRight=pr;
	cot->area=ar;
	cot->head=NULL;
	cot->next = NULL;
	return cot;
}

City* createCity(char *cityName, char *food, int res){
	City *cit = (City*) malloc( sizeof (struct City_t));
	if (cit == NULL)
		free(cit);
	strcpy(cit->name, cityName);
	strcpy(cit->food, food);
	cit->numResidents=res;
	cit->next = NULL;
	return cit;
}

void printCountry( Country* cot ){
	if(cot != NULL){
		City* cit = cot->head;
		printf("Country %s coordinates: <%d,%d> , <%d,%d>\n", cot->name,
				cot->area->topLeft->x, cot->area->topLeft->y,
				cot->area->bottomRight->x,cot->area->bottomRight->y);
		while(cit!=NULL){
			printCity(cit);
			cit=cit->next;
		}
	}
}

void printCity( City *cit ){
	if(cit != NULL)
		printf("\t%s includes %d residents and their favorite food is %s\n", cit->name, cit->numResidents, cit->food);
}

void printAtlas( Country *head ){
	Country *cot = head ;
	while (cot != NULL){
		printCountry(cot);
		cot=cot->next;
	}
}

void addCountry( Country **head, Country *cot, Country *end){
	Country* cott = *head;
	if (*head == NULL) { // if Atlas/countries' list is empty
		*head = cot;
		end = *head;
	} else {
		while (cott != NULL){
			end = cott;
			cott = cott->next;
		}
		end->next = cot;
	}
}

void addCityToCountry( Country* cot, City* cit, City* endCit){

	if (doesCityExistInCountry( cot, cit->name)) return;
	City* citt = cot->head;
	if (cot->head == NULL) { // if cities' list is empty
		cot->head = cit;
		endCit = cot->head;
	} else {
		while (citt != NULL){
			endCit = citt;
			citt = citt->next;
		}
		endCit->next = cit;
	}
}

Country* searchCountryByName( Country *head, char *name ){
	Country *cot = head;
	while (cot != NULL){
		if(strcmp(cot->name, name)==0)
			break;
		cot=cot->next;
	}
	return cot;
}

City* searchCityByName( Country *cot, char *name ){
	City *cit = cot->head;
	while (cit != NULL){
		if(strcmp(cit->name, name)==0)
			break;
		cit=cit->next;
	}
	return cit;
}

void deleteAtlas( Country* head){
	Country *cot = head;
	while (cot != NULL){
		Country *cott = cot;
		cot = cott->next;
		freeCountry(cott);
	}
}

void freeCountry(Country* cot){
	City *cit = cot->head;
	while(cit != NULL){
		removeCityFromCountry(cot, cit->name);
		cit = cit->next;
	}
	free(cot->area->topLeft);
	free(cot->area->bottomRight);
	free(cot->area);
	free(cot);
}

void removeCityFromCountry(Country* cot, char * cityName){
	City* cit = cot->head;
	City *citt = searchCityByName( cot, cityName );
	if(citt==cit){ // if citt is the "head" of cities
		cot->head = cot->head->next;
		free(citt);
	}
	if(citt != cit) { // if citt is NOT the "head"
		while(cit->next != citt){
			cit = cit->next;
		}
		cit->next = citt->next;
		free(citt);
	}
}

bool isPointInCountry (Point* po, Country* cot){
	if((po->x>=cot->area->topLeft->x)&&
			(po->x<=cot->area->bottomRight->x)&&
			(po->y<=cot->area->topLeft->y)&&
			(po->y>=cot->area->bottomRight->y)){
		return true;
	}else
		return false;
}

void listPointInCountry (Point* po, Country* head){
	Country* cot = head;
	int degel = 0; // initialize flag to "not found"
	while (cot != NULL){
		if (isPointInCountry(po, cot)){
			printf("found in: %s\n",cot->name);
			degel = 1;
		}
		cot = cot->next;
	}
	if ((cot == NULL)&&(degel==0))
		printf("there is no country in the area\n");
}

bool doesCityExistInCountry(Country* searchedCountry, char* cityName)
{
	City* curr = NULL;
	curr = searchedCountry->head;
	while(curr != NULL){
		if(strcmp(curr->name, cityName) == 0)
			return true;
		curr = curr->next;
	}
	return false;

}

Country* copyCountry(Country* cot){
	Country *cott = NULL;
	cott = createCountry(cot->name, cot->area->topLeft, cot->area->bottomRight);
	if(cott == NULL)
		return NULL;
	cott->numCities = cot->numCities;
	cott->head = NULL;
	City *cit = cot->head;
	City *citt;
	while(cit != NULL){
		citt = createCity(cit->name, cit->food, cit->numResidents);
		addCityToCountry(cott, citt, cott->head);
		cit=cit->next;
	}
	return cott;
}


int transformKeyIntoNumberKey (Element key){
	char* hash = (char*) key;
	int sum = 0, i, len;
	len = strlen(hash);
	for (i = 0; i < len; i++)
		sum = sum + hash[i];
	return sum;
}

bool equalKey(Element elem1, Element elem2){
	char* key1 = (char*)elem1;
	char* key2 = (char*)elem2;

	char* res1 = (char*)malloc(sizeof(char)*strlen(key1)+1);
	char* res2 = (char*)malloc(sizeof(char)*strlen(key2)+1);
	strcpy(res1,key1);
	strcpy(res2,key2);
	if(strcmp(key1,key2)==0)
		return true;
	return false;
}

status printValueCountry(Element elem){

	Country* country = (Country*)elem;
	if(country ==NULL )
		return failure;
	printCountry(country);
	return success;
}

Element copyValueCountry(Element elem)
{
	Country* country = (Country*)elem;
	Country* res = NULL;
	res = copyCountry(country);
	if(res == NULL)
		return NULL;
	return (Element)res;
}

Element copyKeyString(Element elem)
{
	char* country_name = (char*)elem;
	char* res = (char*)malloc(sizeof(char)*strlen(country_name)+1);
	if(res == NULL)
		return NULL;
	strcpy(res,country_name);
	return (Element)res;
}

status freeKeyString(Element elem){

	char* country = (char*)elem;
	char* res = (char*)malloc(sizeof(char)*strlen(country)+1);
	if(res == NULL)
		return failure;
	strcpy(res,country);
	free(res);
	return success;
}

status freeValueCountry(Element elem){
	Country* cot = (Country*)elem;
	if(cot ==NULL )
		return failure;
	free(cot);
	return success;
}

status printKeyString(Element elem){
	char* country_name = (char*)elem;
	char* res = (char*)malloc(sizeof(char)*strlen(country_name)+1);
	if(res == NULL)
		return failure;
	strcpy(res,country_name);
	printf("%s",res);
	return success;
}


//   ***********************
//   **** FILE HANDLING ****
//   ***********************
hashTable ReadFile( int HashNumber, int numberOfCountries , char configuration[] ) {

	if(numberOfCountries < 0 || HashNumber < 0 )
		return NULL ;



	FILE* fp = fopen ( configuration , "r") ; // argv[2] = path
	int i, kelet, lx, ly, rx, ry, res;
	char *str, line[MAX_LINE_LENGTH], countryName[MAX_WORD_LENGTH], cityName[MAX_WORD_LENGTH], food[MAX_WORD_LENGTH];
	Country *end = (Country*) NULL; //end = "end" of the Atlas/countries
	City *endCit = (City*) NULL;
	hashTable ht =  createHashTable(copyKeyString,freeKeyString,printKeyString,copyValueCountry,freeValueCountry,
			printValueCountry,equalKey,transformKeyIntoNumberKey,HashNumber);

	if(ht == NULL)
		exit(1);

	if (fp == NULL){
		printf("Error! opening file");
		exit(1);
	}

	i=1;
	kelet = numberOfCountries;
	while( i <= kelet ){
		str = fgets(line, MAX_LINE_LENGTH, fp); // str = one line from the file
		if (str == NULL){
			break;
		}
		if ((str[0]!='\t')){ // New country
			addToHashTable(ht,end->name,end );
			Point *pl = (Point*)malloc( sizeof( Point ) );
			Point *pr = (Point*)malloc( sizeof( Point ) );
			str=strtok(line, ",");
			strcpy(countryName, str);
			str=strtok(NULL, ",");
			lx=atoi(str);
			str=strtok(NULL, ",");
			ly=atoi(str);
			str=strtok(NULL, ",");
			rx=atoi(str);
			str=strtok(NULL, "\n");
			ry=atoi(str);
			pl->x=lx;
			pl->y=ly;
			pr->x=rx;
			pr->y=ry;
			Country* cot = createCountry(countryName, pl, pr);
			//addCountry(&head, cot, end);
			end = cot;
			i++;
		}
		if ((str[0]=='\t')){
			str=strtok(line, ",");
			str++; // ignore the str[0]='\t' so now str will not include it
			strcpy(cityName, str);
			str=strtok(NULL, ",");
			strcpy(food, str);
			str=strtok(NULL, "\n");
			res=atoi(str);
			City *cit=createCity(cityName, food, res);
			addCityToCountry(end, cit, endCit);
			endCit = cit;
		}
	}
	str = fgets(line, MAX_LINE_LENGTH, fp); // str = one line from the file
	while(str[0]=='\t'){
		str=strtok(line, ",");
		str++; // ignore the str[0]='\t' so now str will not include it
		strcpy(cityName, str);
		str=strtok(NULL, ",");
		strcpy(food, str);
		str=strtok(NULL, "\n");
		res=atoi(str);
		City *cit=createCity(cityName, food, res);
		addCityToCountry(end, cit, endCit);
		endCit = cit;
		str = fgets(line, MAX_LINE_LENGTH, fp); // str = one line from the file
	}
	addToHashTable(ht,end->name,end );
	fclose(fp);
	return ht;
}
