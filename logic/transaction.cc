#include "transaction.h"

#include <iostream>

bank::logic::transaction::Transaction::Transaction() {
  data_accessor_ = std::make_unique<bank::logic::accessor::Accessor>();
  data_accessor_->SetAtmCash(9999);
}

void bank::logic::transaction::Transaction::AccessAccount(
    const bridge::Card &customer_card, const int &pin,
    const uint64_t &account_number, const int &action) {
  Card card{customer_card.customer_number, customer_card.card_number,
            customer_card.pin};
  int account_index;
  if (!ReadCard(card)) {
    std::cout << "Can not Read Card" << std::endl;
  } else if (!PinNumber(card, pin)) {
    std::cout << "Wrong Pin Number" << std::endl;
  } else if (!SelectAccount(card, account_number, &account_index)) {
    std::cout << "Can not select account" << std::endl;
  } else if (!Banking(card, action, account_index)) {
    std::cout << "Access denied" << std::endl;
  }
}

bool bank::logic::transaction::Transaction::ReadCard(const Card &card) {
  return data_accessor_->IsExistAccount(card.customer_number, card.card_number);
}

bool bank::logic::transaction::Transaction::PinNumber(const Card &card,
                                                      const int &pin) {
  return data_accessor_->GetValidPinNumber(card.customer_number,
                                           card.card_number, pin);
}

bool bank::logic::transaction::Transaction::SelectAccount(
    const Card &card, const uint64_t &account_number, int *account_index) {
  return data_accessor_->GetAccount(card.customer_number, card.card_number,
                                    account_number, account_index);
}

bool bank::logic::transaction::Transaction::Banking(const Card &card,
                                                    const int &action,
                                                    const int &account_index) {
  bool result = false;
  uint64_t amount;
  uint64_t account_amount;
  switch (action) {
  case Balance:
    amount = data_accessor_->GetBalance(card.customer_number, card.card_number,
                                        account_index);
    std::cout << "Amount of cash in your account : " << amount << std::endl;
    result = true;
    break;
  case Deposit:
    std::cout << "Enter amount of deposit : ";
    std::cin >> amount;
    if (data_accessor_->SetDeposit(card.customer_number, card.card_number,
                                   amount, account_index, &account_amount)) {
      std::cout << "Succeed your request : " << amount << std::endl;
      std::cout << "Account amount : " << account_amount << std::endl;
      result = true;
    } else {
      std::cout << "Invalid your request" << std::endl;
    }
    break;
  case Withdraw:
    std::cout << "Enter amount of withdraw : ";
    std::cin >> amount;
    if (data_accessor_->SetWithdraw(card.card_number, card.card_number, amount,
                                    account_index, &account_amount)) {
      std::cout << "Succeed your request : " << amount << std::endl;
      std::cout << "Account amount : " << account_amount << std::endl;
      result = true;
    } else {
      std::cout << "Invalid your request" << std::endl;
    }
    break;
  default:
    break;
  }

  return result;
}

void bank::logic::transaction::Transaction::MakeDummyData(
    const bank::logic::bridge::CustomerInformation &customer) {
  data_accessor_->SetDummyData(customer);
}

uint64_t bank::logic::transaction::Transaction::testAction(
    const bank::logic::bridge::Card &card, const int &action,
    const int &account_index, const uint64_t &money) {
  uint64_t result{};
  switch (action) {
  case Balance:
    data_accessor_->GetBalance(card.customer_number, card.card_number,
                               account_index);
    break;
  case Deposit:
    data_accessor_->SetDeposit(card.customer_number, card.card_number, money,
                               account_index, &result);
    break;
  case Withdraw:
    data_accessor_->SetWithdraw(card.card_number, card.card_number, money,
                                account_index, &result);
    break;
  default:
    break;
  }

  return result;
}
