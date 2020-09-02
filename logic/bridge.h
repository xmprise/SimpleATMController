#ifndef SIMPLE_ATM_CONTROLLER_BRIDGE_H_
#define SIMPLE_ATM_CONTROLLER_BRIDGE_H_

#include <cstdint>
#include <string>
#include <vector>

namespace bank {
namespace logic {
namespace bridge {

struct Card {
  int customer_number;
  int card_number;
  int pin;
};

struct Account {
  uint64_t account_number;
  uint64_t amount;
};

struct CustomerInformation {
  std::string name;
  Card card;
  std::vector<Account> account;
};

} // namespace bridge
} // namespace logic
} // namespace bank
#endif // SIMPLE_ATM_CONTROLLER_BRIDGE_H_
