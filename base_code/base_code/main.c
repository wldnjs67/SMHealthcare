//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};

    // Tocode: to read the list of the exercises and diets
    loadDiets(DIETFILEPATH); // Read and save 'diets.txt' file
    loadExercises(EXERCISEFILEPATH); // Read and save 'exercises.txt' file

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n"); // Exercise selection
        	printf("2. Diet \n"); // Diet selection
        	printf("3. Show logged information \n"); // Check the accumulated information about exercises and diets
        	printf("4. Exit \n"); // exit the program
        	printf("Select the desired number: "); // User's choice
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) { // Cases that depend on the number entered by the user
            case 1: // If the user chose number 1 (Exercise)
            	inputExercise(&health_data); 
            	//Prompt the user to select an exercise, record the duration, and update health_data accordingly.
            	saveData(HEALTHFILEPATH, &health_data);
            	//Save the updated health data to the text file
                break; // Exit the loop
                
            case 2: // If the user chose number 2 (Diet)
            	inputDiet(&health_data);
            	//Prompt the user to select a diet and update health_data with the selected diet details.
            	saveData(HEALTHFILEPATH, &health_data);
            	//Save the updated health data to the text file
                break; // Exit the loop
                
            case 3: // If the user chose number 3 (Show logged information)
            	printHealthData(&health_data);
            	//Outputs the current health data, including exercise, diet, and total calorie information.
                break; // Exit the loop
                
            case 4: // If the user chose number 4 (Exit)
            	saveData(HEALTHFILEPATH, &health_data);
            	//Save the final health data to the text file
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break; // Exit the loop
                
            default: //if the user entered wrong number (Except 1~4), an ERROR message is output.
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n"); 
        }
        
        if (health_data.total_calories_intake - BASAL_METABOLIC_RATE - health_data.total_calories_burned == 0)
		{
            printf("You have consumed all your calories for today! \n");
            break; // Exit the loop if the calorie goal is achieved. The program will be terminated.
		} 
		
    } while (choice!=4); // If the user chose number 1 or 2 or 3, then a repeat statement is executed. 
    //If the user chose number 4, The program will be terminated immediately. (without running a repeat statement)

    return 0;
}

