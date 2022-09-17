# Payment-Application
Payment Application including a card component, server and terminal components for making transactions by a client.

### System Architecture
* System consists of 3 main modules: Card Module, Terminal Module and Server Module.
* Card module represents all methods and variables related to the card such as: Card Holder name, Card PAN number and card expiry date.
* Terminal module for the methods taking card data and processing it for making transaction: get transaction date, Checking validity of card, Checking card expiry date, specifying maximum amount of transaction and specifying the amount of transaction required by client.
* Server module responsible for checking the client's account on server database, check the availabilty of client's account, getting transaction information from terminal and saving the transaction process.

### Functions and variables used in the application
##### Card Module

* EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

* EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

* EN_cardError_t getCardPAN(ST_cardData_t *cardData);

##### Terminal Module

* EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

* EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

* EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);

* EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

* EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

* EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

##### Server Module

* EN_transState_t recieveTransactionData(ST_transaction_t *transData);

* EN_serverError_t isValidAccount(ST_cardData_t *cardData);

* EN_serverError_t isAmountAvailable(ST_trminalData_t *termData);

* EN_serverError_t saveTransaction(ST_transaction_t *transData);

* EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
