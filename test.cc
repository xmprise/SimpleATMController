#include <gtest/gtest.h>

#include "logic/bridge.h"
#include "logic/transaction.h"

TEST(AtmControllerTest, AtmWorkingDepositTest) {
  std::unique_ptr<bank::logic::transaction::Transaction> transaction =
      std::make_unique<bank::logic::transaction::Transaction>();
  bank::logic::bridge::CustomerInformation customer_1;
  bank::logic::bridge::Account account_1{};
  customer_1.card.card_number = 1111;
  customer_1.card.customer_number = 1;
  account_1.account_number = 111;
  account_1.amount = 1;
  customer_1.account.push_back(account_1);
  transaction->MakeDummyData(customer_1);

  ASSERT_EQ(2, transaction->testAction(customer_1.card, 1, 0, 1));
}

TEST(AtmControllerTest, AtmWorkingWithdrawTest) {
  std::unique_ptr<bank::logic::transaction::Transaction> transaction =
      std::make_unique<bank::logic::transaction::Transaction>();
  bank::logic::bridge::CustomerInformation customer_1;
  bank::logic::bridge::Account account_1{};
  customer_1.card.card_number = 1111;
  customer_1.card.customer_number = 1;
  account_1.account_number = 111;
  account_1.amount = 10;
  customer_1.account.push_back(account_1);
  transaction->MakeDummyData(customer_1);

  ASSERT_EQ(9, transaction->testAction(customer_1.card, 2, 0, 1));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}