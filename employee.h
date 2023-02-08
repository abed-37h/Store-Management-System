#pragma once
#include "user.h"
class Employee :
    public User
{
private:
    static unsigned int _availableId;
    double _wage;
protected:
    istream& input(istream&) override;
    ostream& output(ostream&) const override;
public:
    Employee(const unsigned int = 0, const string = "", const string = "", const string = "", const string = "", const string = "", const Date = Date(), const double = 0.0);
    Employee(const string, const string, const string, const string, const string, const Date = Date());
    Employee(const string, const string);
    ~Employee();
    void wage(const double);
    const double wage(void) const;
    const bool createAccount(void);
    const bool modifyAccount(void);
    const bool deleteAccount(void);
    const bool login(void);
    const bool logout(void);
    void showProfileInfo(void) const;
    const bool refill(const unsigned int, const unsigned int);
    bool operator==(const Employee&);
    /*friend istream& operator>>(istream&, Employee&);
    friend ostream& operator<<(ostream&, const Employee&);*/
};

