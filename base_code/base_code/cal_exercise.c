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
    FILE *file = fopen(EXERCISEFILEPATH, "r"); //Pointer to open a file in read mode
    if (file == NULL) { //If the file does not exist or the path is invalid, outputs ERROR message
        printf("There is no file for exercises! \n");
        return;
    }
    
    //To declare variables
    char exercise_name[MAX_EXERCISE_NAME_LEN];
    int calories_burned_per_minute;
    
    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%s %d", exercise_name, &calories_burned_per_minute)==2) { //Successful reading of both data results in ==2 condition and a repeat statement is executed

        if (exercise_list_size >= MAX_EXERCISES){
        	break; //When the array is larger than the maximum size, the data will no longer be read and exit.
		}
		strcpy(exercise_list[exercise_list_size].exercise_name, exercise_name); //Save read exercise_name by Copying String Function
        exercise_list[exercise_list_size].calories_burned_per_minute = calories_burned_per_minute; //Save read calories 
        exercise_list_size++;
    }

    fclose(file); //Close the file
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
    int choice, duration, i; //To declare variables
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");

    // ToCode: to enter the exercise to be chosen with exit option
    for (i = 0; i < exercise_list_size; i++) 
	{
        printf("%d. %s (%d kcal)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute); //Outputs Exercise List (Name, Calories) 
    }
    printf("0. Exit\n"); //Exit option
    
 	printf("Choose a number for exercise selection (Choose Number 0 to Exit): "); //Outputs a comment that allows the user to choose the type of exercise
	scanf("%d", &choice);  
    
	if (choice == 0) { //If the user wants to exit, she must press 0.
        printf("Exit exercise selection.\n");
        return;
    }
    
    if (choice < 1 || choice > exercise_list_size) { //If the user enters the wrong number, an error message is output.
        printf("[Error] Invalid option. \n");
        printf("Please try again! \n");
        return;
	}
	
    // To enter the duration of the exercise
    printf("Enter the duration of the exercise (in min.): ");
    scanf("%d", &duration);
    
    if (duration <= 0) { //if the user wrote down duration in negative numbers
        printf("[Error] Duration must be greater than 0.\n");
        return;
    }
    
    // ToCode: to enter the selected exercise and total calcories burned in the health data
    int burned_calories = exercise_list[choice - 1].calories_burned_per_minute * duration;
    //// Calculate total burned calories by multiplying calories burned per minute with the duration of the exercise
    
    strcpy(health_data->exercises[health_data->exercise_count].exercise_name, exercise_list[choice - 1].exercise_name); 
    // Copy the name of the selected exercise from exercise_list to the next available slot in health_data->exercises
    //health_data->exercises[health_data->exercise_count].exercise_name => structure pointer->member(name)
    //exercise_list[choice-1].name: Exercise name that the user chose
    
    health_data->exercises[health_data->exercise_count].calories_burned_per_minute = burned_calories; 
    // Store the total burned calories for the selected exercise in health_data->exercises at the current index
    //health_data->exercises[health_data->exercise_count].calories_burned_per_minute => structure pointer->member(calories)
    
    health_data->exercise_count++;
    // Increment the exercise_count to track the next available index for storing a new exercise record
    
    health_data->total_calories_burned += burned_calories;
    // total_calories_burned: Stores the total calories burned by the user so far within the structure
    // += operation: Updates the total burned calories by adding the calories burned from the selected exercise
    
    printf("You have chosen %s for %d minutes. Total burned calories: %d kcal.\n", exercise_list[choice - 1].exercise_name, duration, burned_calories);
    //Outputs the calories of the exercise you have selected  and Total burned calories.  
    printf("Your total burned calories so far: %d kcal.\n", health_data->total_calories_burned);
    //Outputs the total calories consumed so far.
}

