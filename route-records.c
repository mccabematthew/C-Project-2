#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "route-records.h"

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
    
    fgets( buffer, sizeof( buffer ), fileIn ); // unrecorded first record (header)
    
    while ( fgets( buffer, sizeof( buffer ), fileIn ) != NULL ) // remaining line count
    {
        count++;
    }

    rewind( fileIn );

    RouteRecord* records = ( RouteRecord* )malloc( count * sizeof( RouteRecord ) ); // dynamic mem allocation for array after count
    
    if ( records == NULL ) // error handling
    {
        printf( "Memory allocation failed\n" );
        return NULL;
    }

    for ( int i = 0; i < count; i++ ) 
    {
        for ( int j = 0; j < 6; j++ ) 
        {
            records[ i ].passengerCount[ j ] = 0;
        }
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
int fillRecords(RouteRecord* r, FILE* fileIn) {
    char origin[MAX_SIZE];
    char destination[MAX_SIZE];
    char airlineCode[MAX_SIZE];
    int month, passengers;
    int routeCount = 0;

    char line[100];
    fgets(line, sizeof(line), fileIn);

    while (fscanf(fileIn, "%d,%[^,],%[^,],%[^,],%d\n",
                  &month, origin, destination, airlineCode, &passengers) == 5) {

        if (strlen(airlineCode) == 3)
            continue;

        int monthIndex = month - 1;

        if (monthIndex < 0 || monthIndex >= 6)
            continue;

        int index = findAirlineRoute(r, routeCount, origin, destination, airlineCode, 0);

        if (index != -1) {
            r[index].passengerCount[monthIndex] += passengers;
        } else {
            strcpy(r[routeCount].origin, origin);
            strcpy(r[routeCount].destination, destination);
            strcpy(r[routeCount].airline, airlineCode);

            for (int i = 0; i < 6; i++) {
                r[routeCount].passengerCount[i] = 0;
            }

            r[routeCount].passengerCount[monthIndex] = passengers;

            routeCount++;
        }
    }

    return routeCount;
}

int findAirlineRoute( RouteRecord* r, int length, const char* origin,
    const char* destination, const char* airline, int curIdx ) 
    {
    if ( curIdx >= length ) 
    {
        return -1;
    }

    if ( strcmp( r[ curIdx ].origin, origin ) == 0 &&
    strcmp( r[ curIdx ].destination, destination ) == 0 &&
    strcmp( r[ curIdx ].airline, airline ) == 0 ) 
    {
        return curIdx;
    }

    else 
    {
        return findAirlineRoute( r, length, origin, destination, airline, curIdx + 1 );
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
    int matches = 0;
    int totalPassengers = 0;
    int passengersByMonth[ 6 ] = { 0 };
    
    // Print search type
    switch(st) 
    {
        case ROUTE:
            printf( "Searching by route...\n" );
            break;
        case ORIGIN:
            printf( "Search by origin...\n" );
            break;
        case DESTINATION:
            printf( "Searching by destination...\n" );
            break;
        case AIRLINE:
            printf( "Search by airline...\n" );
            break;
    }
    
    // Search through records
    for ( int i = 0; i < length; i++ ) 
    {
        int matchFound = 0;
        
        // Check if current record matches search criteria
        switch( st ) 
        {
            case ROUTE:
                if ( strcmp(r[ i ].origin, key1 ) == 0 && strcmp( r[ i ].destination, key2 ) == 0 ) 
                {
                    matchFound = 1;
                }
                break;
            case ORIGIN:
                if ( strcmp( r[ i ].origin, key1 ) == 0 ) 
                {
                    matchFound = 1;
                }
                break;
            case DESTINATION:
                if ( strcmp( r[ i ].destination, key1 ) == 0 ) 
                {
                    matchFound = 1;
                }
                break;
            case AIRLINE:
                if ( strcmp(r[ i ].airline, key1 ) == 0 ) 
                {
                    matchFound = 1;
                }
                break;
        }
        
        if (matchFound) {
            // Print airline and route
            printf( "%s ( %s-%s ) ", r[i].airline, r[i].origin, r[i].destination );
            matches++;
            
            // Add passenger counts
            for ( int j = 0; j < 6; j++ ) 
            {
                passengersByMonth[ j ] += r[ i ].passengerCount[ j ];
                totalPassengers += r[ i ].passengerCount[ j ];
            }
        }
    }
    
    // Print statistics
    printf( "\n%d matches were found.\n", matches );
    printf( "Statistics\n" );
    printf( "Total Passengers: %d\n", totalPassengers );
    
    for ( int i = 0; i < 6; i++ ) 
    {
        printf( "Total Passengers in Month %d: %d\n", i + 1, passengersByMonth[ i ] );
    }
    
    // Calculate average passengers per month
    if ( matches > 0 ) 
    {
        int averagePerMonth = totalPassengers / 6;
        printf( "Average Passengers per Month: %d\n", averagePerMonth );
    } else 
    {
        printf( "Average Passengers per Month: 0\n" );
    }
}

/*
    Function: printMenu
    -------------------
    Description: Prints the menu

    Returns: Nothing
*/
void printMenu ( )
{
    printf( "\n\n######### Airline Route Records Database MENU #########\n" );
    printf( "1. Search by Route\n" );
    printf( "2. Search by Origin Airport\n" );
    printf( "3. Search by Desination Airport\n" );
    printf( "4. Search by Airline\n" );
    printf( "5. Quit\n" );
    printf( "Enter your selection: " );
}
