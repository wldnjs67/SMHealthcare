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
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%s %d", exercise_name, &calories_burned_per_minute==2) { //Successful reading of both data results in ==2 condition and a repeat statement is executed

        if (exercise_list_size >= MAX_EXERCISES){
        	break; //When the array is larger than the maximum size, the data will no longer be read and exit.
		}
		strcpy(exercise_list[exercise_list_size].name, exercise_name); //Save read food_name by Copying String Function
        exercise_list[exersize_list_size].calories = calories_burned_per_minute; //Save read calorie 
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
    int choice, duration, i;
    
    // ToCode: to provide the options for the exercises to be selected
    printf("The list of exercises: \n");


    // ToCode: to enter the exercise to be chosen with exit option
    for (i = 0; i < exercise_list_size; i++) 
	{
        printf("%d. %s (%d kcal)\n", i+1, exercise_list[i].name, exercise_list[i].calories);
    }
    
    printf("0. Exit\n");
 	printf("Choose a number for exercise selection (Choose Number 0 to Exit): ");
	scanf("%d", &choice);
    
	if (choice == 0) {
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
    
    if (duration <= 0) {
        printf("[Error] Duration must be greater than 0.\n");
        return;
    }
    
    // ToCode: to enter the selected exercise and total calcories burned in the health data
    int burned_calories = exercise_list[choice - 1].calories * duration;
    
    strcpy(health_data->last_exercise.name, exercise_list[choice - 1].name);
    health_data->last_exercise.calories = burned_calories;
    
    health_data->total_burned_calories += burned_calories;
    
    printf("You have chosen %s for %d minutes. Total burned calories: %d kcal.\n", health_data->last_exercise.name, duration, burned_calories);
    
    printf("Your total burned calories so far: %d kcal.\n", health_data->total_burned_calories);
}
