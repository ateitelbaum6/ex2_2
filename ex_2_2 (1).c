/******************
Name:
ID:
Assignment: ex3
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

char brands[NUM_OF_BRANDS][BRANDS_NAMES] =
{"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};

char types[NUM_OF_TYPES][TYPES_NAMES] =
{"SUV", "Sedan", "Coupe", "GT"};

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

/* ---------------- helpers ---------------- */

int sumBrandDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day, int brand){
    int sum = 0;
    for(int t = 0; t < NUM_OF_TYPES; t++){
        sum += cube[day][brand][t];
    }
    return sum;
}

int sumDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int day){
    int sum = 0;
    for(int b = 0; b < NUM_OF_BRANDS; b++){
        for(int t = 0; t < NUM_OF_TYPES; t++){
            sum += cube[day][b][t];
        }
    }
    return sum;
}

/* ---------------- main ---------------- */

int main() {

    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    int currentDay = 0;

    /* init cube */
    for(int d = 0; d < DAYS_IN_YEAR; d++){
        for(int b = 0; b < NUM_OF_BRANDS; b++){
            for(int t = 0; t < NUM_OF_TYPES; t++){
                cube[d][b][t] = -1;
            }
        }
    }

    printMenu();
    scanf("%d", &choice);

    while(choice != done){

        switch(choice){

        /* ---------------- PART 1 ---------------- */
        case addOne: {
            int brand;
            scanf("%d", &brand);

            if(brand < 0 || brand >= NUM_OF_BRANDS){
                printf("This brand is not valid\n");
                break;
            }

            for(int t = 0; t < NUM_OF_TYPES; t++){
                scanf("%d", &cube[currentDay][brand][t]);
            }

            days[brand]++;
            break;
        }

        /* ---------------- PART 2 ---------------- */
        case addAll: {
            int filled[NUM_OF_BRANDS] = {0};

            while(1){

                /* print missing brands */
                printf("No data for brands ");
                int first = 1;
                for(int b = 0; b < NUM_OF_BRANDS; b++){
                    if(!filled[b]){
                        if(!first) printf(" ");
                        printf("%s", brands[b]);
                        first = 0;
                    }
                }
                printf("\nPlease complete the data\n");

                /* check done */
                int doneFlag = 1;
                for(int b = 0; b < NUM_OF_BRANDS; b++){
                    if(!filled[b]) doneFlag = 0;
                }
                if(doneFlag){
                    currentDay++;
                    break;
                }

                int brand;
                scanf("%d", &brand);

                if(brand < 0 || brand >= NUM_OF_BRANDS || filled[brand]){
                    printf("This brand is not valid\n");
                    continue;
                }

                for(int t = 0; t < NUM_OF_TYPES; t++){
                    scanf("%d", &cube[currentDay][brand][t]);
                }

                filled[brand] = 1;
            }
            break;
        }

        /* ---------------- PART 3 ---------------- */
        case stats: {
            int day;

            while(1){
                printf("What day would you like to analyze?\n");
                scanf("%d", &day);

                day--;

                if(day < 0 || day >= currentDay){
                    printf("Please enter a valid day.\n");
                    continue;
                }

                int total = sumDay(cube, day);

                int bestBrand = 0, bestType = 0;
                int brandSum[NUM_OF_BRANDS] = {0};
                int typeSum[NUM_OF_TYPES] = {0};

                for(int b = 0; b < NUM_OF_BRANDS; b++){
                    for(int t = 0; t < NUM_OF_TYPES; t++){
                        brandSum[b] += cube[day][b][t];
                        typeSum[t] += cube[day][b][t];
                    }
                }

                for(int b = 1; b < NUM_OF_BRANDS; b++)
                    if(brandSum[b] > brandSum[bestBrand])
                        bestBrand = b;

                for(int t = 1; t < NUM_OF_TYPES; t++)
                    if(typeSum[t] > typeSum[bestType])
                        bestType = t;

                printf("In day number %d:\n", day + 1);
                printf("The sales total was %d\n", total);
                printf("The best sold brand with %d sales was %s\n",
                       brandSum[bestBrand], brands[bestBrand]);
                printf("The best sold type with %d sales was %s\n",
                       typeSum[bestType], types[bestType]);
                break;
            }
            break;
        }

        /* ---------------- PART 4 ---------------- */
        case print: {
            for(int d = 0; d < currentDay; d++){
                printf("*****************************************\n");
                printf("Sales for day %d:\n", d + 1);

                for(int b = 0; b < NUM_OF_BRANDS; b++){
                    printf("%s: ", brands[b]);
                    for(int t = 0; t < NUM_OF_TYPES; t++){
                        printf("%d ", cube[d][b][t]);
                    }
                    printf("\n");
                }
            }
            break;
        }

        /* ---------------- PART 5 ---------------- */
        case insights: {
            int brandSum[NUM_OF_BRANDS] = {0};
            int typeSum[NUM_OF_TYPES] = {0};
            int daySum[DAYS_IN_YEAR] = {0};

            for(int d = 0; d < currentDay; d++){
                for(int b = 0; b < NUM_OF_BRANDS; b++){
                    for(int t = 0; t < NUM_OF_TYPES; t++){
                        int val = cube[d][b][t];
                        brandSum[b] += val;
                        typeSum[t] += val;
                        daySum[d] += val;
                    }
                }
            }

            int bestB = 0, bestT = 0, bestD = 0;

            for(int i = 1; i < NUM_OF_BRANDS; i++)
                if(brandSum[i] > brandSum[bestB]) bestB = i;

            for(int i = 1; i < NUM_OF_TYPES; i++)
                if(typeSum[i] > typeSum[bestT]) bestT = i;

            for(int i = 1; i < currentDay; i++)
                if(daySum[i] > daySum[bestD]) bestD = i;

            printf("The best-selling brand overall is %s:%d$\n",
                   brands[bestB], brandSum[bestB]);

            printf("The best-selling type of car is %s:%d$\n",
                   types[bestT], typeSum[bestT]);

            printf("The most profitable day was day number %d:%d$\n",
                   bestD + 1, daySum[bestD]);

            break;
        }

        /* ---------------- PART 6 ---------------- */
        case deltas: {

            for(int b = 0; b < NUM_OF_BRANDS; b++){

                double sum = 0;
                int prev = -1;
                int count = 0;

                for(int d = 0; d < currentDay; d++){

                    int s = sumBrandDay(cube, d, b);

                    if(prev != -1){
                        sum += (s - prev);
                        count++;
                    }

                    prev = s;
                }

                double avg = (count == 0) ? 0 : sum / count;

                printf("Brand: %s, Average Delta: %.2f\n",
                       brands[b], avg);
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
