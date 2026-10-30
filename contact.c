#include <stdio.h>      // Used for input and output functions
#include <stdlib.h>     // Used for standard library functions
#include <string.h>     // Used for string operations
#include <ctype.h>      // Used for character checking functions
#include "contact.h"    // Contains structure and function declarations
#include "file.h"       // Contains file handling functions

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Function is used to display all contacts by sorting based on selected option

    switch (sortCriteria)
    {
        case 1:
            printf("Sorting based on name : \n");             // Sorting contacts by name
            for (int i = 0; i < addressBook->contactCount - 1; i++)      // Bubble sort by name
            {
                for (int j = 0; j < addressBook->contactCount - i - 1; j++)   // compare adjacent contacts
                {
                    // If first name is greater than second name, swap them
                    if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
                    {
                        Contact temp = addressBook->contacts[j];              // Temporary variable used for swapping contacts
                        addressBook->contacts[j] = addressBook->contacts[j + 1];  // Move next contact to current position
                        addressBook->contacts[j + 1] = temp;                  // Store previous contact in next position
                    }
                }
            }
            printf(" %-6s%-20s%-16s%-30s\n", "Index", "Name", "Phone", "Email");   // Display contact table heading
            for (int i = 0; i < addressBook->contactCount; i++)                 // Display all contacts after sorting
            {
                printf(" %-6d%-20s%-16s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
            break;

        case 2:
            printf("Sorting based on phone : \n");             // Sorting contacts based on phone number
            for (int i = 0; i < addressBook->contactCount - 1; i++)      // Bubble sort based on phone number
            {
                for (int j = 0; j < addressBook->contactCount - i - 1; j++)   // compare adjacent contacts
                {
                    if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0)   // Compare two phone numbers
                    {
                        Contact temp = addressBook->contacts[j];              // Swap contacts
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1] = temp;
                    }
                }
            }
            printf(" %-6s%-20s%-16s%-30s\n", "Index", "Name", "Phone", "Email"); // Display heading
            for (int i = 0; i < addressBook->contactCount; i++)   // Display all sorted contacts
            {
                printf(" %-6d%-20s%-16s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); 
            }
            break;

        case 3:
            printf("Sorting based on email : \n");             // Sorting contacts based on email
            for (int i = 0; i < addressBook->contactCount - 1; i++)      // Bubble sort based on email
            {
                for (int j = 0; j < addressBook->contactCount - i - 1; j++)
                {
                    if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0)   // Compare email addresses
                    {
                        Contact temp = addressBook->contacts[j];              // Swap contacts
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1] = temp;
                    }
                }
            }
            printf(" %-6s%-20s%-16s%-30s\n", "Index", "Name", "Phone", "Email");  // Display heading
            for (int i = 0; i < addressBook->contactCount; i++)   // Display sorted contacts
            {
                printf(" %-6d%-20s%-16s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            }
            break;

        default:
            printf("Invalid entry,try again"); // If user enters invalid sorting option
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;       // Initialize contact count as zero when address book starts
    loadContactsFromFile(addressBook);   // Load previously saved contacts from file
}

/* --------------- Validation  --------------- */
// Each returns 0 if valid, 1 if invalid //

int validateName(char *name)
{
    if (strlen(name) < 3)                // Check minimum length of name
    {   
        printf("Error Message : Name must contain atleast 3 characters\n");   // tell the user why it failed
        return 1;   // invalid
    }
    for (int i = 0; name[i] != '\0'; i++)    // Check each character in the name
    {
        if (!(isalpha((unsigned char)name[i]) || name[i] == ' '))    // Name should contain only alphabets and spaces
        {
            printf("Error Message : Name should contain only alphabets\n");
            return 1;   // invalid
        }
    }
    return 0;   // satisfies all conditions
}

int validatePhone(char *phone)
{
    int len = strlen(phone);    // Find length of phone number

    if (len != 10)            // Phone number should contain exactly 10 digits
    {
        printf("Error Message : Phone number must contain exactly 10 digits\n");   // tell the user why it failed
        return 1;   // invalid
    }
    for (int i = 0; i < len; i++)   // Check whether all characters are digits
    {
        if (!isdigit((unsigned char)phone[i]))    // If character is not a digit
        {
            printf("Error Message : Other than Digits any other Character not allowed in phone number\n");
            return 1;   // invalid
        }
    }
    if (phone[0] < '6' || phone[0] > '9')     // First digit of number should be between 6 to 9
    {
        printf("Error Message : First digit must be between 6 and 9\n");
        return 1;   // invalid
    }
    return 0;   // valid
}

int validateEmail(char *email)
{
    int atCount = 0, dotCount = 0;   // Variables to count special characters
    int atPos = -1, dotPos = -1;     // Store positions of @ and .

    for (int i = 0; email[i] != '\0'; i++)    // Check every character of email
    {
        if (email[i] == '@') 
        {
            atCount++;
            atPos = i;
        }
        else if (email[i] == '.')       // Count dot symbol and store position
        {
            dotCount++;
            dotPos = i;
        }
    }
    if (atCount == 0)    // Email must contain @ symbol
    {
        printf("Error Message : Missing @\n");
        return 1;   // invalid
    }
    if (atCount > 1)    // Email should contain only one @
    {
        printf("Error Message : Multiple @ symbols are not allowed\n");
        return 1;   // invalid
    }
    if (dotCount == 0)    // Email must contain dot
    {
        printf("Error Message : Missing . (dot)\n");
        return 1;   // invalid
    }
    if (dotCount > 1)    // Email should contain only one dot
    {
        printf("Error Message : Only one . (dot) is allowed\n");
        return 1;   // invalid
    }
    if (dotPos < atPos)   // Dot should come after @ symbol
    {
        printf("Error Message : . (dot) must appear after @ symbol\n");
        return 1;   // invalid
    }
    if (dotPos - atPos < 2)   // There should be at least one character between @ and .
    {
        printf("Error Message : Atleast one character required between @ and .\n");
        return 1;   // invalid
    }
    if (strcmp(email + dotPos, ".com") != 0)   // Email should end with .com
    {
        printf("Error Message : Extra characters after the domain\n");
        return 1;   // invalid
    }
    for (int i = 0; email[i] != '\0'; i++)   // Check remaining characters of email
    {
        char c = email[i];
        if (c == '@' || c == '.')   // @ and . are allowed symbols
        {
            continue;
        }
        if (!(islower((unsigned char)c) || isdigit((unsigned char)c)))    // Allow only lowercase letters and numbers
        {
            printf("Error Message : Invalid symbol\n");
            return 1;   // invalid
        }
    }
    return 0;
}

/* ---------- Contact operations ---------- */

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)  // Check whether address book has reached maximum contact limit
    {
        printf("Address book is full, cannot add more contacts\n");
        return;                  // stop function if no space is available
    }
    
    // Variables to store contact details temporarily
    char name[50];
    char phone[20];
    char email[50];
    char choice[10];
    int valid;       // Variable used to check validation status

    printf("Enter the Details:\n");
    
    valid = 0;
    while (!valid)                      // keep asking until a unique, valid name is entered
    {
        printf("Enter the Name: ");
        getchar();                      // Remove previous newline character from input buffer
        scanf("%[^\n]", name);          // read the whole line, including spaces

        valid = 1;
        for (int i = 0; i < addressBook->contactCount; i++)     // Check whether name already exists
        {
            if (strcmp(addressBook->contacts[i].name, name) == 0) 
            {
                printf("--------------------------------------\n");
                printf("Name is already in existence\n");
                printf("--------------------------------------\n");
                valid = 0;
                break;
            }
        }
        if (valid && validateName(name))      // If name is unique, check name format
        {
            valid = 0;
        }
    }

    valid = 0;
    while (!valid)                      // keep asking until a unique, valid phone number is entered
    {
        printf("Enter the Phone Number: ");
        getchar();                     // Remove newline character
        scanf("%s", phone);            // Read the phone number

        valid = 1;
        for (int i = 0; i < addressBook->contactCount; i++)           // Check duplicate phone number
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0) 
            {
                printf("--------------------------------------\n");
                printf("Phone number is already in existence\n");
                printf("--------------------------------------\n");
                valid = 0;
                break;
            }
        }
        if (valid && validatePhone(phone))    // Validate phone number format
        {
            valid = 0;
        }
    }

    valid = 0;
    while (!valid)                      // keep asking until a unique, valid email is entered
    {
        printf("Enter the Email: ");
        getchar();
        scanf("%[^\n]", email);   // read the whole line

        valid = 1;
        for (int i = 0; i < addressBook->contactCount; i++)          // Check duplicate email
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0) 
            {
                printf("--------------------------------------\n");
                printf("Email is already in existence\n");
                printf("--------------------------------------\n");
                valid = 0;
                break;
            }
        }
        if (valid && validateEmail(email))     // Validate email format
        {
            valid = 0;
        }
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);      // store the new contact
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);    // store phone
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);    // store email
    addressBook->contactCount++;   // Increase contact count after adding new contact

    printf("--------------------------------------\n");
    printf("Do you want to save [Yes] or [No]: ");   // Ask user whether to save contact into file
    scanf("%s", choice);
    if (strcmp(choice, "Yes") == 0)        // Save contact details only when user selects Yes
    {
        saveContactsToFile(addressBook);
    }
    printf("--------------------------------------\n");
    printf("Contact created successfully\n");   // Display success message
}

