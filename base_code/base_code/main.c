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
    loadDiets(DIETFILEPATH);
    loadExercises(EXERCISEFILEPATH);

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            case 1:
            	inputExercise(&health_data); 
            	//Prompt the user to select an exercise, record the duration, and update health_data accordingly.
            	saveData(HEALTHFILEPATH, &health_data);
            	//Save the updated health data to the text file
                break;
                
            case 2:
            	inputDiet(&health_data);
            	//Prompt the user to select a diet and update health_data with the selected diet details.
            	saveData(HEALTHFILEPATH, &health_data);
            	//Save the updated health data to the text file
                break;
                
            case 3:
            	printHealthData(&health_data);
            	//Outputs the current health data, including exercise, diet, and total calorie information.
                break;
                
            case 4:
            	saveData(HEALTHFILEPATH, &health_data);
            	//Save the final health data to the text file
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
                
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
        if (health_data.total_calories_intake - 1300 - health_data.total_calories_burned == 0){
            printf("You have consumed all your calories for today! \n");
            break; //Exit the loop if the calorie goal is achieved
		} 
    } while (choice!=4); //if user chose number 1,2,3, then a repeat statement is executed

    return 0;
}

