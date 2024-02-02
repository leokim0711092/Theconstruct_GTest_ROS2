#include "library_header.h"
#include "gtest/gtest.h"

TEST(SavingsAccount, TestDeposit) {
  // create an instance
  SavingsAccount my_account("Holiday savings account", 0);
  my_account.deposit(100);
  EXPECT_EQ(100, my_account.get_balance());
}

TEST(SavingsAccount, TestDepositAndWithdraw) {
  // create an instance
  SavingsAccount my_account("Holiday savings account", 555);
  bool deposit_result = my_account.deposit(100.10);
  EXPECT_TRUE(deposit_result);
  ASSERT_FLOAT_EQ(100.10, my_account.get_balance());
  my_account.withdraw(50.0);
  ASSERT_FLOAT_EQ(50.1, my_account.get_balance());
}

TEST(SavingsAccount, TestExcessWithdraw) {
  // create an instance
  SavingsAccount my_account("Holiday savings account", 555);
  bool deposit_result = my_account.deposit(100.00);

  EXPECT_TRUE(deposit_result);
  ASSERT_FLOAT_EQ(100.00, my_account.get_balance());

  bool withdraw_result = my_account.withdraw(500.0);
  EXPECT_FALSE(withdraw_result);
  ASSERT_FLOAT_EQ(100.00, my_account.get_balance());
}

TEST(SavingsAccount, TestGetName) {
  // create an instance
  SavingsAccount my_account("Holiday savings account", 555);
  std::string name = my_account.get_name();
  EXPECT_EQ("Holiday savings account", name);
}