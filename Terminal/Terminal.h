#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#include "../Card/Card.h"
#include "../App/stdtypes.h"

typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
OK_Term, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;



           /* Function Prototypes for Terminal */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termdata);
EN_terminalError_t isCardExpried(ST_cardData_t *cardData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *Data);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termdata);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termdata);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termdata);

#endif // TERMINAL_H_INCLUDED

