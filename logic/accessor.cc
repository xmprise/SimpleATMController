#include "accessor.h"

#include <algorithm>

bank::logic::accessor::Accessor::Accessor() : atm_cash_{0} {}

void bank::logic::accessor::Accessor::SetAtmCash(const uint64_t &atm_cash) {
  atm_cash_ = atm_cash;
}

bool bank::logic::accessor::Accessor::IsExistAccount(const int &customer_number,
                                                     const int &card_number) {
  std::unordered_map<int, DummyCustomerInformation>::iterator iter;
  SearchCardNumber(customer_number, card_number, &iter);

  return iter != dummy_dataset_.end();
}

bool bank::logic::accessor::Accessor::GetValidPinNumber(
    const int &customer_number, const int &card_number, const int &pin) {
  std::unordered_map<int, DummyCustomerInformation>::iterator iter;
  SearchCardNumber(customer_number, card_number, &iter);

  return (*iter).second.card.pin == pin;
}

bool bank::logic::accessor::Accessor::GetAccount(const int &customer_number,
                                                 const int &card_number,
                                                 const uint64_t &account_number,
                                                 int *account_index) {
  if (!ValidAccountNumber(account_number))
    return false;
  bool result = false;
  std::unordered_map<int, DummyCustomerInformation>::iterator iter;
  SearchCardNumber(customer_number, card_number, &iter);

  return SearchAccount(account_number, &iter, account_index);
}

uint64_t bank::logic::accessor::Accessor::GetBalance(const int &customer_number,
                                                     const int &card_number,
                                                     const int &account_index) {
  std::unordered_map<int, DummyCustomerInformation>::iterator iter;
  SearchCardNumber(customer_number, card_number, &iter);

  return (*iter).second.account[account_index].amount;
}

bool bank::logic::accessor::Accessor::SetDeposit(const int &customer_number,
                                                 const int &card_number,
                                                 const uint64_t &request_amount,
                                                 const int &account_index,
                                                 uint64_t *account_amount) {
  bool result = true;
  if (request_amount > 0 && request_amount < INT64_MAX) {
    std::unordered_map<int, DummyCustomerInformation>::iterator iter;
    SearchCardNumber(customer_number, card_number, &iter);
    (*iter).second.account[account_index].amount + request_amount < INT64_MAX
        ? (*iter).second.account[account_index].amount += request_amount
        : result = false;
    *account_amount = (*iter).second.account[account_index].amount;
  } else {
    result = false;
  }

  return result;
}

bool bank::logic::accessor::Accessor::SetWithdraw(
    const int &customer_number, const int &card_number,
    const uint64_t &request_amount, const int &account_index,
    uint64_t *account_amount) {
  bool result = false;
  if (request_amount > 0 && request_amount < atm_cash_) {
    std::unordered_map<int, DummyCustomerInformation>::iterator iter;
    SearchCardNumber(customer_number, card_number, &iter);
    if ((*iter).second.account[account_index].amount > request_amount) {
      (*iter).second.account[account_index].amount -= request_amount;
      atm_cash_ -= request_amount;
      result = true;
    }
    *account_amount = (*iter).second.account[account_index].amount;
  }

  return result;
}

void bank::logic::accessor::Accessor::SetDummyData(
    const bridge::CustomerInformation &account_information) {
  DummyCustomerInformation dummy_customer;
  dummy_customer.name = account_information.name;
  dummy_customer.card.card_number = account_information.card.card_number;
  dummy_customer.card.pin = account_information.card.pin;
  dummy_customer.account.resize(account_information.account.size());
  for (size_t i = 0; i < dummy_customer.account.size(); i++) {
    dummy_customer.account[i].amount = account_information.account[i].amount;
    dummy_customer.account[i].account_number =
        account_information.account[i].account_number;
  }
  dummy_dataset_[account_information.card.customer_number] = dummy_customer;
}

bool bank::logic::accessor::Accessor::ValidAccountNumber(
    const int &account_number) {
  return account_number > 0;
}

void bank::logic::accessor::Accessor::SearchCardNumber(
    const int &customer_number, const int &card_number,
    std::unordered_map<int, DummyCustomerInformation>::iterator *iter) {
  DummyCustomerInformation dummy;
  dummy.card.card_number = card_number;
  *iter = std::find_if(
      dummy_dataset_.begin(), dummy_dataset_.end(),
      [&](const std::unordered_map<int, DummyCustomerInformation>::value_type
              &dummy_data) {
        return dummy_data.second.card.card_number == dummy.card.card_number;
      });
}

bool bank::logic::accessor::Accessor::SearchAccount(
    const uint64_t &account_number,
    std::unordered_map<int, DummyCustomerInformation>::iterator *iter,
    int *index) {
  bool result = false;
  int index_count = 0;
  for (auto account : (*iter)->second.account) {
    if (account_number == account.account_number) {
      result = true;
      break;
    }
    ++index_count;
  }
  *index = index_count;

  return result;
}
