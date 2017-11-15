
/*
	Student Record Manager
		Uses dynamic memory allocation
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMenu();
void printRecords(char** fn, char** ln, double* s);
void addRecord(char ***fn, char ***ln, double **s);
void addString(char ***strArray, char* str);
void addDouble(double** dubArray, double dub);
void deleteRecord(char*** fn, char*** ln, double** s);
void removeString(char ***strArray);
void removeDouble(double** dubArray);
int findName(char** ln,char* n);
void printName(char** fn, char **ln, double *s);
void sortScore(char*** fn, char*** ln, double** s, int n);
void sortlName(char*** fn, char*** ln, double** s, int n);
void medianRecord(char** fn, char**ln, double* s, int n);
void scoresAbove(char** fn, char** ln, double* s, int n,int threshold);


int records;
int counter;

int main(){
	records = 0;
	counter = 1;

	int initRecords = 0;
	int choice,i;
	char **fn; // first Names
	char **ln; // last Names
	double *s; // score

	printf("= Student Record Manager =\n"
		   "Please enter how many value"
		   "s you would like to initall"
		   "y enter [min 5, max 15]: ");
	scanf("%d", &initRecords);
	if(initRecords < 5 || initRecords > 15)
		return 0;

	// allocate memory
	fn = malloc(0); // will reallocate later
	ln = malloc(0);
	s =  malloc(0);

	printf("Please enter the value (firstName lastName score ENTER): \n");
	for(i = 0;i<(initRecords);i++){
		addRecord(&fn, &ln, &s);
		counter++;
	}

	printf("Records added... \n");
	do{
		printMenu();
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printRecords(fn, ln, s);
				break;
			case 2:
				addRecord(&fn,&ln,&s);
				printf("> Record added. \n");
				break;
			case 3:
				deleteRecord(&fn, &ln, &s);
				printf("> Record deleted. \n");
				break;
			case 4:
				printf("Please enter the last name you'd like to search for: ");
				printName(fn,ln,s);
				break;
			case 5:
				sortScore(&fn, &ln, &s, records);
				printRecords(fn, ln, s);
				break;
			case 6:
				sortlName(&fn, &ln, &s, records);
				printRecords(fn, ln, s);
				break;
			case 7:
				medianRecord(fn, ln, s, records);
				break;
			case 0:
				return 0;
			default:
				return 0;
		}
	}
	while(1);
}

// Print user menu
void printMenu(){
	printf("\tMain Menu\t\n"
		"============================\n"
		" > Print records (press 1) \n"
		" > Add a new record (press 2) \n"
		" > Delete a record (press 3) \n"
		" > Search by last name (press 4)\n"
		" > Sort by score (press 5) \n"
		" > Sort by last name (press 6) \n"
		" > Find median score (press 7) \n"
		" > Exit the program (press 0)\n"
		"============================\n"
		"Please select an option: ");
}

// Print all user records
void printRecords(char** fn, char** ln, double* s){
	int i;
	for(i=0;i<records;i++)
		printf("(%d) First name: %s | Last name: %s | Score: %0.2lf \n",i+1,fn[i],ln[i],s[i]); // will start at the first item and go i amount in the index
}


void addRecord(char*** fn, char*** ln, double** s){
	// gather value
	
	char* fname = malloc(64);
	char* lname = malloc(64);
	double score;
	records++;

	printf("%d) ", (counter));
	scanf("%s %s %lf",fname, lname, &score);

	addString(fn, fname);
	addString(ln, fname);
	addDouble(s, score);
}

void addString(char*** strArray, char* str){
	// realloc array one larger
	*strArray = realloc(*strArray, (records) * sizeof(char*));

	// set pointer equal
	(*strArray)[records-1] = str;

}

void addDouble(double** dubArray, double dub){
	// realloc array one larger
	*dubArray = realloc(*dubArray, (records) * sizeof(double));

	// set pointer equal
	(*dubArray)[records-1] = dub;
}

void deleteRecord(char*** fn, char*** ln, double** s){
	//This part gets the name
	int i, j;
	char *name = malloc(64);
	printf("Please enter the last name of the record(s) you'd like to delete: ");
	scanf("%s",name);

	while(findName(*ln, name) != 0){
		for(i = 0;i<records && strcmp(name,(*ln)[i]) != 0;i++);
		records--;
		//free((*ln)[i]);
		//free((*fn)[i]);
		for(i=i; i < records-1; i++){
			(*ln)[i] = (*ln)[i+1];
			(*fn)[i] = (*fn)[i+1];
			(*s)[i] = (*s)[i+1];
		}
		removeString(fn);
		removeString(ln);
		removeDouble(s);
	}

}
void removeString(char ***strArray){
	*strArray = realloc(*strArray, (records) * sizeof(char*));

}
void removeDouble(double** dubArray){
	*dubArray = realloc(*dubArray, (records) * sizeof(double));
}

// Finds how many instances of a last name are present
int findName(char** ln,char* n){
	int i, counter=0;

	for(i=0;i<records-1;i++){
		if(strcmp(n,*(ln+i)) == 0){
			counter++;
		}
	}
	return counter;
}

void printName(char** fn, char **ln, double *s){
	char *search = malloc(64);
	int i, count = 0;
	printf("Please enter the last name you'd like to search for: ");
	scanf("%s",search);

	// for loop to iterate through all values in last name
	for(i=0;i<records;i++){
		if(strcmp(search,ln[i]) == 0){
			count ++;
			printf(" > First name: %s | Last name: %s | Score: %0.2lf \n",fn[i],ln[i],s[i]);
		}
	}

	if(count == 0){
		printf("> No records found. \n");
	}
}

// Recursive bubble sort for score
void sortScore(char*** fn, char*** ln, double** s, int n){
	int i;
	float tempF = 0;
	char* tempC = malloc(64);
	if(n == 1)
		return;
	for(i=0;i<n-1;i++){
		if((*s)[i+1] > (*s)[i]){
			tempF = (*s)[i+1];
			(*s)[i+1] = (*s)[i];
			(*s)[i] = tempF;

			tempC = (*fn)[i+1];
			(*fn)[i+1] = (*fn)[i];
			(*fn)[i] = tempC;

			tempC = (*ln)[i+1];
			(*ln)[i+1] = (*ln)[i];
			(*ln)[i] = tempC;

		}
	}

	sortScore(fn,ln,s,n-1);
}

// Recursive bubble sort for score
void sortlName(char*** fn, char*** ln, double** s, int n){
	int i;
	float tempF = 0;
	char* tempC = malloc(64);
	if(n == 1)
		return;
	for(i=0;i<n-1;i++){
		if(strcmp((*ln)[i],(*ln)[i+1]) > 0){
			tempF = (*s)[i+1];
			(*s)[i+1] = (*s)[i];
			(*s)[i] = tempF;

			tempC = (*fn)[i+1];
			(*fn)[i+1] = (*fn)[i];
			(*fn)[i] = tempC;

			tempC = (*ln)[i+1];
			(*ln)[i+1] = (*ln)[i];
			(*ln)[i] = tempC;

		}
	}

	sortlName(fn,ln,s,n-1);
}

// Find median user record score
void medianRecord(char** fn, char**ln, double* s, int n){
	// sort scores by scores first
	sortScore(&fn, &ln, &s, n);

	// get half of array
	int half = records/2;
	float medianScore = s[half];
	printf("The median score is: %0.2f. \n  These students have a score above that: \n", medianScore);
	scoresAbove(fn,ln,s, n, medianScore);

}

void scoresAbove(char** fn, char** ln, double* s, int n,int threshold){
	int i;
	for(i=0;i<n;i++){
		if(*(s+i) > threshold)
			printf(" > First name: %s | Last name: %s | Score: %0.2f \n",*(fn+i),*(ln+i),*(s+i));
	}
}