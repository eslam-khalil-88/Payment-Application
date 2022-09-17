#include "Server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SUCCESS 0
#define FAIL 1


/************************************************************************/
                /* Server code should do the following */
/* 1- Check if the account is valid, using info from Card or Terminal */
/* 2-  If valid, check if the required amount is more than or equal to the balance */
/* 3-  If it's sufficient, change the balance amount in database, then print the transaction*/
/*************************************************************************/

//Transactions Server Database
ST_transaction trans_database[10] = {
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0} ,
           {{0 , 0 , 0} , {0.0 , 0.0 , 0} , 0 , 0}
                      };

// Accounts Database including: {"Balance of client" , "PAN of client card"}
ST_accountsDB_t database[10] = {
                    {120224.0, "1534-2203-8910-9881" , 0} ,
                    {220195.6, "2551-3399-2010-5693" , 0} ,
                    {50000.4, "5648-2568-1369-2217" , 0} ,
                    {400900.76, "8463-2579-2367-1211" , 0} ,
                    {746893.9, "5531-5033-8412-7193" , 0} ,
                    {150000.2, "3497-2573-7314-1006" , 0} ,
                    {605000.33, "9773-2116-5666-4312" , 0} ,
                    {95000.63, "7449-4474-5791-2214" , 0} ,
                    {30000.59, "2201-1585-9847-9375" , 0} ,
                    {850120.1, "6179-9813-8532-5843" , 0}
                     };

int client_indx;// Variable to get the index of the client in the server database
ST_transaction *Trans_Data;// For saving the transaction data at server side
extern ST_cardData_t *cardData ;// Import Card data from Card file
extern ST_terminalData_t *TerminalData;// Import terminal data




/*****************************************************************************/
/* Function for checking existence of the account and amount of transaction */
/*****************************************************************************/
EN_transStat_t recieveTransactionData(ST_transaction *transData){
    int chk_state , choice; //Variable used to check the state of each function whether it passes or not

  for(int indx = 0; indx < 10 ; indx++){
    if(strcmp(database[indx].primaryAccountNumber , transData -> cardHolderData.clientPAN) == 0){
        //Check for transaction amount
        printf("amount in database: %f and amount required is: %f\n" , database[indx].balance , transData -> terminalData.transAmount);

          if(database[indx].balance >= transData -> terminalData.transAmount){
            Trans_Data -> transState = APPROVED;
            client_indx = indx;

            /* Check if the account is blocked by client, and if not ask him whether to block it or not*/
            if(database[indx].Block_state != 0){
                printf("Account is blocked by Client !\n");
                return;
            }
            printf("Would you like to block your account ? For Yes enter 1, For NO enter 0: ");
            scanf("%d" , &choice);
            if(choice == 1){
                printf("\n Account is blocked, thanks !");
                database[indx].Block_state++;
                return;
            }

            /* Taking next steps to make the transaction
            */
            printf("Approved\n");
            chk_state = isValidAccount(cardData);
            if(chk_state != SUCCESS){
                return;
            }
            chk_state = isAmountAvailable(TerminalData);
            if(chk_state != SUCCESS){
                return;
            }
            chk_state = getTransaction(Trans_Data -> transactionSequenceNumber, Trans_Data);
            if(chk_state != SUCCESS){
                return;
            }

            chk_state = saveTransaction(Trans_Data);
            if(chk_state != SUCCESS){
                return;
            }



            return APPROVED;
          }
          else{
              printf("Declined for insufficient Fund\n");
            return DECLINED_INSUFFECIENT_FUND;
              }
         }
       }
       printf("Declined Stolen Card receive!!!\n");
       return DECLINED_STOLEN_CARD;
   }

/******************************************************************/
       /* Check if the account is valid or stolen */
/******************************************************************/
EN_serverError_t isValidAccount(ST_cardData_t *cardData){
  uint8_t *PAN_number = cardData -> clientPAN;
  for(int indx = 0; indx < 10 ; indx++){
    if(strcmp(database[indx].primaryAccountNumber , PAN_number) == 0){

        printf("Account is Valid\n");
        return OK_Serv; //Account is valid
                }
       }
       printf("Declined Stolen Card isValid **\n");
       return ACCOUNT_NOT_FOUND;
  }


/******************************************************************/
  /* Checking if the amount of balance is sufficient to withdraw */
/******************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    //Compare the transaction amount with the client's balance in database, whether it's sufficient or not
   if(termData -> transAmount > database[client_indx].balance){
      printf("Client's Balance is: %f\n" , database[client_indx].balance);
      printf("Low Balance for transaction\n");
      return LOW_BALANCE;
       }
    printf("Client's Balance is: %f\n" , database[client_indx].balance);
    printf("Amount is OK\n");
    return OK_Serv;
  }

/******************************************************************/
      /* Saving transaction and updating the balance */
/******************************************************************/
EN_serverError_t saveTransaction(ST_transaction *transData){

  float transaction_amount = transData -> terminalData.transAmount;
  database[client_indx].balance -= transaction_amount;
     if(database[client_indx].balance < 0.0){
        printf("Saving transaction Failed\n");
        return SAVING_FAILED;
     }
     printf("******* Balance is updated, Thanks for using our services ********\n");
     return OK_Serv;

  }

/********************************************************************************/
   /* Updating number of transactions in case it satisfies the maximum limit */
/********************************************************************************/

EN_serverError_t getTransaction(unsigned long transactionSequenceNumber, ST_transaction *transData){
    printf("\nTransactions number is: %lu\n" , trans_database[client_indx].transactionSequenceNumber);

  if(trans_database[client_indx].transactionSequenceNumber < 8){//Maximum allowable transactions per day
     trans_database[client_indx].transactionSequenceNumber++;
     Trans_Data -> transactionSequenceNumber = trans_database[client_indx].transactionSequenceNumber;
     printf("Transactions updated !\n");
     return OK_Serv;
      }
      printf("Transaction not found\n");
      return TRANSACTION_NOT_FOUND;
  }

