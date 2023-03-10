#pragma once
#include "user.h"
#include "product.h"
class Dealer :
    public User
{
private:
    static unsigned int _availableId;
public:
    Dealer(const unsigned int = 0, const string = "", const string = "", const string = "", const string = "", const string = "", const Date = Date());
    Dealer(const string, const string, const string, const string, const string, const Date = Date());
    Dealer(const string, const string);
    ~Dealer();
    const bool createAccount(void) override;
    const bool modifyAccount(void) override;
    const bool deleteAccount(void) override;
    const bool login(void) override;
    const bool logout(void) override;
    const bool addItem(Product);
    const bool removeItem(const unsigned int);
    const bool refill(const unsigned int, const unsigned int);
    /*bool operator==(const Dealer&);
    friend istream& operator>>(istream&, Dealer&);
    friend ostream& operator<<(ostream&, const Dealer&);
    friend istringstream& operator>>(istringstream&, Dealer&);*/
};

