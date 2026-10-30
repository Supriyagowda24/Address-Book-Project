/*
Project     : Addressbook
Name        : Supriya J
Date        : 28/07/2026
Description : Addressbook contains all the contact details like Name Phone Email
Sample i/p  : Address Book Menu:
              Address Book Menu:
              1. Create contact
              2. Search contact
              3. Edit contact
              4. Delete contact
              5. List all contacts
              6. Exit
              Enter your choice: 1
              Enter the Details:
              Enter the Name: Supriya
              Enter the Phone Number: 8906534284
              Enter the Email: supriya10@gmail.com
              --------------------------------------
              Do you want to save [Yes] or [No]: 1
              --------------------------------------
              Contact created successfully

Sample o/p  : Supriya,8906534284,supriya10@gmail.com
*/

#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;                // main menu selection
    AddressBook addressBook;   // holds all contacts + the count
    initialize(&addressBook);  // Initialize the address book (loads saved contacts from file)

    do {
        printf("\nAddress Book Menu:\n");     // show the main menu
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);              // read the menu choice
        
        switch (choice) {        // dispatch to the right function
            case 1:
                createContact(&addressBook);   // add a new contact
                break;
            case 2:
                searchContact(&addressBook);   // find a contact
                break;
            case 3:
                editContact(&addressBook);    // update an existing contact
                break;
            case 4:
                deleteContact(&addressBook);   // remove a contact
                break;
            case 5:
                printf("Select sort criteria:\n");   // sub-menu for listing
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;                 // which field to sort by
                scanf("%d", &sortChoice);        // read sort choice
                listContacts(&addressBook, sortChoice);  // print all contacts, sorted
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);  // persist contacts before quitting
                break;
            default:
                printf("Invalid choice. Please try again.\n");  // anything outside 1-6
        }
    } while (choice != 6);  // keep looping until user picks Exit
    
       return 0;
}