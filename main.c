#include <stdio.h>
#include <stdlib.h>


int main( int argc, char *argv[] )
{
    /* 1. Declare variables here */
    FILE *filePtr = fopen( "data-2024.csv", "r" );

    
    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program DONE*/
    if (argc < 2) {
        printf("ERROR: Missing file name\n");
        return 1;
    }
    
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). DONE*/
    printf("Opening %s...\n", argv[1]);
    filePtr = fopen(argv[1], "r");
    
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. DONE */
    if ( filePtr == NULL ) 
    {
        printf( "ERROR: Could not open file\n" );
        return 1;
    }
    
    
    /* 5. Do the following to load the records into an array of RouteRecords
    	
    		5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
            createRecords( filePtr ); WIP
    		
    		5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    		
    		5.3 Close the the file.
            
    */

    //5.1
    
    // 5.2

    fclose( filePtr ); //5.3 DONE
    
    /* 6. Create an infinite loop that will do the following:
    		6.1 Call printMenu()

    		6.2 Ask the user to input a value for the menu - WIP: figure out var for the switch statement (for below) val in scanf
    		//printf("Enter your selection: ");
            //scanf("%d", &someValueForMenuOptions);

    		6.3 Handle the case in which a non-integer value is entered
    		
    		6.4 Create a switch/case statement to handle all the menu options
    		
	    		6.4.1 Each option requires the user to enter a search key
	    		
	    		6.4.2 Quit needs to free the array
    
    */

    printMenu( ); // 6.1

    // 6.2

    // 6.3

    // 6.4 NOT DONE, We'll have to move this to ctrl+] this to the right because it will be in the while loop stated above
    switch (menuChoice) {
        case 1: // Search by Route
            printf("Enter origin: ");
            scanf("%s", key1);
            printf("Enter destination: ");
            scanf("%s", key2);
            searchRecords(records, numRecords, key1, key2, ROUTE);
            break;
            
        case 2: // Search by Origin
            printf("Enter origin: ");
            scanf("%s", key1);
            searchRecords(records, numRecords, key1, NULL, ORIGIN);
            break;
            
        case 3: // Search by Destination
            printf("Enter destination: ");
            scanf("%s", key1);
            searchRecords(records, numRecords, key1, NULL, DESTINATION);
            break;
            
        case 4: // Search by Airline
            printf("Enter airline: ");
            scanf("%s", key1);
            searchRecords(records, numRecords, key1, NULL, AIRLINE);
            break;
            
        case 5: // Quit
            printf("Good-bye\n");
            free(records); // Free memory!!! (can't wait until i don't have to do this teehee)
            return 0;
            
        default:
            printf("Invalid option. Please try again.\n");
    }

    // 6.4.1

    // 6.4.2
    
    return 0;
}
