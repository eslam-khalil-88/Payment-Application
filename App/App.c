#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"
#include "../Server/Server.h"
#include "App.h"


#define SUCCESS 0
#define FAIL 1

/************************************************************************/
/* Application code should do the following */
/* 1- Take the code from user and find his name, PAN and Expiry date */
/* 2- Send these data to Card, which saves it in their corresponding variables */
/* 3- Terminal should retrieve data of card, and check the validity of card (ex. Expiry) */
/* 4- If card is valid , check the transaction amount required if it's less than or equal the balance */
    // If not, just print a message "Declined for passing the limit !", and exit
/*5- If not, Terminal should connect to Server */
/* 6- Server corresponding function should check if the account is valid or not */
/* 7- If the amount is valid, then reduce the balance, and print a new message for "Successful transaction" */
/*************************************************************************/



/***************************************************************/
                  /* Main Processing Functions */
/***************************************************************/

    extern ST_cardData_t *cardData ;
    extern ST_terminalData_t *TerminalData;
    extern ST_transaction *Trans_Data;
    extern ST_cardData_t *InputcardData ;


void appStart(void){
    int state;
    char *TODAY = "22-09-2022";// Date of the day

    //Allocating memory space for Card Data, Terminal Data & Server data
    InputcardData = (ST_cardData_t *) malloc(sizeof(ST_cardData_t) * 1);
    ST_terminalData_t *Temp_TerminalInput = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t) * 1);//Temporary Terminal data to be validated
    cardData = (ST_cardData_t*) malloc(sizeof(ST_cardData_t) * 1);
    TerminalData = (ST_terminalData_t *) malloc(sizeof(ST_terminalData_t) * 1);
    Trans_Data = (ST_transaction*) malloc(sizeof(ST_transaction) * 1);

  /************************************ Main Application ******************************************************************/
   printf("Starting Application\n");

                          /********************** Card Stage ****************************/
  //First, give the cardholder name, PAN and expiry date using getCardHoldername() , ....

  state = getCardHolderName(InputcardData);//Get Card Name Holder
  if(state != SUCCESS){
    return;
  }

  state = getCardPAN (InputcardData); //Get card PAN number of Primary Account Number
  if(state != SUCCESS){
    return;
  }

  state = getCardExpiryDate(InputcardData);// Get the expiry date of the card
  if(state != SUCCESS){
    return;
    }
    //Showing client information including: Name and Primary Account Number.
  printf("Card name: %s , card PAN: %s and Expiry date is: %s\n" , cardData -> clientName , cardData -> clientPAN , cardData -> expirydate);


                    /****************************** Terminal Stage *****************************/
  //Next, Terminal should ask and check for transaction date, Card expiry date, Transaction Amount
  strcpy(Temp_TerminalInput -> transactionDate , TODAY);

  state = getTransactionDate(Temp_TerminalInput);// Get the date of transaction (ex. Today)
  if(state != SUCCESS){
    return;
    }

   state = isCardExpried(cardData);// Check if the card if valid or expired
   if(state != SUCCESS){
       return;
    }
   state = isValidCardPAN(cardData);// Check the Card PAN, either it's valid or not
   if(state != SUCCESS){
       return;
     }
   //Ask the user for the transaction amount
   printf("Please enter the transaction amount: ");
   scanf("%f" , &Temp_TerminalInput -> transAmount);
   state = getTransactionAmount(Temp_TerminalInput);
   if(state != SUCCESS){
    return;
    }

   //Set the maximum amount of transaction at: 200,000
   state = setMaxAmount(Temp_TerminalInput);
   if(state != SUCCESS){
      return;
      }



    //Checking if the amount of transaction doesn't exceed the maximum amount of withdraw
    state = isBelowMaxAmount(Temp_TerminalInput);
    if(state != SUCCESS){
      return;
      }


              /********************* Server Stage ********************************/

     //Transferring data of the client to the server
     printf("\nChecking Data on server ... \n\n");
    strcpy(Trans_Data -> cardHolderData.clientName , cardData -> clientName);
    strcpy(Trans_Data -> cardHolderData.clientPAN , cardData -> clientPAN);
    Trans_Data -> terminalData.transAmount = TerminalData -> transAmount;
    Trans_Data -> terminalData.maxTransAmount = TerminalData -> maxTransAmount;
    strcpy(Trans_Data -> terminalData.transactionDate , TerminalData -> transactionDate);
    Trans_Data -> transactionSequenceNumber = 0;

    //Check if the account is valid via the server

    state = recieveTransactionData(Trans_Data);
    if(state != SUCCESS){
        return;
    }



  }

