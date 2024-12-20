//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r"); // Pointer to open a file in read mode
    if (file == NULL) { // If the file does not exist or the path is invalid, outputs ERROR message
        printf("There is no file for exercises! \n");
        return; //If the code continues to run while the file cannot be opened, a runtime error occurs. So, requiring termination of the function execution.
    }
    
    // To declare variables
    char exercise_name[MAX_EXERCISE_NAME_LEN];
    int calories_burned_per_minute;
    
    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%s %d", exercise_name, &calories_burned_per_minute)==2) { // Successful reading of both data results in ==2 condition and a repeat statement is executed

        if (exercise_list_size >= MAX_EXERCISES){
        	break; // When the array is larger than the maximum size, the data will no longer be read and exit.
		}
		strcpy(exercise_list[exercise_list_size].exercise_name, exercise_name); // Save read exercise_name by Copying String Function
		// Pointers approaching the next empty space in an array that stores the name of exercise within the exercise structure
        exercise_list[exercise_list_size].calories_burned_per_minute = calories_burned_per_minute; // Save read calories burned per minute to member of the exercise structure
        exercise_list_size++; // Increase exercise_list_size 
    }

    fclose(file); // Close the file
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    // To declare variables
    int choice, duration, i; 
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");

    // ToCode: to enter the exercise to be chosen with exit option
    for (i = 0; i < exercise_list_size; i++) 
	{
        printf("%d. %s (%d kcal)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute); //Outputs Exercise List (Number, Name, Calories) 
    }
    printf("0. Exit\n"); // Exit option
    
 	printf("Choose a number for exercise selection (Choose Number 0 to Exit): "); //Outputs a comment that allows the user to choose the type of exercise
	scanf("%d", &choice);  
    
	if (choice == 0) { // If the user wants to exit, she must enter 0.
        printf("Exit exercise selection.\n");
        return; // Requiring termination of the function execution.
    }
    
    if (choice < 1 || choice > exercise_list_size) { // If the user enters the wrong number, an ERROR message is output.
        printf("[Error] Invalid option. \n");
        printf("Please try again! \n");
        return; // Requiring termination of the function execution.
	}
	
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);
    
    if (duration <= 0) { // If the user wrote duration in negative numbers, an ERROR message is output.
        printf("[Error] Duration must be greater than 0.\n");
        return; // Requiring termination of the function execution.
    }
    
    // ToCode: to enter the selected exercise and total calcories burned in the health data
    int burned_calories = exercise_list[choice - 1].calories_burned_per_minute * duration;
    // Calculate burned calories by multiplying calories_burned_per_minute with the duration of the exercise
    
    strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice - 1].exercise_name); 
    // Copy the name of the selected exercise from exercise_list to the next available slot in health_data->exercises
    
    // Access the exercise_name of (the exercise_count)th element in the exercise array of health_data structure
    // Pointers approaching the next empty space in an array that stores the name of exercise within the HealthData structure
    
    // exercise_list[choice-1].name: Exercise name that the user chose
    
    health_data->exercises[health_data->exercise_count].calories_burned_per_minute = burned_calories; 
    // Store the total burned calories for the selected exercise in health_data->exercises at the current index
    // health_data->exercises[health_data->exercise_count].calories_burned_per_minute => structure pointer->member(calories)
    
    health_data->exercise_count++;
    // Increase exercise_count for saving a new exercise record
    
    health_data->total_calories_burned += burned_calories;
    // total_calories_burned: Stores the total calories burned by the user so far within the structure
    // += operation: Updates the total burned calories by adding the calories burned from the selected exercise
    
    printf("You have chosen %s for %d minutes. Total burned calories: %d kcal.\n", exercise_list[choice - 1].exercise_name, duration, burned_calories);
    // Outputs the calories of the exercise you have selected  and Total burned calories.  
    printf("Your total burned calories so far: %d kcal.\n", health_data->total_calories_burned);
    // Outputs the total calories consumed so far.
}

