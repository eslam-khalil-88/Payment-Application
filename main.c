#include <stdio.h>
#include <stdlib.h>
#include "../App/App.h"


int main()
{
    int selection , state = 0;


    while(1){
        printf("\n");
        printf("***********************************************");
        printf("\n\tWelcome to the Payment Application\n");
        printf("***********************************************");
        printf("\nPlease Select a choice by writing the number\n");
        printf("1- Make A Transaction\n");
        printf("2- Exit Application\n");
        printf("Please enter your selection: ");
        scanf("%d",&selection);


          /* Main Application */
         if(selection == 1){
            /*******************************/
                 //Start application
            /*******************************/
            appStart();

            break;
             }

         else if(selection == 2){
            printf("\nThanks for using our services, Exitting !!");
            printf("***************************************\n");
            break;
             }
         else{
            printf("\nSorry wrong selection, Please enter a valid selection !");
            continue;
            }
    }

    return 0;
}
