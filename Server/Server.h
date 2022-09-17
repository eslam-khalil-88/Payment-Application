#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED


#include "../Terminal/Terminal.h"
#include "../App/stdtypes.h"

typedef enum EN_transState_t
{
APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
OK_Serv, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t ;


// Database of transactions
typedef struct ST_transaction_t
{
   ST_cardData_t cardHolderData;
   ST_terminalData_t terminalData;
   EN_transStat_t transState;
   uint32_t transactionSequenceNumber;
}ST_transaction;

//Database of accounts and balance
typedef struct ST_accountsDB_t
{
float balance;
uint8_t primaryAccountNumber[20];
uint8_t Block_state;
}ST_accountsDB_t;





// Function Prototypes
EN_transStat_t recieveTransactionData(ST_transaction *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction *transData);

#endif // SERVER_H_INCLUDED
