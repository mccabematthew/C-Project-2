#include <stdio.h>
#include <route-records.h>

/*
    Function: createRecords
    -------------------
    Description: Creates array of RouteRecords and initializes it

        fileIn: A file pointer to get data from csv

    Returns: The pointer to dynamically allocated array
*/
RouteRecord* createRecords ( FILE* fileIn ) // WIP: delete all inline comments when done
{
    int count = 0; // total record count
    char buffer[ 1024 ]; // Buffer to hold each line
    
    fgets(buffer, sizeof(buffer), fileIn); // unrecorded first record (header)
    
    while (fgets(buffer, sizeof(buffer), fileIn) != NULL) // remaining line count
    {
        count++;
    }

    RouteRecord* records = ( RouteRecord* )malloc( count * sizeof( RouteRecord ) ); // dynamic mem allocation for array after count
    
    if (records == NULL) // error handling
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    
    return records; // the required array ptr
}

/*
    Function: fillRecords
    -------------------
    Description: Processes data in csv and calls findAirlineRoute to prevent value redundancy

        r: Array pointer for the dynamically allocated array
        fileIn: A file pointer to get data from csv
        
    Returns: The amount of RouteRecords used in the array
*/
int fillRecords ( RouteRecord* r, FILE* filein )
{

}

int findAirlineRoute(RouteRecord* r, int length, const char* origin,
    const char* destination, const char* airline, int curIdx) {

if (curIdx >= length) {
    return -1;
}

if (strcmp(r[curIdx].origin, origin) == 0 &&
strcmp(r[curIdx].destination, destination) == 0 &&
strcmp(r[curIdx].airline, airline) == 0) {
    return curIdx;
}

else {
    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1);
}

}

/*
    Function: searchRecords
    -------------------
    Description: This function searches a RouteRecord array and prints out the results of the search.

        r: Array pointer for the dynamically allocated array
        length: Route record length
        key1: Search criterion that varies by search type 
            - contains origin airport code for ROUTE searches, or the target value for ORIGIN/DESTINATION/AIRLINE searches.
        key2: : Secondary search criterion used only with ROUTE search type 
            - contains the destination airport code when searching by complete route.
        st: Determines if the functions is searching by ROUTE, ORIGIN, DESTINATION, or AIRLINE
        
    Returns: Nothing
*/
void searchRecords ( RouteRecord* r, int length, const char* 
    key1, const char* key2, SearchType st )
{

}

/*
    Function: printMenu
    -------------------
    Description: Prints the menu

    Returns: Nothing
*/
void printMenu ( )
{
    printf("######### Airline Route Records Database MENU #########");
    printf("1. Search by Route");
    printf("2. Search by Origin Airport");
    printf("3. Search by Desination Airport");
    printf("4. Search by Airline");
    printf("5. Quit");
}
