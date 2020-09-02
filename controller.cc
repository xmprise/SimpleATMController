#include <iostream>

#include "logic/bridge.h"
#include "logic/transaction.h"

typedef enum { Balance = 0, Deposit = 1, Withdraw = 2 } AtmAction;

int main() {
  std::cout << "Run ATM!!!" << std::endl;
  std::unique_ptr<bank::logic::transaction::Transaction> transaction =
      std::make_unique<bank::logic::transaction::Transaction>();

  // make dummy data
  bank::logic::bridge::CustomerInformation customer_1;
  bank::logic::bridge::Account account_1{};
  customer_1.name = "John";
  customer_1.card.card_number = 1111;
  customer_1.card.customer_number = 1;
  customer_1.card.pin = 1234;
  account_1.account_number = 111;
  account_1.amount = 12345;
  customer_1.account.push_back(account_1);
  transaction->MakeDummyData(customer_1);

  bank::logic::bridge::CustomerInformation customer_2;
  bank::logic::bridge::Account account_2{};
  customer_2.name = "Mark";
  customer_2.card.card_number = 1112;
  customer_2.card.customer_number = 2;
  customer_2.card.pin = 1230;
  account_2.account_number = 1112;
  account_2.amount = 142;
  customer_2.account.push_back(account_2);
  transaction->MakeDummyData(customer_2);

  // Run Atm (card, pin, account_number, action)
  // transaction->AccessAccount(customer_1.card, 1234, 111, Deposit);
  transaction->AccessAccount(customer_2.card, 1230, 1112, Withdraw);

  return 0;
}
