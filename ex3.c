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
#define ONE_DAY_ADJUST 1 //using this to adjust our user days to the program days (program is reading 0-364)
#define ZERO_SALES 0 //using in case 4 to determine if brand hadn't sold any cars

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

//Functions
void printUnfoundData(int days[NUM_OF_BRANDS], int currentDay, char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
void insertDailyData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS], int currentDay); 
int checkPositiveValues(int salesData[NUM_OF_TYPES]);
int sumDailySales(int dayInput, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
void bestSoldBrand(int dayInput, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int findMaxBrand(int brandSales[NUM_OF_BRANDS]);
void bestSoldType(int dayInput, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int findMaxType(int typeSales[NUM_OF_TYPES]);
void printDataset(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], char brands[NUM_OF_BRANDS][BRANDS_NAMES],char types[NUM_OF_TYPES][TYPES_NAMES], int currentDay);
int sumBrandTotalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, int brandIndex);
void bestSoldBrandOverall (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
int sumTypeTotalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, int typeIndex);
void bestSoldTypeOverall (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, char types[NUM_OF_TYPES][TYPES_NAMES]);





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
            case addAll:{
                for (int i=0;i<NUM_OF_BRANDS;i++){
                    insertDailyData(cube, days, currentDay);//Running this function 5 times so each brand will have data
                    //inserted for this current day. 
                    //The way this function is built would make sure that each brand will have his data inserted, no duplication
                    //and no skipping brands. 
                }
                currentDay+=ONE_DAY_ADJUST; //After the program added data for all the brands in our current day, we are incrementing the counter by one day 
                //...
                break;}
            case stats:{
                printf("What day would you like to analyze?\n");
                int dayInput;
                scanf("%d",&dayInput);
                while (dayInput<1 || dayInput> DAYS_IN_YEAR || dayInput>currentDay){ //Conditions to validate the legit numbers (1-365) and 
                //to make sure the users is not asking data about a day that hadnt been reported yet (bigger than our current day)
                    printf("Please enter a valid day.\n");
                    printf("What day would you like to analyze?\n");
                    scanf("%d",&dayInput);
                };
                dayInput -= ONE_DAY_ADJUST; //Our program started from 0, wheareas our users will use days from 1 and so on, so we must adjust the given day to 
                //the days as counted in the program
                printf("In day number %d:\n", dayInput+ONE_DAY_ADJUST);
                //Using our predefined functions to print data:
                printf("The sales total was %d\n",sumDailySales(dayInput, cube)); 
                bestSoldBrand(dayInput, cube);
                bestSoldType(dayInput, cube);
                break;
            }
            case print: {
                printDataset(cube, brands, types, currentDay);
                break;
            }

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

int sumDailySales(int dayInput, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
    //Function to sum the total sales in a specific day
    int sum =0; //Initiating our sum as zero
    for (int i=0; i<NUM_OF_BRANDS; i++){//Iterating through all the brands
        for (int j=0; j<NUM_OF_TYPES; j++){//Iterating through all the types of each brand
            sum+= cube[dayInput][i][j]; //Summing each sales data.
        }
    }
    return sum;
};

void bestSoldBrand(int dayInput, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
    int brandsSales[NUM_OF_BRANDS]={0}; //Initiating an array that will contain the selling data
    //for each brand, starting at 0 for every brand. every brand is represented here in his 
    //regular index.
    for (int i=0; i<NUM_OF_BRANDS; i++){//Iterating through all brands
        for (int j=0; j<NUM_OF_TYPES; j++){//Iterating through types of each brand
            brandsSales[i]+= cube[dayInput][i][j];//Adding the sales of a type in a given day to the index 
            //of the brand in our array.
        }
    }
    //Now we must find the max item in our sales array, using the findMax function.
    int maxIndex = findMaxBrand(brandsSales);
    printf("The best sold brand with %d sales was %s\n", brandsSales[maxIndex], brands[maxIndex]);
}

void bestSoldType(int dayInput, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
    //Function that sums the sales of each type in a given day. 
    int typeSales[NUM_OF_TYPES]={0}; //Array to conatin the sales total, each index in the array represents the type index in 
    //our pre-definded settings.
    for (int i=0; i<NUM_OF_TYPES;i++){
        //Outer loop is iterating through the number of types
        for (int j=0; j<NUM_OF_BRANDS; j++){ 
            typeSales[i] += cube[dayInput][j][i]; //summing the sales of a single type, through all the brands.
        }
    }
    //Now on to find the max item in our sales array, using the findMaxType function.
    int maxIndex = findMaxType(typeSales);
    printf("The best sold type with %d sales was %s\n", typeSales[maxIndex], types[maxIndex]);
    //Printing the sales of the winning type, by using the index from the max function inside our sales array
    //Printing the name of the type using the index from the max function, as we know the indexes in the array are alligned 
    //with the types indexes
}

int findMaxBrand(int brandSales[NUM_OF_BRANDS]){
    //Function that gets an array of the brand sales, iterating over each item and concluding 
    // what index holds the greatest number, hence what brand has sold the most
    int currentLeader = 0;//Starting at the first index as our current leader
    for (int i=1; i<NUM_OF_BRANDS;i++){//checking every index from 1 and so on against our current leader
        if (brandSales[i] > brandSales[currentLeader]){ //if the current index is greater then the current leader,
        //we update the leader to be this current index
            currentLeader = i;
        }
    }
    return currentLeader;
}

int findMaxType(int typeSales[NUM_OF_TYPES]){//identical function to findMaxBrand, except we are using array the size of NUM_OF_TYPES
    int currentLeader = 0;
    for (int i=1; i<NUM_OF_TYPES; i++){
        if (typeSales[i] > typeSales[currentLeader]){
            currentLeader = i;
        }
    }
    return currentLeader;
}

void printDataset(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], char brands[NUM_OF_BRANDS][BRANDS_NAMES], char types[NUM_OF_TYPES][TYPES_NAMES], int currentDay){
    printf("*****************************************\n\n");
    for (int i=0; i < NUM_OF_BRANDS; i++){//Iterating through all brands by order
        printf("Sales for %s:\n", brands[i]); //Printing the base line for every brand
        int brandTotalSales = sumBrandTotalSales(cube, currentDay, i); //Checking if the total sales of a brand was 0 before we start printing daily stats
        if (brandTotalSales == ZERO_SALES){
            continue; //In a case of zero sales, we habe no intention the print the stats, so we continue to the next brand in the list.
        }
        for (int j=0; j<currentDay; j++){ //iterating through all past days
            printf("Day %d- ", j+ONE_DAY_ADJUST);//base print for each day
            for (int k=0; k<NUM_OF_TYPES;k++){
                printf("%s: %d ", types[k], cube[j][i][k]); //produces the name of the type through the types array, and the sales of the given type in the current day from the loop
                
            }
            printf("\n");
        }
    }
    printf("\n\n*****************************************\n");
}

int sumBrandTotalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, int brandIndex){
    //Function to iterate through a given brand total sales until the current day, to conclude its sales data.
    int brandSum = 0; //Starts at 0 and incremented with every sale
    for (int i=0; i<currentDay; i++){ //Starting at the first day until our current day.
        for (int j=0; j<NUM_OF_TYPES; j++){//In each day, we are counting the brand sales as a sum of all of his types sales
            brandSum += cube[i][brandIndex][j]; //adding the sales data of type j in our current day. this will run through all days.
        }
    }
    return brandSum;
}

int sumTypeTotalSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, int typeIndex){
    //simillar to the sumBrandTotalSales, except now the type is permanent, and the days and brand being iterated
    int typeSum = 0;
    for (int i=0; i<currentDay; i++){
        for (int j=0; j<NUM_OF_BRANDS; j++){
            typeSum += cube[i][j][typeIndex];
        }
    }
    return typeSum;
}

void bestSoldBrandOverall (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, char brands[NUM_OF_BRANDS][BRANDS_NAMES]){
    //function that will compute and conclude which is the top selling brand and how much sales did he make
    int brandSumsOverall[NUM_OF_BRANDS]={0}; //initiating an int array that will hold all the sums of sales of all brands. 
    for (int i=0;i<NUM_OF_BRANDS; i++){
        brandSumsOverall[i] = sumBrandTotalSales(cube, currentDay, i); //using function from previous cases in the program, now it will sum all the sales
        //of each brand until our current day and will put in under the brand's index in our array inside the function
    }
    int topBrandIndex = findMaxBrand(brandSumsOverall); //returns the index of the most sales, hence which is the most selling brand
    printf("The best-selling brand overall is %s: %d$\n", brands[topBrandIndex], brandSumsOverall[topBrandIndex]); //printing the top brand name from the
    //brands array and it sales sum from the array
}

void bestSoldTypeOverall (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int currentDay, char types[NUM_OF_TYPES][TYPES_NAMES]){
    //function that will compute and conclude which is the top selling type and how much sales did he make. 
    int typeSumsOverall[NUM_OF_TYPES]={0}; //array to hold sales of all types, alligned with their permanent index across the program
    for (int i=0; i<NUM_OF_TYPES; i++){ //running through all types
        typeSumsOverall[i] = sumTypeTotalSales (cube, currentDay, i); //using function that will sums all the sales of a given type until our current day
    }
    int topTypeIndex = findMaxType(typeSumsOverall); //findMaxType index returns the index of an item in array that holds the greatest number, hence
    //the index of the type that sold the most
    printf("The best-selling type of car is %s: %d$\n", types[topTypeIndex], typeSumsOverall[topTypeIndex]); //printing the top type name from the types
    //array and it sales from the sales array
}








