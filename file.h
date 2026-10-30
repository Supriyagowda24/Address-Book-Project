#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);     // write all contacts to contacts.txt
void loadContactsFromFile(AddressBook *addressBook);   // read contacts back from contacts.txt

#endif
