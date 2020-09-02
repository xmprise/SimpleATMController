#ifndef SIMPLE_ATM_CONTROLLER_TRANSACTION_H_
#define SIMPLE_ATM_CONTROLLER_TRANSACTION_H_

#include <memory>

#include "accessor.h"
#include "bridge.h"

namespace bank {
namespace logic {
namespace transaction {

typedef enum { Balance = 0, Deposit = 1, Withdraw = 2 } AtmAction;

struct Card {
  int customer_number;
  int card_number;
  int pin;
};

class Transaction {
public:
  explicit Transaction();
  void AccessAccount(const bridge::Card &customer_card, const int &pin,
                     const uint64_t &account_number, const int &action);
  void MakeDummyData(const bridge::CustomerInformation &customer);

  uint64_t testAction(const bank::logic::bridge::Card &card, const int &action,
                      const int &account_index, const uint64_t &money);

private:
  bool ReadCard(const Card &card);
  bool PinNumber(const Card &card, const int &pin);
  bool SelectAccount(const Card &card, const uint64_t &account_number,
                     int *account_index);
  bool Banking(const Card &card, const int &action, const int &account_index);
  std::unique_ptr<bank::logic::accessor::Accessor> data_accessor_;
};

} // namespace transaction
} // namespace logic
} // namespace bank

#endif // SIMPLE_ATM_CONTROLLER_TRANSACTION_H_
