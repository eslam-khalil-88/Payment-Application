#include "Card.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
                  /* Card code should do the following */
/* 1- Take the code from user and find his name, PAN and Expiry date */
/* 2- Save these data in struct Client data members */
/* 3- Terminal could get these data using getCardHoldername(), ... etc. */
/*************************************************************************/

ST_cardData_t cards[10] = {{"Eslam Ibrahim Khalil" , "1534-2203-8910-9881" , "12/24"} ,
                           {"Ahmed Ibrahim Mohamed" , "2551-3399-2010-5693" , "07/21"} ,
                           {"Mohamed Elsayed Abdo" , "5648-2568-1369-2217" , "08/22"} ,
                           {"Mostafa Hegy Soliman" , "8463-2579-2367-1211" , "11/22"} ,
                           {"Hussein Elsayed Elmasry" , "5531-5033-8412-7193" , "03/20"} ,
                           {"Mohamed Elaziz Noaman" , "3497-2573-7314-1006" , "11/21"} ,
                           {"Hazem Hussein Gharieb" , "9773-2116-5666-4312" , "09/22"} ,
                           {"Diaa Eldin Aly Darwish" , "7449-4474-5791-2214" , "12/23"} ,
                           {"Alaa Metwally Elsayed" , "1635-3098-9847-9375" , "01/24"} ,
                           {"Abdallah Osman Fathy" , "6179-9813-8532-5843" , "04/21"}
 };


ST_cardData_t *cardData ;// Holds correct data after checkings
ST_cardData_t *InputcardData ;//Temporary card date to be checked






/****************************************************************/
  /* Retrieve the Card Holder Name, Expiry Data and Card PAN */
/****************************************************************/

/* Checking and saving card holder name */
EN_cardError_t getCardHolderName(ST_cardData_t *Data){
    char name [25] = {0};
    printf("Enter your name: ");
    //getchar();//skip last newline character
    //fgets(name , 25 , stdin);
    _flushall();
    scanf("%[^\n]",name);

       //Check if input name satisfies conditions
       if(strlen(name) < 20 || strlen(name) > 24 || name == '\0'){
        printf("Wrong Name !\n");
        return WRONG_NAME;//Failed due to wrong name or NULL
    }
    else{
        strcpy(cardData -> clientName , name);
    }

   return OK;
   }

/* Checking and saving expiry date of input card */
EN_cardError_t getCardExpiryDate(ST_cardData_t *Data){
    char date [6] = {0};
    printf("\nEnter expiry date: ");
    //getchar();//skip last newline character
    //fgets(date , 6 , stdin);
    _flushall();
    scanf("%[^\n]",date);

    //Check if expiry date input satisfies conditions
    if(strlen(date) > 5 || strlen(date) < 5 || date == '\0'){
        printf("Wrong form of expiry date !\n");
        return WRONG_EXP_DATE;// Failed as a result of expired card
    }
    else{
        strcpy(cardData -> expirydate , date);
    }
    return OK;
     }

/* Checking and saving PAN number of the input card */
EN_cardError_t getCardPAN (ST_cardData_t *Data){
    char PAN [25] = {0};
    printf("\nEnter your PAN number: ");
    //getchar();//skip last newline character
    //fgets(PAN , 25 , stdin);
    _flushall();
    scanf("%[^\n]",PAN);

    //Check if input PAN satisfies the conditions
    if(strlen(PAN) > 19 || strlen(PAN) < 16 || PAN == '\0'){
        printf("Wrong form of PAN number !\n");
        return WRONG_PAN;// Failed as a result of incorrect PAN form
    }
    else{
        strcpy(cardData -> clientPAN , PAN);
    }
    return OK;
     }
