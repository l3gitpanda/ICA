#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "accountsDatabase.h"

static int failures = 0;

void expect(bool cond, const std::string& msg) {
    if (!cond) {
        std::cerr << "FAIL: " << msg << "\n";
        ++failures;
    } else {
        std::cout << "OK:   " << msg << "\n";
    }
}

void printRecord(const AccountRecord* r) {
    if (!r) {
        std::cout << "  <not stored>\n";
        return;
    }
    std::cout << "  email:        " << r->email << '\n';
    std::cout << "  userId:       " << r->userId << '\n';
    std::cout << "  passwordHash: " << r->passwordHash << '\n';
}

int main() {
    AccountsDatabase db;

    // Test cases: tuple(email, password, expected status)
    struct Case { std::string email; std::string password; AccountStatus expected; std::string desc; };
    std::vector<Case> cases = {
        {"bill@example.com", "Secur3!Pass", AccountStatus::kSuccess, "valid account (bill)"},
        {"bademail",         "Secur3!Pass", AccountStatus::kInvalidEmail, "invalid email (no @/.)"},
        {"alice@example.com","weak",        AccountStatus::kWeakPassword, "weak password"},
        {"bill@example.com", "Another1!",   AccountStatus::kDuplicateEmail, "duplicate email (bill)"},
        {"bob@example.com",  "An0ther$Pass",AccountStatus::kSuccess, "valid account (bob)"}
    };

    std::cout << "Running addAccount test cases...\n\n";
    for (const auto& c : cases) {
        AccountStatus s = db.addAccount(c.email, c.password);
        std::cout << "Attempt: " << c.desc << " -> addAccount(\"" << c.email << "\", \"" << c.password << "\") returned: "
                  << AccountsDatabase::statusMessage(s) << '\n';
        expect(s == c.expected, "expected " + AccountsDatabase::statusMessage(c.expected));
    }

    std::cout << "\nDatabase contents (by attempted email):\n";
    std::set<int> seenUserIds;
    for (const auto& c : cases) {
        std::cout << "- Lookup: " << c.email << '\n';
        const AccountRecord* r = db.findByEmail(c.email);
        printRecord(r);

        if (r) {
            // check hashed password is not the plaintext
            expect(r->passwordHash != c.password, "password stored as hash (not plaintext) for " + c.email);

            // collect userIds for uniqueness check later
            seenUserIds.insert(r->userId);

            // basic email match check
            expect(r->email == c.email, "stored email matches query for " + c.email);
        } else {
            // for cases that expected success, failing to find is an error
            if (c.expected == AccountStatus::kSuccess) {
                expect(false, "expected record for " + c.email + " but findByEmail returned nullptr");
            } else {
                expect(true, "no record stored for invalid/duplicate case " + c.email);
            }
        }
        std::cout << '\n';
    }

    // Additional checks:
    // - Ensure user IDs assigned are unique (for stored records)
    std::size_t storedCount = 0;
    for (const auto& c : cases) {
        if (db.findByEmail(c.email) != nullptr) ++storedCount;
    }
    expect(seenUserIds.size() == storedCount, "userIds are unique across stored accounts");

    // - Ensure program did not crash during invalid attempts (reaching here implies no crash).
    expect(true, "program continued after invalid/duplicate insert attempts");

    if (failures == 0) {
        std::cout << "\nAll tests passed.\n";
        return 0;
    } else {
        std::cerr << "\n" << failures << " test(s) failed.\n";
        return 1;
    }
}
