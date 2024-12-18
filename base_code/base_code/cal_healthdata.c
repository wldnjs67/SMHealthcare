//
//  cal_healthdata.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w"); //Pointer to open a file in writing mode
    if (file == NULL) { //If the file does not exist or the path is invalid, outputs ERROR message
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n"); //Print [Exercises] to the file.
    for (i=0;i<health_data->exercise_count; i++) { //Repeat as many times as the number of exercise records stored in the structure.
    	fprintf(file, "Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute); 
    	//Print the name of each exercise and the calories burned per minute to the file.
	}
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n"); //Print [Diets] to the file.
    for (i=0;i<health_data->diet_count; i++) { //Repeat as many times as the number of diets records stored in the structure.
    	fprintf(file, "Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    	//Print the name of each food and the calories intake in the file.
	}


    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basal Metabolic Rate: 1300 kcal\n"); //Fix the basic metabolism at 1300 kcal and output it to the file.
    fprintf(file, "Total calories burned: %d kcal\n", health_data->total_burned_calories); //Outputs the total burned calorie values to the file.
    fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories); //Outputs the total calorie intake values to the file.
    fprintf(file, "The remaining calories: %d kcal\n", health_data->total_calories - 1300 - health_data->total_burned_calories);// Calculate the remaining calorie values and output it to the file.
    
    fclose(file);
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	int BASAL_METABOLIC_RATE = 1300; 
	int remaining_calories = health_data->total_calories - BASAL_METABOLIC_RATE - health_data->total_burned_calories;
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
    for (i=0;i<health_data->exercise_count; i++) {
    	printf("Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute);
	}
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for (i=0;i<health_data->diet_count; i++) {
    	printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
	}

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE);
    printf("Total calories burned: %d kcal\n", health_data->total_burned_calories);
    printf("Total calories intake: %d kcal\n", health_data->total_calories);
    printf("The remaining calories: %d kcal\n", remaining_calories);
 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    if (remaining_calories==0)
    {
    	printf("You have consumed all your calories for today!/n");
	}
    else if (remaining_calories<0)
    {
    	printf("[WARNING] Too few calories!\n");
    	if (health_data->total_calories == 2000)
    	   printf("Your total calorie intake for today has reached your goal!\n");
    	else if (health_data->total_calories < 2000)
           printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
		else 
		   printf("You have eaten more calories than planned today, but you have exercised too much!");    	
	}
	else
	{
		printf("Please exercise for your health!\n");
		if (health_data->total_calories == 2000)
    	printf("Your total calorie intake for today has reached your goal!\n");
    	else if (health_data->total_calories < 2000)
        printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
	}
	 printf("=======================================================================\n");
}
