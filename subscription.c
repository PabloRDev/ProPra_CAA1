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
    scanf(s_date, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
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
            data.surname,
            data.name,
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

// 2a - Parse input from CSVEntry
void person_parse(tPerson *person, const tCSVEntry entry) {
    assert(person != NULL);
    assert(entry.fields != NULL);
    assert(entry.numFields >= 8);

    // 33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867
    strcpy(person->document, entry.fields[0]);
    strcpy(person->surname, entry.fields[1]);
    strcpy(person->name, entry.fields[2]);
    strcpy(person->phone, entry.fields[3]);
    strcpy(person->email, entry.fields[4]);
    strcpy(person->address, entry.fields[5]);
    strcpy(person->cp, entry.fields[6]);
    sscanf(entry.fields[7], "%d/%d/%d", &person->birthday.day, &person->birthday.month, &person->birthday.year);
}

// 2b - Add a new person to people data
void people_add(tPeople *people_data, const tPerson person) {
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

// 2c - Parse input from CSVEntry
void subscription_parse(tSubscription *subscription, const tCSVEntry entry) {
    assert(subscription != NULL);
    assert(entry.fields != NULL);
    assert(entry.numFields >= 7);

    // 2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3
    subscription->id = atoi(entry.fields[0]);
    strcpy(subscription->document, entry.fields[1]);
    sscanf(entry.fields[2], "%d/%d/%d", &subscription->startDate.day, &subscription->startDate.month, &subscription->startDate.year);
    sscanf(entry.fields[3], "%d/%d/%d", &subscription->endDate.day, &subscription->endDate.month, &subscription->endDate.year);
    subscription->plan = plan_parse(entry.fields[4]);
    subscription->price = atof(entry.fields[5]); // atof -> convert string to float
    subscription->numDevices = atoi(entry.fields[6]);
}

// 2d - Copy the data from the source to destination (individual data)
void subscription_cpy(tSubscription *destination, tSubscription source) {
    destination->id = source.id;
    strncpy(destination->document, source.document, MAX_DOCUMENT + 1);
    destination->plan = source.plan;
    destination->price = source.price;
    date_cpy(&destination->startDate, source.startDate);
    date_cpy(&(destination->endDate), source.endDate);
    destination->numDevices = source.numDevices;
}

// 2e - Get subscription data using a string
void subscription_get(tSubscription subscription, char *buffer) {
    char formatted_price[20];
    round_price(subscription.price, formatted_price);

    sprintf(buffer, "%d;%s;%02d/%02d/%04d;%02d/%02d/%04d;%s;%s;%d",
            subscription.id,
            subscription.document,
            subscription.startDate.day, subscription.startDate.month, subscription.startDate.year,
            subscription.endDate.day, subscription.endDate.month, subscription.endDate.year,
            plan_to_string(subscription.plan),
            formatted_price,
            subscription.numDevices
    );
}

// 2f - Initialize subscriptions data
void subscriptions_init(tSubscriptions *subscriptions_data) {
    // Check input/output data
    assert(subscriptions_data != NULL);

    subscriptions_data->count = 0;
}

// 2g - Add a new subscription
void subscriptions_add(tSubscriptions *subscriptions_data, const tPeople people, const tSubscription subscription) {
    assert(subscriptions_data != NULL); // Check input data not NULL

    const char *subscriber_id = subscription.document;
    assert(subscriber_id != NULL); // Check subscriber not NULL
    if (people_find(people, subscriber_id) < 0) {
        // Check subscriber is in people table
        return;
    }

    const int subscription_index = subscriptions_find(*subscriptions_data, subscription.id);
    if (subscription_index >= 0) {
        // Check subscription is not already in subscriptions_data
        return;
    }

    const int subscriptions_count = subscriptions_data->count;
    assert(subscriptions_count < MAX_SUBSCRIPTIONS);

    subscriptions_data->elems[subscriptions_count] = subscription;
    subscriptions_data->count++;
}

// 2h - Get subscription data of position index using a string
void subscriptions_get(tSubscriptions subscriptions_data, const int index, char *buffer) {
    assert(index >= 0 && index < subscriptions_data.count);
    subscription_get(subscriptions_data.elems[index], buffer);
}

// 2i - Returns the position of a subscription looking for id's subscription. -1 if it does not exist
int subscriptions_find(const tSubscriptions subscriptions_data, const int id) {
    int i = 0;
    while (i < subscriptions_data.count) {
        if (subscriptions_data.elems[i].id == id) {
            return i;
        }
        i++;
    }

    return -1;
}

tPlan plan_parse(const char* plan_string) {
    if (strcmp(plan_string, "Free") == 0) {
        return Free;
    }
    if (strcmp(plan_string, "Standard") == 0) {
        return Standard;
    }
    if (strcmp(plan_string, "Premium") == 0) {
        return Premium;
    }

    fprintf(stderr, "Error: Unknown plan '%s'\n", plan_string);
    exit(EXIT_FAILURE);  // Stop execution if the value is invalid
}

char* plan_to_string(const tPlan plan) {
    switch (plan) {
        case Free: return "Free";
        case Standard: return "Standard";
        case Premium: return "Premium";
    }

    return "";
}

float round_price(const float price, char *formatted_price) {
    float roundedPrice = (int)(price * 100 + 0.5) / 100.0;
    // int
    if ((int)roundedPrice == roundedPrice) {
        sprintf(formatted_price, "%.0f", roundedPrice);
    // 1f
    } else if ((int)(roundedPrice * 10) == roundedPrice * 10) {
        sprintf(formatted_price, "%.1f", roundedPrice);
    // 2f
    } else {
        sprintf(formatted_price, "%.2f", roundedPrice);
    }

    return roundedPrice;
}

