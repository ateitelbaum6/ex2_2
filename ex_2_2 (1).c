/******************
Name:
ID:
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
#define stats   3
#define print   4
#define insights  5
#define deltas  6
#define done    7

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

    // Initialize all slots in the data cube to -1 to signify they are empty
    for (int d = 0; d < DAYS_IN_YEAR; d++) {
        for (int b = 0; b < NUM_OF_BRANDS; b++) {
            for (int t = 0; t < NUM_OF_TYPES; t++) {
                cube[d][b][t] = -1;
            }
        }
    }

    printMenu();
    scanf("%d", &choice);
    
    while(choice != done){
        switch(choice){
            case addOne: {
                int day, brand;
                int suv, sedan, coupe, gt;
                
                scanf("%d %d", &day, &brand);
                
                if (day >= 1 && day <= DAYS_IN_YEAR && brand >= 0 && brand < NUM_OF_BRANDS) {
                    scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt);
                    
                    cube[day - 1][brand][0] = suv;
                    cube[day - 1][brand][1] = sedan;
                    cube[day - 1][brand][2] = coupe;
                    cube[day - 1][brand][3] = gt;
                    
                    days[brand]++;
                } else {
                    printf("Invalid input\n");
                }
                break;
            }
            case addAll: {
                int day;
                int suv, sedan, coupe, gt;
                
                scanf("%d", &day);
                
                if (day >= 1 && day <= DAYS_IN_YEAR) {
                    for (int b = 0; b < NUM_OF_BRANDS; b++) {
                        scanf("%d %d %d %d", &suv, &sedan, &coupe, &gt);
                        
                        cube[day - 1][b][0] = suv;
                        cube[day - 1][b][1] = sedan;
                        cube[day - 1][b][2] = coupe;
                        cube[day - 1][b][3] = gt;
                        
                        days[b]++;
                    }
                } else {
                    printf("Invalid input\n");
                }
                break;
            }
            case stats: {
                int day;
                scanf("%d", &day);

                if (day >= 1 && day <= DAYS_IN_YEAR) {
                    int total_sales = 0;
                    int highest_brand_sales = -1;
                    int best_brand_idx = 0;
                    int highest_type_sales = -1;
                    int best_type_idx = 0;

                    // Calculate brand totals for the specified day
                    for (int b = 0; b < NUM_OF_BRANDS; b++) {
                        int brand_sum = 0;
                        for (int t = 0; t < NUM_OF_TYPES; t++) {
                            if (cube[day - 1][b][t] != -1) {
                                brand_sum += cube[day - 1][b][t];
                            }
                        }
                        total_sales += brand_sum;
                        if (brand_sum > highest_brand_sales) {
                            highest_brand_sales = brand_sum;
                            best_brand_idx = b;
                        }
                    }

                    // Calculate vehicle type totals for the specified day
                    for (int t = 0; t < NUM_OF_TYPES; t++) {
                        int type_sum = 0;
                        for (int b = 0; b < NUM_OF_BRANDS; b++) {
                            if (cube[day - 1][b][t] != -1) {
                                type_sum += cube[day - 1][b][t];
                            }
                        }
                        if (type_sum > highest_type_sales) {
                            highest_type_sales = type_sum;
                            best_type_idx = t;
                        }
                    }

                    printf("In day number %d:\n", day);
                    printf("The sales total is %d\n", total_sales);
                    printf("The best-selling brand is %s: %d\n", brands[best_brand_idx], highest_brand_sales);
                    printf("The best-selling type of car is %s: %d\n", types[best_type_idx], highest_type_sales);
                } else {
                    printf("Invalid input\n");
                }
                break;
            }
            case print: {
                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    printf("Sales for %s:\n", brands[b]);
                    for (int d = 0; d < DAYS_IN_YEAR; d++) {
                        if (cube[d][b][0] != -1) { 
                            printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n", 
                                   d + 1, cube[d][b][0], cube[d][b][1], cube[d][b][2], cube[d][b][3]);
                        }
                    }
                }
                break;
            }
            case insights: {
                int overall_best_brand = 0, max_brand_sales = -1;
                int overall_best_type = 0, max_type_sales = -1;
                int overall_best_day = 0, max_day_sales = -1;

                // Determine top selling brand overall
                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    int brand_total = 0;
                    for (int d = 0; d < DAYS_IN_YEAR; d++) {
                        for (int t = 0; t < NUM_OF_TYPES; t++) {
                            if (cube[d][b][t] != -1) {
                                brand_total += cube[d][b][t];
                            }
                        }
                    }
                    if (brand_total > max_brand_sales) {
                        max_brand_sales = brand_total;
                        overall_best_brand = b;
                    }
                }

                // Determine top selling vehicle type overall
                for (int t = 0; t < NUM_OF_TYPES; t++) {
                    int type_total = 0;
                    for (int d = 0; d < DAYS_IN_YEAR; d++) {
                        for (int b = 0; b < NUM_OF_BRANDS; b++) {
                            if (cube[d][b][t] != -1) {
                                type_total += cube[d][b][t];
                            }
                        }
                    }
                    if (type_total > max_type_sales) {
                        max_type_sales = type_total;
                        overall_best_type = t;
                    }
                }

                // Determine the single highest sales day overall
                for (int d = 0; d < DAYS_IN_YEAR; d++) {
                    int day_total = 0;
                    for (int b = 0; b < NUM_OF_BRANDS; b++) {
                        for (int t = 0; t < NUM_OF_TYPES; t++) {
                            if (cube[d][b][t] != -1) {
                                day_total += cube[d][b][t];
                            }
                        }
                    }
                    if (day_total > max_day_sales) {
                        max_day_sales = day_total;
                        overall_best_day = d;
                    }
                }

                printf("The best-selling brand overall is %s: %d\n", brands[overall_best_brand], max_brand_sales);
                printf("The best-selling type of car is %s: %d\n", types[overall_best_type], max_type_sales);
                printf("The most profitable day was day number %d: %d\n", overall_best_day + 1, max_day_sales);
                break;
            }
            case deltas: {
                for (int b = 0; b < NUM_OF_BRANDS; b++) {
                    double total_delta = 0.0;
                    int delta_count = 0;

                    for (int d = 1; d < DAYS_IN_YEAR; d++) {
                        int today_total = 0;
                        int yesterday_total = 0;
                        int today_has_data = 0;
                        int yesterday_has_data = 0;

                        for (int t = 0; t < NUM_OF_TYPES; t++) {
                            if (cube[d][b][t] != -1) {
                                today_total += cube[d][b][t];
                                today_has_data = 1;
                            }
                            if (cube[d - 1][b][t] != -1) {
                                yesterday_total += cube[d - 1][b][t];
                                yesterday_has_data = 1;
                            }
                        }

                        if (today_has_data && yesterday_has_data) {
                            total_delta += (today_total - yesterday_total);
                            delta_count++;
                        }
                    }

                    double average_delta = 0.0;
                    if (delta_count > 0) {
                        average_delta = total_delta / delta_count;
                    }
                    printf("Brand: %s, Average Delta: %f\n", brands[b], average_delta);
                }
                break;
            }
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}
