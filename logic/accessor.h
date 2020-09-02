#ifndef SIMPLE_ATM_CONTROLLER_ACCESSOR_H_
#define SIMPLE_ATM_CONTROLLER_ACCESSOR_H_

#include <unordered_map>

#include "bridge.h"

namespace bank {
namespace logic {
namespace accessor {

struct DummyCard {
  int card_number;
  int pin;
};

struct DummyAccount {
  uint64_t account_number;
  uint64_t amount;
};

struct DummyCustomerInformation {
  std::string name;
  DummyCard card;
  std::vector<DummyAccount> account;
};

class Accessor {
public:
  explicit Accessor();
  bool IsExistAccount(const int &customer_number, const int &card_number);
  bool GetValidPinNumber(const int &customer_number, const int &card_number,
                         const int &pin);
  bool GetAccount(const int &customer_number, const int &card_number,
                  const uint64_t &account_number, int *account_index);
  uint64_t GetBalance(const int &customer_number, const int &card_number,
                      const int &account_index);
  bool SetDeposit(const int &customer_number, const int &card_number,
                  const uint64_t &request_amount, const int &account_index,
                  uint64_t *account_amount);
  bool SetWithdraw(const int &customer_number, const int &card_number,
                   const uint64_t &request_amount, const int &account_index,
                   uint64_t *account_amount);
  void SetDummyData(const bridge::CustomerInformation &account_information);
  void SetAtmCash(const uint64_t &atm_cash);

private:
  void SearchCardNumber(
      const int &customer_number, const int &card_number,
      std::unordered_map<int, DummyCustomerInformation>::iterator *iter);
  bool SearchAccount(
      const uint64_t &account_number,
      std::unordered_map<int, DummyCustomerInformation>::iterator *iter,
      int *index);
  bool ValidAccountNumber(const int &account_number);
  std::unordered_map<int, DummyCustomerInformation> dummy_dataset_;
  uint64_t atm_cash_;
};

} // namespace accessor
} // namespace logic
} // namespace bank
#endif // SIMPLE_ATM_CONTROLLER_ACCESSOR_H_
