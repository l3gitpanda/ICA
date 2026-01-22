#ifndef SERVICE_CHARGE_CHECKING_TYPE_H
#define SERVICE_CHARGE_CHECKING_TYPE_H

#include "bankAccountType.h"
#include <string>

class serviceChargeCheckingType : public bankAccountType
{
public:
    serviceChargeCheckingType(const std::string& name, int accountNumber, double balance);

    void withdraw(double amount) override;
    void print() const override;

private:
    double serviceFee_ = 5.00;
};

#endif
