#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100    // upper limit on how many contacts the array can hold

// One contact's data
typedef struct {
    char name[50];       // contact's full name
    char phone[20];      // contact's phone number
    char email[50];      // contact's email address
} Contact;

// The whole address book: a fixed array of contacts + how many are actually used
typedef struct {
    Contact contacts[MAX_CONTACTS];    // storage for all contacts
    int contactCount;                 // how many slots are currently in use
} AddressBook;

void createContact(AddressBook *addressBook);  // add a new contact
void searchContact(AddressBook *addressBook);  // find contacts by name/phone/email
void editContact(AddressBook *addressBook);    // modify an existing contact
void deleteContact(AddressBook *addressBook);  // remove a contact
void listContacts(AddressBook *addressBook, int sortCriteria);  // print all contacts, sorted
void initialize(AddressBook *addressBook);     // set up the address book at startup

int validateName(char *name);        // 0 = valid, 1 = invalid
int validatePhone(char *phone);      // 0 = valid, 1 = invalid
int validateEmail(char *email);      // 0 = valid, 1 = invalid

#endif