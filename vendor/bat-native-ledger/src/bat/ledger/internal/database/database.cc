/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>
#include <utility>

#include "bat/ledger/internal/database/database.h"
#include "bat/ledger/internal/ledger_impl.h"

using std::placeholders::_1;

namespace {

const int kCurrentVersionNumber = 12;
const int kCompatibleVersionNumber = 1;


ledger::DBTransactionPtr CreateTransaction() {
  auto transaction = ledger::DBTransaction::New();
  transaction->version = kCurrentVersionNumber;
  transaction->compatible_version = kCompatibleVersionNumber;

  return transaction;
}

}  // namespace

namespace braveledger_database {

Database::Database(bat_ledger::LedgerImpl* ledger) :
    ledger_(ledger) {
}

Database::~Database() = default;

void Database::Initialize(ledger::ResultCallback callback) {
  auto transaction = CreateTransaction();
  auto command = ledger::DBCommand::New();
  command->type = ledger::DBCommand::Type::INITIALIZE;
  transaction->commands.push_back(std::move(command));

  InitializeTables(transaction.get());

  ledger_->RunDBTransaction(
      std::move(transaction),
      std::bind(&Database::OnInitialize,
                this,
                _1,
                callback));
}

void Database::OnInitialize(
    ledger::DBCommandResponsePtr response,
    ledger::ResultCallback callback) {
  auto result = ledger::Result::LEDGER_OK;
  if (response->status != ledger::DBCommandResponse::Status::OK) {
    result = ledger::Result::DATABASE_INIT_FAILED;
  }

  callback(result);
}

void Database::InitializeTables(ledger::DBTransaction* transaction) {
  const std::string query =
      "CREATE TABLE IF NOT EXISTS test_db ("
        "field_1 INTEGER DEFAULT 0 NOT NULL,"
        "field_2 INTEGER DEFAULT 0 NOT NULL"
      ")";

  auto command = ledger::DBCommand::New();
  command->type = ledger::DBCommand::Type::EXECUTE;
  command->command = query;
  transaction->commands.push_back(std::move(command));
}

}  // namespace braveledger_database