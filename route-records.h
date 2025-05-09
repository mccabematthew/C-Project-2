#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

#define MAX_SIZE 20
#include <stdio.h>

typedef struct ROUTERECORD {
    char origin[MAX_SIZE];
    char destination[MAX_SIZE];
    char airline[MAX_SIZE];
    int passengerCount[6];
} RouteRecord;

typedef enum SearchType {
    ROUTE,
    ORIGIN,
    DESTINATION,
    AIRLINE
} SearchType;

/*
    Function: createRecords
    -------------------
    Description: Creates array of RouteRecords and initializes it

        fileIn: A file pointer to get data from csv

    Returns: The pointer to dynamically allocated array
*/
RouteRecord* createRecords( FILE* fileIn );

/*
    Function: fillRecords
    -------------------
    Description: Processes data in csv and calls findAirlineRoute to prevent value redundancy

        r: Array pointer for the dynamically allocated array
        fileIn: A file pointer to get data from csv
        
    Returns: The amount of RouteRecords used in the array
*/
int fillRecords( RouteRecord* r, FILE* fileIn );

/*
    Function: findAirlineRoute
    -------------------
    Description: Recursive function that finds a record in RouteRecord array with same origin
                 and destination airport codes and airline.

        r: Array pointer for the dynamically allocated array
        length: Route record length
        origin: The airport code of origin
        destination: The airport destination code
        airline: The airline code
        curIdx: The current index within array
        
    Returns: Either index number in which three strings appear in the array or -1
             if it cannot find these three strings in the same struct object.
*/
int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx );

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
void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st );

/*
    Function: printMenu
    -------------------
    Description: Prints the menu

    Returns: Nothing
*/
void printMenu( );

#endif
