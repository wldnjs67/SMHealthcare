//
//  cal_diets.c
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

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r"); // Pointer to open a file in read mode
    
    if (file == NULL) { // If the file does not exist or the path is invalid, outputs ERROR message
        printf("There is no file for diets! \n");
        return; //If the code continues to run while the file cannot be opened, a runtime error occurs. So, requiring termination of the function execution.
    }
    
    char food_name[MAX_FOOD_NAME_LEN]; 
    int calories_intake;    

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%s %d", food_name, &calories_intake)==2) { // Successful reading of both data results in ==2 condition and a repeat statement is executed
    	
        if (diet_list_size >= MAX_DIETS){
        	break; // When the array is larger than the maximum size, the data will no longer be read and exit.
		}
		strcpy(diet_list[diet_list_size].food_name, food_name); // Save read food_name by Copying String Function
		// Pointers approaching the next empty space in an array that stores the name of food within the diet structure
        diet_list[diet_list_size].calories_intake = calories_intake; // Save read calories_intake value to member of the diet structure
        diet_list_size++; // Increase diet_list_size 
    }
    fclose(file); // Close the file
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i; //To declare variable choice [if statement], i [for statement]
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    
    for (i = 0; i < diet_list_size; i++) {
        printf("%d. %s (%d kcal)\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake); // Outputs diet List (Number, Name, Calories) 
    }
    printf("0. Exit\n"); // Exit option 

	// ToCode: to enter the diet to be chosen with exit option (Press 0 to set it to exit.)
	printf("Choose a number for diet selection (Choose Number 0 to Exit): ");
	scanf("%d", &choice);
    
    if (choice==0) { // If the user wants to exit, she must press 0.
    	printf("Exit diet selection.\n"); 
    	return; // requiring termination of the function execution.
	}
	
    if (choice < 1 || choice > diet_list_size) { // If the user enters the wrong number, an error message is output.
        printf("[Error] Invalid option. \n");
        printf("Please try again! \n");
        return; // requiring termination of the function execution.
	}
	
    // ToCode: to enter the selected diet in the health data
    strcpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice - 1].food_name);
	// Copy the selected diet's name from diet_list to the next available slot in health_data->diet
	
    // Access the food_name of (the diet_count)th element in the diet array of health_data structure
    // Pointers approaching the next empty space in an array that stores the name of food within the HealthData structure
    
    // diet_list[choice-1].food_name: Diet's name that the user chose
    
    health_data->diet[health_data->diet_count].calories_intake = diet_list[choice - 1].calories_intake; 
	// Copy the selected diet's calories to last_diet.calories
    // health_data->diet[health_data->diet_count].calories_intake => structure pointer -> member(calories)
    // diet_list[choice-1].calories_intake: Diet's calories that the user chose
    
    health_data->diet_count++;
    // Increase the diet_count for saving a new diet record

	// ToCode: to enter the total calories intake in the health data
    health_data->total_calories_intake += diet_list[choice - 1].calories_intake;
    // total_calories_intake: Stores the total number of calories that the user has consumed so far within the structure
    // += operation: Updates by adding the calories from the selected diet to the total calories saved to date
    
	printf("You have chosen %s. Total calories intake is now %d kcal.\n",  diet_list[choice - 1].food_name, health_data->total_calories_intake);
    //Outputs the name of the diet that the user has selected and the total calories consumed so far.
}

