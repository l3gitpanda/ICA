#include <iostream>
#include <string>
#include "accountsDatabase.h"

static int failures = 0;

void expect(bool cond, const std::string& msg) {
    if (!cond) {
        std::cerr << "FAIL: " << msg << "\n";
        ++failures;
    } else {
        std::cout << "OK: " << msg << "\n";
    }
}

int main() {
    AccountsDatabase db;

    // 1) success case
    AccountStatus s1 = db.addAccount("bill@example.com", "Secur3!Pass");
    expect(s1 == AccountStatus::kSuccess, "create valid account should succeed");

    const AccountRecord* r = db.findByEmail("bill@example.com");
    expect(r != nullptr, "findByEmail should return record for existing email");
    if (r) {
        expect(r->email == "bill@example.com", "stored email matches");
        expect(r->userId >= 100000, "userId assigned");
        expect(r->passwordHash != "Secur3!Pass", "password stored as hash, not plaintext");
    }

    // 2) invalid email
    AccountStatus s2 = db.addAccount("bademail", "Secur3!Pass");
    expect(s2 == AccountStatus::kInvalidEmail, "invalid email rejected");

    // 3) weak password
    AccountStatus s3 = db.addAccount("alice@example.com", "weak");
    expect(s3 == AccountStatus::kWeakPassword, "weak password rejected");

    // 4) duplicate email
    AccountStatus s4 = db.addAccount("bill@example.com", "Another1!");
    expect(s4 == AccountStatus::kDuplicateEmail, "duplicate email rejected");

    // 5) find non-existent
    const AccountRecord* none = db.findByEmail("noone@example.com");
    expect(none == nullptr, "findByEmail returns nullptr for unknown email");

    if (failures == 0) {
        std::cout << "All tests passed.\n";
        return 0;
    } else {
        std::cerr << failures << " test(s) failed.\n";
        return 1;
    }
}