#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Terminal.h"
/************************************************************************/
               /* Terminal code should do the following */
/* 1- Take the Card information using getCardHoldername(), ... etc. */
/* 2- Get Transaction date (today), and save it */
/* 3- Check if the card is expired or not */
/* 4- If not, get the transaction amount (amount to be withdrawn) */
/* 5- Check if the amount exceeds the actual balance or not */
/* 6- If not, transfer control to the server, for further check */
/*************************************************************************/


uint8_t *Date_Today = "22-09-2022";


ST_terminalData_t *TerminalData; //Holds the data of the terminal


/**********************************************************************/
/* Find/Get the transaction date and store it in terminal data */
/**********************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termdata){
    uint8_t *new_date = (uint8_t*) malloc(sizeof(uint8_t) * 11);

    printf("Please enter the date of transaction in the form DD/MM/YYYY: ");
    getchar();
    fgets(new_date , 11 , stdin);
      if(strlen(new_date) != 10 || new_date == NULL || new_date[2] != '/' || new_date[5] != '/'){
        printf("Wrong Date format !\n");
        return WRONG_DATE; //Wrong date
    }

    else{
       strcpy(TerminalData -> transactionDate , new_date);
    }

   return OK_Term;//Success
  }

/************************************************************************/
            /* Check if the card is expired or not */
/************************************************************************/
EN_terminalError_t isCardExpried(ST_cardData_t *cardData){
  int Expiry_Month , Expiry_Year;// input expiry date to be checked
  char *date = TerminalData -> transactionDate;
  int year = (date[8] - '0') * 10 + (date[9] - '0') + 2000;
  int month = (date[3] - '0') * 10 + (date[4] - '0');

  uint8_t *expirydate = cardData -> expirydate;
  Expiry_Year = (expirydate[3] - '0') * 10 + (expirydate[4] - '0') + 2000;//Convert string year to number/integer form
  Expiry_Month = (expirydate[0] - '0') * 10 + (expirydate[1] - '0');//Convert string month to number/integer form

  if(Expiry_Year > year || (Expiry_Year == year && Expiry_Month >= month)){
      //The card is not expired, and it's OK
     }

   else{
     printf("Sorry card is expired !!\n");
     return EXPIRED_CARD;
   }

        printf("Checking Card .... Card is OK\n");
        return OK_Term; //Card is valid and not expired
   }



/*************************************************************************************/
      /* Setting and getting of the transaction amount required */
/*************************************************************************************/

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termdata){
    if(termdata -> transAmount <= 0){
        printf("Invalid Amount !\n");
        return INVALID_AMOUNT;
    }
    else{
       TerminalData -> transAmount = termdata -> transAmount;
    }
    printf("Amount is OK \n");
  return OK_Term;
  }



/*****************************************************************************************/
    /* Specify the maximum amount of transaction in a day for this terminal */
/*****************************************************************************************/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termdata){
    float maximum_Amount = 200000.1;
    if(maximum_Amount <= 0.0){
        printf("Invalid maximum Amount input !\n");
        return INVALID_MAX_AMOUNT;
    }
    else{
        TerminalData -> maxTransAmount = maximum_Amount;
        termdata -> maxTransAmount = maximum_Amount;
        printf("Maximum Amount has been specified as: %f\n" , maximum_Amount);
    }
   return OK_Term;
   }


  /* Check if required amount is beyond the transaction limit of the ATM (not balance) */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termdata){
    printf("\nTransaction amount: %f and maximum amount or limit: %f\n" , termdata -> transAmount , termdata -> maxTransAmount);
   if(termdata -> transAmount > termdata -> maxTransAmount){

    printf("Amount exceeds the maximum limit !\n");
    return EXCEED_MAX_AMOUNT; //Amount exceeded, Error in process
   }

   printf("Amount satisfies maximum Transaction\n");
   return OK_Term; //Amount satisfies maximumTransaction
  }

/* Function to check if the card PAN is valid or not */
EN_terminalError_t isValidCardPAN(ST_cardData_t *Data){
   if(strlen(Data -> clientPAN) > 19 || strlen(Data -> clientPAN) < 16 || Data -> clientPAN == '\0'){
        printf("Card PAN is not valid !\n");
        return INVALID_CARD;// Failed as a result of incorrect PAN form
      }
    else{
      }

      return OK_Term;
   }
