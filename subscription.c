#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "subscription.h"

//////////////////////////////////
// Available methods
//////////////////////////////////

// Parse a tDate from string information
void date_parse(tDate *date, const char *s_date) {
    // Check output data
    assert(date != NULL);

    // Check input date
    assert(s_date != NULL);
    assert(strlen(s_date) == 10);

    // Parse the input date
    sscanf(s_date, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Copy the data from the source to destination
void date_cpy(tDate *destination, tDate source) {
    destination->day = source.day;
    destination->month = source.month;
    destination->year = source.year;
}

// Copy the data from the source to destination
void person_cpy(tPerson *destination, tPerson source) {
    // Copy identity document data
    strncpy(destination->document, source.document, MAX_DOCUMENT + 1);

    // Copy name data
    strncpy(destination->name, source.name, MAX_CHARS + 1);

    // Copy surname data
    strncpy(destination->surname, source.surname, MAX_CHARS + 1);

    // Copy phone data
    strncpy(destination->phone, source.phone, MAX_PHONE + 1);

    // Copy email data
    strncpy(destination->email, source.email, MAX_CHARS + 1);

    // Copy address data
    strncpy(destination->address, source.address, MAX_CHARS + 1);

    // Copy cp data
    strncpy(destination->cp, source.cp, MAX_CP + 1);

    // Copy the birthday date
    date_cpy(&(destination->birthday), source.birthday);
}

// Get person data using a string
void person_get(tPerson data, char *buffer) {
    // Print all data at same time
    sprintf(buffer, "%s;%s;%s;%s;%s;%s;%s;%02d/%02d/%04d",
            data.document,
            data.name,
            data.surname,
            data.phone,
            data.email,
            data.address,
            data.cp,
            data.birthday.day, data.birthday.month, data.birthday.year);
}

// Initialize the people data
void people_init(tPeople *data) {
    // Check input/output data
    assert(data != NULL);

    data->count = 0;
}

// Get person data of position index using a string
void people_get(tPeople data, int index, char *buffer) {
    assert(index >= 0 && index < data.count);
    person_get(data.elems[index], buffer);
}

// Return the position of a person with provided document. -1 if it does not exist
int people_find(tPeople data, const char *document) {
    int i = 0;
    while (i < data.count) {
        if (strcmp(data.elems[i].document, document) == 0) {
            return i;
        }
        i++;
    }

    return -1;
}

// Print people data
void people_print(tPeople data) {
    char buffer[1024];
    int i;
    for (i = 0; i < data.count; i++) {
        people_get(data, i, buffer);
        printf("%s\n", buffer);
    }
}

// Print subscriptions data
void subscriptions_print(tSubscriptions data) {
    char buffer[1024];
    int i;
    for (i = 0; i < data.count; i++) {
        subscriptions_get(data, i, buffer);
        printf("%s\n", buffer);
    }
}

//////////////////////////////////////
// EX2: Implement your methods here....
//////////////////////////////////////

// Parse input from CSVEntry
void person_parse(tPerson *data, tCSVEntry entry) {
    // Ex. 2a
}

// Add a new person to people data
void people_add(tPeople *people_data, tPerson person) {
    assert(people_data != NULL); // Check input data not NULL
    const int person_index = people_find(*people_data, person.document);
    if (person_index >= 0) {
        // Check is not already in people_data
        return;
    }

    const int people_count = people_data->count;
    assert(people_count < MAX_PEOPLE);

    people_data->elems[people_count] = person;
    people_data->count++;
}

// Parse input from CSVEntry
void subscription_parse(tSubscription *data, tCSVEntry entry) {
    // Ex. 2c
}

// Copy the data from the source to destination (individual data)
void subscription_cpy(tSubscription *destination, tSubscription source) {
    // Ex. 2d
}

// Get subscription data using a string
void subscription_get(tSubscription data, char *buffer) {
    // Ex. 2e
}

// Initialize subscriptions data
void subscriptions_init(tSubscriptions *data) {
    // Ex. 2f
}

// Add a new subscription
void subscriptions_add(tSubscriptions *data, tPeople people, tSubscription subscription) {
    // Ex. 2g
}

// Get subscription data of position index using a string
void subscriptions_get(tSubscriptions data, int index, char *buffer) {
    // Ex. 2h
}

// Returns the position of a subscription looking for id's subscription. -1 if it does not exist
int subscriptions_find(tSubscriptions data, int id) {
    // Ex. 2i

    return -1;
}
