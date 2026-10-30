#include <stdio.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *ptr;
    if ((ptr = fopen("contacts.txt", "w")) == NULL) {   // open file for writing, overwrites old contents
        printf("Error opening file\n");
        return;
    }

    fprintf(ptr, "%d\n", addressBook->contactCount);  // first line: how many contacts follow
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(ptr, "%s,%s,%s\n",       
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);  // one contact per line, comma-separated
    }

    fclose(ptr);  // always close what you open
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *ptr;
    if ((ptr = fopen("contacts.txt", "r")) == NULL) {
        return; // no saved file yet, keep whatever's already in addressBook
    }

    int count;
    if (fscanf(ptr, "%d\n", &count) != 1) {
        fclose(ptr); // read the contact count from line 1
        return;
    }

    for (int i = 0; i < count && addressBook->contactCount < MAX_CONTACTS; i++) {
        if (fscanf(ptr, "%[^,],%[^,],%[^\n]\n",    // read up to each comma, then to end of line
                   addressBook->contacts[addressBook->contactCount].name,
                   addressBook->contacts[addressBook->contactCount].phone,
                   addressBook->contacts[addressBook->contactCount].email) == 3) {
            addressBook->contactCount++;  // only count it if all 3 fields were read
        }
    }

    fclose(ptr);  // always close what you open
}