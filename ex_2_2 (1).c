/******************
Name: Atara Teitelbaum
ID: 671938245
Assignment: ex2_2
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};


void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}


int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    for (int d = 0; d < DAYS_IN_YEAR; d++) {
        for (int b = 0; b < NUM_OF_BRANDS; b++) {
            for (int t = 0; t < NUM_OF_TYPES; t++) {
                cube[d][b][t] = -1;
            }
        }
    }
    
    printMenu();

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        break;
    }

    if (choice == done) {
        printf("Goodbye!\n");
        break;
    }

    switch (choice) {

            case addOne: {
                int day, brand;
                int suv, sedan, coupe, gt;
                if (scanf("%d %d", &day, &brand) != 2) {
                    printf("Invalid Input\n");
                    break;
                }
                if (day < 1 || day > DAYS_IN_YEAR || brand < 0 || brand >= NUM_OF_BRANDS) {
                    printf("Invalid input\n");
                    break;
                }

                if (day < 1 || day > DAYS_IN_YEAR || brand < 0 || brand >= NUM_OF_BRANDS) {
                    printf("Invalid input\n");
                    break;
                }

                 if (scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt) != 4) {
                     printf("Invalid Input\n");
                     break;
                 }

                    cube[day - 1][brand][0] = suv;
                    cube[day - 1][brand][1] = sedan;
                    cube[day - 1][brand][2] = coupe;
                    cube[day - 1][brand][3] = gt;
                       
                break;
            }
            case addAll: {
            int day;

            if (scanf("%d", &day) != 1) {
                printf("Invalid input\n");
                break;
            }

            if (day < 1 || day > DAYS_IN_YEAR) {
                printf("Invalid input\n");
                break;
            }

            for (int b = 0; b < NUM_OF_BRANDS; b++) {
                int suv, sedan, coupe, gt;

                if (scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt) != 4) {
                    printf("Invalid input\n");
                    break;
                }

                cube[day - 1][b][0] = suv;
                cube[day - 1][b][1] = sedan;
                cube[day - 1][b][2] = coupe;
                cube[day - 1][b][3] = gt;
            }
            break;
        }
        case stats: {
                int day;

            if (scanf("%d", &day) != 1) {
                printf("Invalid input\n");
                break;
            }

            if (day < 1 || day > DAYS_IN_YEAR) {
                printf("Invalid input\n");
                break;
            }

            int total_sales = 0;
            int best_brand = 0, best_brand_val = -1;
            int best_type = 0, best_type_val = -1;

            for (int b = 0; b < NUM_OF_BRANDS; b++) {
                int sum = 0;

                for (int t = 0; t < NUM_OF_TYPES; t++) {
                    if (cube[day - 1][b][t] != -1)
                        sum += cube[day - 1][b][t];
                }

                total_sales += sum;

                if (sum > best_brand_val) {
                    best_brand_val = sum;
                    best_brand = b;
                }
            }
            
            printf("In day number %d:\n", day);
            printf("The sales total is %d\n", total_sales);
            printf("The best-selling brand is %s: %d\n", brands[best_brand], best_brand_val);
            printf("The best-selling type of car is %s: %d\n", types[best_type], best_type_val);
            break;
        }
            
            case print: {
                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                printf("Sales for %s:\n", brands[b]);

                for (int d = 0; d < DAYS_IN_YEAR; d++) {
                    if (cube[d][b][0] != -1) {
                        printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n",
                               d + 1,
                               cube[d][b][0],
                               cube[d][b][1],
                               cube[d][b][2],
                               cube[d][b][3]);
                    }
                }
            }
            break;
        }

        case insights: {
            int bestB = 0, bestBval = -1;
            int bestT = 0, bestTval = -1;
            int bestD = 0, bestDval = -1;

            for (int b = 0; b < NUM_OF_BRANDS; b++) {
                int sum = 0;

                for (int d = 0; d < DAYS_IN_YEAR; d++)
                    for (int t = 0; t < NUM_OF_TYPES; t++)
                        if (cube[d][b][t] != -1)
                            sum += cube[d][b][t];

                if (sum > bestBval) {
                    bestBval = sum;
                    bestB = b;
                }
            }

            for (int t = 0; t < NUM_OF_TYPES; t++) {
                int sum = 0;

                for (int d = 0; d < DAYS_IN_YEAR; d++)
                    for (int b = 0; b < NUM_OF_BRANDS; b++)
                        if (cube[d][b][t] != -1)
                            sum += cube[d][b][t];

                if (sum > bestTval) {
                    bestTval = sum;
                    bestT = t;
                }
            }

            for (int d = 0; d < DAYS_IN_YEAR; d++) {
                int sum = 0;

                for (int b = 0; b < NUM_OF_BRANDS; b++)
                    for (int t = 0; t < NUM_OF_TYPES; t++)
                        if (cube[d][b][t] != -1)
                            sum += cube[d][b][t];

                if (sum > bestDval) {
                    bestDval = sum;
                    bestD = d;
                }
            }

            printf("The best-selling brand overall is %s: %d\n", brands[bestB], bestBval);
            printf("The best-selling type of car is %s: %d\n", types[bestT], bestTval);
            printf("The most profitable day was day number %d: %d\n", bestD + 1, bestDval);
            break;
        }

        case deltas: {
            for (int b = 0; b < NUM_OF_BRANDS; b++) {

                double total = 0;
                int count = 0;

                for (int d = 1; d < DAYS_IN_YEAR; d++) {

                    int today = 0, yesterday = 0;
                    int ok1 = 0, ok2 = 0;

                    for (int t = 0; t < NUM_OF_TYPES; t++) {
                        if (cube[d][b][t] != -1) {
                            today += cube[d][b][t];
                            ok1 = 1;
                        }
                        if (cube[d - 1][b][t] != -1) {
                            yesterday += cube[d - 1][b][t];
                            ok2 = 1;
                        }
                    }

                    if (ok1 && ok2) {
                        total += (today - yesterday);
                        count++;
                    }
                }

                double avg = (count > 0) ? total / count : 0;

                printf("Brand: %s, Average Delta: %f\n", brands[b], avg);
            }
            break;
        }

        default:
            printf("Invalid input\n");
        }

        printMenu();
    }

    return 0;
}
