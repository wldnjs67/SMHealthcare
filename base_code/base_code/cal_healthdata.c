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
	int i; //To declare variable i [for statement]
	
    FILE* file = fopen(HEALTHFILEPATH, "w"); // Pointer to open a file in writing mode
    
    if (file == NULL) { // If the file does not exist or the path is invalid, outputs ERROR message
        printf("There is no file for health data.\n");
        return; // If the code continues to run while the file cannot be opened, a runtime error occurs. So, requiring termination of the function execution.
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n"); // Print [Exercises] to the file.
    
    for (i=0;i<health_data->exercise_count; i++) { // Repeat as many times as the number of exercise records stored in the structure.
    	fprintf(file, "Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute); 
    	// Print the name of each exercise and the calories burned per minute to the file.
	}
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n"); // Print [Diets] to the file.
    
    for (i=0;i<health_data->diet_count; i++) { // Repeat as many times as the number of diets records stored in the structure.
    	fprintf(file, "Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);
    	// Print the name of each food and the calories intake in the file.
	}

    int remaining_calories = health_data->total_calories_intake - BASAL_METABOLIC_RATE - health_data->total_calories_burned;
    
    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basal Metabolic Rate: 1300 kcal\n"); // Outputs basal metabolic rate values (1300 kcal) to the text file.
    fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); // Outputs the total burned calories values to the text file.
    fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake); // Outputs the total calories intake values to the text file.
    fprintf(file, "The remaining calories: %d kcal\n", remaining_calories); // Outputs the remaining calories values to the text file.
    
    fclose(file); // Close the file
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
	int i; //To declare variable i [for statement]
	int remaining_calories = health_data->total_calories_intake - BASAL_METABOLIC_RATE - health_data->total_calories_burned; //To declare remaining_calories calculated from the formula.
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
    for (i=0;i<health_data->exercise_count; i++) { //Repeat [for statement] as much as execise_count
    	printf("Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->exercises[i].calories_burned_per_minute); // Outputs the users's history of exercises
    	// History: (1) Exercise that the user chose, (2) The corresponding calories for the exercise time entered by the user
	} 
  
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for (i=0;i<health_data->diet_count; i++) { //Repeat [for statement] as much as diet_count
    	printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake); // Outputs the users's history of diets
    	// History: (1) Food that the user chose, (2) The corresponding calories for food
	}

    printf("=======================================================================\n");


	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
    printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE); // Outputs basal metabolic rate values (1300 kcal) to prompt.
    printf("Total calories burned: %d kcal\n", health_data->total_calories_burned); // Outputs the total burned calories values to prompt.
    printf("Total calories intake: %d kcal\n", health_data->total_calories_intake); // Outputs the total calories intake values to prompt.
    printf("The remaining calories: %d kcal\n", remaining_calories); // Outputs the remaining calories values to prompt.
 
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
    if (remaining_calories==0) // If remaining_calories are zero
    {
    	printf("You have consumed all your calories for today!\n"); //Recommendations 
	}
	
    else if (remaining_calories<0)  // If remaining_calories are under zero
    {
    	printf("[WARNING] Too few calories!\n"); // Warning message
    	if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) // If the calorie intake have reached the recommended daily calories
    	   printf("Your total calorie intake for today has reached your goal!\n");
    	else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) // If the calorie intake are under the recommended daily calories
           printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n"); // Recommend for user to eat more 
		else // If the calories consumed are over the recommended daily calories
		   printf("You have eaten more calories than planned today, but you have exercised too much!\n"); // Recommend for user to exercise more 
	}
	
	else  // If remaining_calories are over zero
	{
		printf("Please exercise for your health!\n"); //Recommendations 
		if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) // If the calories consumed have reached the recommended daily calories
    	printf("Your total calorie intake for today has reached your goal!\n");
    	else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) // If the calories consumed are under the recommended daily calories
        printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n"); // Recommend for user to eat more
	}
	
	 printf("=======================================================================\n");
}
