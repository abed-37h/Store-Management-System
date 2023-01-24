#pragma once
#include "user.h"
class Employee :
    public User
{
private:
    double _wage;
public:
    Employee(const unsigned int = 0, const string = "", const string = "", const string = "", const string = "", const string = "", const Date = Date(), const double = 0.0);
    Employee(const string, const string, const string, const string, const string, const Date = Date());
    Employee(const string, const string);
    ~Employee();
    void wage(const double);
    const double wage(void)const;
    const bool createAccount(void);
    const bool modifyAccount(void);
    const bool deleteAccount(void);
    const bool login(void);
    const bool logout(void);
    const bool refill(Product, const unsigned int);
    bool operator==(const Employee&);
    /*friend istream& operator>>(istream&, Employee&);
    friend ostream& operator<<(ostream&, const Employee&);
    friend istringstream& operator>>(istringstream&, Employee&);*/
};

