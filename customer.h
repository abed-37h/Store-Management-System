#pragma once
#include "user.h"
#include "cart.h"
class Customer :
    public User
{
private:
    double _balance;
    Cart _cart;
protected:
    istream& input(istream&) override;
    ostream& output(ostream&) const override;
public:
    Customer(const unsigned int = 0, const string = "", const string = "", const string = "", const string = "", const string = "", const Date = Date(), const double = 0.0);
    Customer(const string, const string, const string, const string, const string, const Date = Date(), const double = 0.0);
    Customer(const string, const string);
    ~Customer(void);
    void balance(const double);
    const double balance(void)const;
    const bool createAccount(void);
    const bool modifyAccount(void);
    const bool deleteAccount(void);
    const bool login(void);
    const bool logout(void);
    void showProfileInfo(void)const;
    const bool addProductToCart(const string, const unsigned int = 1);
    const bool modifyProductQunatityInCart(const string, const unsigned int);
    const bool removeProductFromCart(const string);
    void viewCart(void)const;
    bool purchase(void);
    bool operator==(const Customer&);
    /*friend istream& operator>>(istream&, Customer&);
    friend ostream& operator<<(ostream&, const Customer&);*/
};