void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)        // Check whether any contacts are available for searching
    {
        printf("No contacts available\n");
        return;          // Exit function if address book is empty
    }

    int option, found = 0;      // search option and contact is found or not
    char query[50];      // Store search input given by user

    printf("Search by:\n1. Name\n2. Phone\n3. Email\n4. Exit\n");   // Display search options
    printf("Enter your choice: ");
    scanf("%d", &option);   // Read search option
    getchar();            // Remove newline character from input buffer

    if (option == 4)      // Exit search menu
    {
        return;
    }

    if (option < 1 || option > 3)     // Check whether entered option is valid
    {
        printf("Invalid choice\n");
        return;
    }

    printf("Enter search text: ");   // Get search value from user
    scanf("%[^\n]", query);    // Read input including spaces

    printf("------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)     // Compare search text with every contact
    {
        char *field = (option == 1) ? addressBook->contacts[i].name
                    : (option == 2) ? addressBook->contacts[i].phone
                                    : addressBook->contacts[i].email;  // Select field based on user choice

        if (strstr(field, query) != NULL)          // Check whether search text is present in selected field
        {
            printf(" %-6d%-20s%-16s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);   // Display matching contact details
            found = 1;   // Update found status
        }
    }
    printf("------------------------------------------------------------\n");

    if (!found)    // If no contact matched with search value
    {
        printf("Contact not found\n");
    }
}

void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)     // Check whether contacts are available for editing
    {
        printf("No contacts available\n");
        return;  // Exit function if address book is empty
    }

    int option;                  // Store user selection for searching contact
    char query[50];              // Store search value entered by user
    int matches[MAX_CONTACTS];   // Store indexes of matching contacts
    int matchCount = 0;          // Count number of matching contacts

    printf("Edit by:\n1. Name\n2. Phone\n3. Email\n4. Exit\n");    // Display edit search options
    printf("Enter your choice: ");
    scanf("%d", &option);   // Read search option
    getchar();   // Remove newline character from input buffer

    if (option == 4)     // Exit edit menu
    {
        return;
    }
    if (option < 1 || option > 3)     // Check invalid option
    {
        printf("Invalid choice\n");
        return;
    }

    printf("Enter search text: ");   // Get search text from user
    scanf("%[^\n]", query);     // Read complete search input

    for (int i = 0; i < addressBook->contactCount; i++)      // Find all contacts matching search text
    {
        char *field = (option == 1) ? addressBook->contacts[i].name
                    : (option == 2) ? addressBook->contacts[i].phone
                                    : addressBook->contacts[i].email;
        if (strstr(field, query) != NULL)     // Check whether search text is available
        {
            matches[matchCount++] = i;       // Store matching contact index
        }
    }

    if (matchCount == 0)     // If no contact found
    {
        printf("Contact not found\n");
        return;
    }

    int index;           // Variable to store contact index to edit
    if (matchCount == 1) 
    {
        index = matches[0];   // If only one contact found, select directly
    }
    else                   // If multiple contacts found
    {
        printf("Multiple matching records found:\n");
        printf(" %-6s%-20s%-16s%-30s\n", "Index", "Name", "Phone", "Email");   // If multiple contacts found
        for (int k = 0; k < matchCount; k++) 
        {
            int i = matches[k];
            printf(" %-6d%-20s%-16s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }

        int chosen;     // Variable to store selected contact number
        printf("Enter the index of the record to edit: ");
        scanf("%d", &chosen);   // Read selected index
        getchar();   // Remove newline character
        chosen--;    // Convert user index to array index

        int valid = 0;      // Check whether selected index is valid
        for (int k = 0; k < matchCount; k++) 
        {
            if (matches[k] == chosen) 
            {
                valid = 1;
                break;
            }
        }
        if (!valid)    // Invalid index entered
        {
            printf("Invalid index\n");
            return;
        }
        index = chosen;   // Store selected contact index
    }

    int field;            // Variable to select which field to edit
    char newValue[50];    // Store new value entered by user
    char choice[10];      // Store save option

    printf("What do you want to edit:\n1. Name\n2. Phone\n3. Email\n4. Exit\n");   // Display edit options
    printf("Enter your choice: ");
    scanf("%d", &field);   // Read field selection
    getchar();   // Remove newline character

    if (field == 4)       // Exit edit operation
    {
        return;
    }

    if (field == 1)     // editing the name
    {
        printf("Enter the new name: ");
        scanf("%[^\n]", newValue);   // Read new name, including spaces
        for (int i = 0; i < addressBook->contactCount; i++)       // Check duplicate name
        {
            if (i != index && strcmp(addressBook->contacts[i].name, newValue) == 0) 
            {
                printf("Name is already in existence\n");
                return;
            }
        }
        if (validateName(newValue))     // Validate new name
        {
            return;
        }
        strcpy(addressBook->contacts[index].name, newValue);   // Update name
    }
    else if (field == 2)     // editing the phone number
    {
        printf("Enter the new phone number: ");
        scanf("%s", newValue);   // read the new phone number
        for (int i = 0; i < addressBook->contactCount; i++)     // check duplicate phone numbers
        {
            if (i != index && strcmp(addressBook->contacts[i].phone, newValue) == 0) 
            {
                printf("Phone number is already in existence\n");
                return;
            }
        }
        if (validatePhone(newValue))    // Validate phone number
        {
            return;
        }
        strcpy(addressBook->contacts[index].phone, newValue);   // Update phone number
    }
    else if (field == 3)     // editing the email
    {
        printf("Enter the new email: ");
        scanf("%s", newValue);   // read the new email
        for (int i = 0; i < addressBook->contactCount; i++)     // Check duplicate email
        {
            if (i != index && strcmp(addressBook->contacts[i].email, newValue) == 0) 
            {
                printf("Email is already in existence\n");
                return;
            }
        }
        if (validateEmail(newValue))    // Validate email format
        {
            return;
        }
        strcpy(addressBook->contacts[index].email, newValue);   // Update email
    }
    else    // Invalid field option
    {
        printf("Invalid choice\n");
        return;
    }

    printf("Do you want to save [Yes] or [No]: ");   // Ask user whether to save changes
    scanf("%s", choice);
    if (strcmp(choice, "Yes") == 0)       // Save updated contact details
    {
        saveContactsToFile(addressBook);
    }
    printf("Contact updated successfully\n");   // Display successful update message
}

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)     // Check whether contacts are available for deletion
    {
        printf("No contacts available\n");
        return;                            // Exit if address book is empty
    }

    int option;                 // Store search option selected by user
    char query[50];             // Store search value entered by user
    int matches[MAX_CONTACTS];  // Store indexes of matching contacts
    int matchCount = 0;         // Count number of matching contacts

    printf("Delete by:\n1. Name\n2. Phone\n3. Email\n4. Exit\n");   // Display delete search options
    printf("Enter your choice: ");
    scanf("%d", &option);   // Read search option
    getchar();   // Remove newline character from input buffer

    if (option == 4)      // Exit delete menu
    {
        return;
    }
    if (option < 1 || option > 3)     // Check whether option is valid
    {
        printf("Invalid choice\n");
        return;
    }

    printf("Enter search text: ");  // Get search text from user
    scanf("%[^\n]", query);   // Read complete search input

    for (int i = 0; i < addressBook->contactCount; i++)             // Search matching contacts
    {
        char *field = (option == 1) ? addressBook->contacts[i].name
                    : (option == 2) ? addressBook->contacts[i].phone
                                    : addressBook->contacts[i].email;
        if (strstr(field, query) != NULL)     // Check whether search text matches
        {
            matches[matchCount++] = i;  // Store matching contact index
        }
    }

    if (matchCount == 0)    // If no matching contact found
    {
        printf("Contact not found\n");
        return;
    }

    int index;      // Store index of contact to delete
    if (matchCount == 1)            // If only one record found, delete directly
    {
        index = matches[0];
    }
    else                     // If multiple contacts found
    {
        printf("Multiple matching records found:\n");
        printf(" %-6s%-20s%-16s%-30s\n", "Index", "Name", "Phone", "Email");   // Display matching contacts
        for (int k = 0; k < matchCount; k++) 
        {
            int i = matches[k];
            printf(" %-6d%-20s%-16s%-30s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
        int chosen;      // Store user selected index
        printf("Enter the index of the record to delete: ");
        scanf("%d", &chosen);   // Read selected contact index
        getchar();   // Remove newline character
        chosen--;    // Convert user index to array index

        int valid = 0;      // Check selected index validity
        for (int k = 0; k < matchCount; k++) 
        {
            if (matches[k] == chosen) 
            {
                valid = 1;
                break;
            }
        }
        if (!valid)     // Invalid index entered
        {
            printf("Invalid index\n");
            return;
        }
        index = chosen;   // Store selected contact index
    }

    char confirm[10];      // Store confirmation from user
    printf("About to delete: %s, %s, %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);   // Display contact which is going to delete
    printf("Are you sure you want to delete this contact? [Yes/No]: "); // Ask user confirmation before deleting
    scanf("%s", confirm);
    if (strcmp(confirm, "Yes") != 0)     // Cancel deletion if user does not enter Yes
    {
        printf("Deletion cancelled\n");
        return;
    }

    for (int j = index; j < addressBook->contactCount - 1; j++)    // Shift remaining contacts one position left
    {
        addressBook->contacts[j] = addressBook->contacts[j + 1];
    }
    addressBook->contactCount--;   // Reduce total contact count after deletion

    saveContactsToFile(addressBook);   // Save updated contacts into file
    printf("------------------------------------------------------------\n");
    printf("Contact deleted successfully\n");   // Display deletion success message
}
