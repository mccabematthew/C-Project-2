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

RouteRecord* createRecords(FILE* fileIn);

int fillRecords(RouteRecord* r, FILE* fileIn);

int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);

void printMenu();

#endif
