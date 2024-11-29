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
//Defining numbers to all of our car types:
#define SUV_NUM 0
#define SEDAN_NUM 1
#define COUPE_NUM 2
#define GT_NUM 3
#define TRUE 1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

//Functions
void printUnfoundData(int days[NUM_OF_BRANDS], int currentDay, char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
void insertDailyData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int currentDay); 
int checkPositiveValues(int salesData[NUM_OF_TYPES]);




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

    //Initiating all of the values in our cube to -1.
    for (int i=0; i<DAYS_IN_YEAR;i++){
        for (int j=0; j<NUM_OF_BRANDS;j++){
            for (int k=0; k<NUM_OF_TYPES;k++){
                cube[i][j][k] = -1;
            }
        }
    }

    int days[NUM_OF_BRANDS] = {0};
    int currentDay = 0; //A counter integer to keep track of the current day for all brands
    int choice;

    printMenu();
    scanf("%d", &choice);
    while(choice != done){
        switch(choice){
            case addOne:
                //...
                break;
            case addAll:
                for (int i=0;i<NUM_OF_BRANDS;i++){
                    insertDailyData(cube, days, currentDay);//Running this function 5 times so each brand will have data
                    //inserted for this current day. 
                    //The way this function is built would make sure that each brand will have his data inserted, no duplication
                    //and no skipping brands. 
                }
                currentDay+=1;
                //...
                break;
            /*
             ......
             */
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


void printUnfoundData(int days[NUM_OF_BRANDS], int currentDay, char brands[NUM_OF_BRANDS][BRANDS_NAMES]){
    //This function will iterate each brand current day against the program current day to check if it is yet to 
    //recieve sales data for today
    printf("No data for brands"); //printing the basic
    for (int i=0;i<NUM_OF_BRANDS;i++){
        if (days[i]== currentDay){//if the brand's current day is equal to the program day, it means the the brand
        //hadn't reported sales yet for today, therefor the user must be aware of this
            printf(" %s",brands[i]);
        }
    }
    printf(".\n");
    printf("Please complete the data.\n");
}

void insertDailyData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int currentDay){
    printUnfoundData(days, currentDay, brands); //Displaying the user the brands which require data insertion
    int brandNum; //Variable to be the user's chosen brand to update data for
    scanf("%d", &brandNum);
    while (brandNum < 0 || brandNum >= NUM_OF_BRANDS || days[brandNum] != currentDay){
        //Checking the user's input for the brand isn't out of range of our brands, and also that the brand's data hadn't already 
        //was reported today.
        printf("The brand is not valid.\n");
        printUnfoundData(days, currentDay, brands);
        scanf("%d", &brandNum);//Recieving input again until it is valid. 
    }
    int dailySalesData[NUM_OF_TYPES]; //This array will store the sales values. Using array so it will be easier to check
    //the values' integrity and to be alligned with the third-dimension in our cube.
    int isValidValues = scanf(" %d %d %d %d",&dailySalesData[SUV_NUM],&dailySalesData[SEDAN_NUM], &dailySalesData[COUPE_NUM],&dailySalesData[GT_NUM]);
    //As we insert our user inputs into the salesData array, we are checking that we recieved 4 inputs, as any other 
    //number of inputs will be invalid input
    while (isValidValues != NUM_OF_TYPES){
        //Validating that our user indeed inserted 4 different integers, or we are asking him to insert values again.
        printf("Invalid input.\n");
        isValidValues = scanf(" %d %d %d %d",&dailySalesData[SUV_NUM],&dailySalesData[SEDAN_NUM], &dailySalesData[COUPE_NUM],&dailySalesData[GT_NUM]);
    };
    int positiveValues = checkPositiveValues(dailySalesData); //Variable would set to be true if our array indeed 
    //contains only positive numbers, because reasonably we can't recieve a negative number of sales.
    while (positiveValues!=TRUE || isValidValues != NUM_OF_TYPES){
        //This condition would make sure 2 critical things: first, all of our sales data is positive or 0.
        //The second thing we are making sure is that our user indeed inserted 4 different values. 
        //Although we already made sure of this, we need to be aware that if the user fails the positiveValue test,
        //He will have a second chance to input his values, and then he can be mistaken.
        printf("Invalid input.\n");
        isValidValues = scanf(" %d %d %d %d",&dailySalesData[SUV_NUM],&dailySalesData[SEDAN_NUM], &dailySalesData[COUPE_NUM],&dailySalesData[GT_NUM]);
        positiveValues = checkPositiveValues(dailySalesData);
        //Taking inputs again and checking there are 4 of them and they are all positive, or we are staying in this while loop
        //until we will recieve a legit input.
    }
    //If we got here, it means we have a legitimate brand number and sales inputs.
    //Proceeding to insert the data to our cube:
    //In the current day, for our current brand we will insert each input to it degisnated car type.
    for (int i=0; i<NUM_OF_TYPES; i++){
        cube[currentDay][brandNum][i] = dailySalesData[i];
    }
    days[brandNum]+=1; //Inserted data for current brand for today, so we are incrementing his days counter 
    //so the user won't be able to choose him again for today.
}

int checkPositiveValues(int salesData[NUM_OF_TYPES]){ //Function designated to determine if all of the integers in an array
//are positive.
    int isArrayPositive = TRUE; //Initiating our assumption to be true.
    for (int i=0; i<NUM_OF_TYPES; i++){
        if (salesData[i] < 0){
            isArrayPositive = 0;
            //if we are met with a negative int, we are seeing the array as negative, and we are changing our variable.
        }
    }
    return isArrayPositive;
}




