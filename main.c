#include <stdio.h>
#include "csv.h"
#include "subscription.h"

int main(void)
{
    tCSVData test_data;
    int i;
    tPerson person;
    tPeople people;
    tSubscription subscription;
    tSubscription subscription2;
    tSubscriptions subscriptions;
    char buffer[1024];

    const char* test_people = "98765432J;Hendrik;Lorentz;987654321;hendrik.lorentz@example.com;his street, 5;00001;27/08/1954\n" \
        "33365111X;Marie;Curie;+33123456789;marie.curie@example.com;Radium street, 88;54321;07/10/1867\n" \
        "55565432Z;Nils;Gustaf Dalen;555123123;nils.gustaf@example.com;Picadilly street, 123;12345;25/11/1972\n" \
        "98765432J;Jean Baptiste;Perrin;999654654;jean.perrin@example.com;Champs-Elysees, 44;77777;12/01/1983\n" \
        "12345672C;Anne;Huiller;666789789;anne.huiller@example.com;rue percebe, 125;22222;12/01/1969";

    const char* test_subscriptions = "1;98765432J;01/01/2025;31/12/2025;Free;0;1\n" \
        "2;33365111X;01/05/2025;30/04/2026;Standard;29.95;3\n" \
        "3;88762222A;01/08/2025;31/07/2026;Premium;69.95;5\n" \
        "4;12345672C;15/06/2025;14/06/2026;Standard;29.95;3\n" \
        "3;88762222A;01/01/2026;31/12/2026;Premium;69.95;5\n" \
        "5;55565432Z;21/03/2025;20/03/2026;Free;0;1\n" \
        "6;11111111R;01/01/2025;31/12/2025;Premium;69.95;5\n" \
        "5;12345672C;01/01/2026;31/12/2026;Premium;69.95;5\n";

    const char* test_subscriptions2 = "7;98765432J;11/09/2025;17/04/2026;Premium;75.50;6\n";

    // Read people data
    csv_init(&test_data);
    csv_parse(&test_data, test_people, "PEOPLE");

    // Initialize people data
    people_init(&people);

    // Add people data
    for (i = 0; i < csv_numEntries(test_data); i++) {
        // Fills a person with all information
        person_parse(&person, csv_getEntry(test_data, i)[0]);
        // Add new person to the list (table) of people
        people_add(&people, person);
    }

    // Print current people
    printf("People:\n");
    people_print(people);

    // Remove people data
    csv_free(&test_data);

    // Read subscription data
    csv_init(&test_data);
    csv_parse(&test_data, test_subscriptions2, "SUBSCRIPTION");

    // Copy a subscription
    subscription_parse(&subscription, csv_getEntry(test_data, 0)[0]);
    subscription_cpy(&subscription2, subscription);

    // Print duplicated subscription
    printf("\nDuplicated subscription:\n");
    subscription_get(subscription2, buffer);
    printf("%s\n", buffer);

    // Remove subscription data
    csv_free(&test_data);

    // Read subscription data
    csv_init(&test_data);
    csv_parse(&test_data, test_subscriptions, "SUBSCRIPTION");

    // Initialize subscriptions data
    subscriptions_init(&subscriptions);

    // Add subscriptions data
    for (i = 0; i < csv_numEntries(test_data); i++) {
        subscription_parse(&subscription, csv_getEntry(test_data, i)[0]);
        subscriptions_add(&subscriptions, people, subscription);
    }

    // Remove subscriptions data
    csv_free(&test_data);

    // Print current subscriptions
    printf("\nSubscriptions:\n");
    subscriptions_print(subscriptions);

    printf("\nPress key to end...\n");
    getchar();
    return 0;
}
