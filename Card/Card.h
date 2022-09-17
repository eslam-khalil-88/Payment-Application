#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "..\App\stdtypes.h"

// Array holding the 3 info parts: name, PAN, Expiry date for 10 users
typedef struct ST_cardData_t{
  uint8_t clientName[25];
  uint8_t clientPAN [25];
  uint8_t expirydate[6];
}ST_cardData_t;


//Enumeration variable for state of each operation
typedef enum EN_cardError_t
{
OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


                    //Function Prototypes
EN_cardError_t getCardHolderName(ST_cardData_t *Data);
EN_cardError_t getCardExpiryDate(ST_cardData_t *Data);
EN_cardError_t getCardPAN (ST_cardData_t *Data);

#endif // CARD_H_INCLUDED
