/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <memory>

#include "base/test/task_environment.h"
#include "bat/ledger/internal/promotion/promotion.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "bat/ledger/internal/ledger_client_mock.h"
#include "bat/ledger/internal/ledger_impl_mock.h"

// npm run test -- brave_unit_tests --filter=PromotionTest.*

using ::testing::_;

namespace braveledger_promotion {

class PromotionTest : public testing::Test {
 private:
  base::test::TaskEnvironment scoped_task_environment_;
 protected:
  std::unique_ptr<ledger::MockLedgerClient> mock_ledger_client_;
  std::unique_ptr<bat_ledger::MockLedgerImpl> mock_ledger_impl_;
  std::unique_ptr<Promotion> promotion_;

  PromotionTest() {
      mock_ledger_client_ = std::make_unique<ledger::MockLedgerClient>();
      mock_ledger_impl_ = std::make_unique<bat_ledger::MockLedgerImpl>
          (mock_ledger_client_.get());
  }

  void SetUp() override {
    promotion_ = std::make_unique<Promotion>(mock_ledger_impl_.get());
  }  
};

// void Initialize();
// Mock Ledger
// SUCCESS: expect call Promotion::Retry
TEST_F(PromotionTest, TestInitialize) {
  // Arrange
  EXPECT_CALL(*mock_ledger_impl_, GetAllPromotions(_));

  // Act
  promotion_->Initialize();

  // Assert
}

// void Fetch(ledger::FetchPromotionCallback callback);
// Mock Ledger w/ empty payment id
// FAIL: wallet with no payment id; 
// - expect 'callback' with 'ledger::Result:CORRUPTED_WALLET'
// - expect ledger_->OnWalletProperties with with 'ledger::Result:CORRUPTED_WALLET'
TEST_F(PromotionTest, TestFetchWithNoWalletPaymentID) {
  // Arrange

  // Act

  // Assert
}

// Mock Ledger w/ empty passphrase
// FAIL: wallet with no passphrase;
// - expect 'callback' with 'ledger::Result:CORRUPTED_WALLET'
// - expect ledger_->OnWalletProperties with with 'ledger::Result:CORRUPTED_WALLET'
TEST_F(PromotionTest, TestFetchWithNoWalletPassphrase) {
  // Arrange

  // Act

  // Assert
}
// Mock Ledger w/ payment id
// Mock Ledger w/ client info
// Mock Ledger w/ braveledger_request_util::GetFetchPromotionUrl
// SUCCESS: 
// - expect ledger_->LoadURL with expected URL
// OR expect callback Promotion::OnFetch with expected URL
TEST_F(PromotionTest, TestFetch) {
  // Arrange

  // Act

  // Assert
}

// void Claim(
//     const std::string& payload,
//     ledger::ClaimPromotionCallback callback);
// SUCCESS: Expect call Promotion::OnCompletedAttestation
TEST_F(PromotionTest, TestClaim) {
  // Arrange

  // Act

  // Assert
}

// void Attest(
//     const std::string& promotion_id,
//     const std::string& solution,
//     ledger::AttestPromotionCallback callback);

// void Refresh(const bool retry_after_error);
// FAIL: 

// void OnTimer(const uint32_t timer_id);
// SUCCESS: timer_id == last_check_timer_id_;
// - expect call Fetch
// - last_check_timer_id_ = 0
TEST_F(PromotionTest, TestOnTimerWithLastCheckTimerID) {
  // Arrange

  // Act

  // Assert
}

// SUCCESS: timer_id == retry_timer_id_;
// - expect call ledger_->GetAllPromotions
// OR expect call Promotion::Retry
TEST_F(PromotionTest, TestOnTimerWithRetryTimerID) {
  // Arrange

  // Act

  // Assert
}

// FAIL: timer_id != (last_check_timer_id_ or retry_timer_id_)
// - neither expected (above) to be called
TEST_F(PromotionTest, TestOnTimerWithUknownTimerID) {
  // Arrange

  // Act

  // Assert
}

// void ClaimTokens(
//     ledger::PromotionPtr promotion,
//     ledger::ResultCallback callback);

}  // namespace braveledger_promotion
/*
TEST_F(PromotionTest, TestOnTimerWithLastCheckTimerID) {
  // Arrange

  // Act

  // Assert
}
*/