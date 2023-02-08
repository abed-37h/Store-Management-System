#pragma once
#include "invalidDate.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <regex>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::map;

class Date
{
private:
    map<int, int> _months;
    int _year;
    int _month;
    int _day;
public:
    Date();
    Date(int, int, int);
    Date(string);
    void year(const int);
    void month(const int);
    void day(const int);
    const int year(void)const;
    const int month(void)const;
    const int day(void)const;
    bool operator==(const Date&) const;
    bool operator<(const Date&) const;
    bool operator>(const Date&) const;
    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);
    friend Date operator-(Date, Date);
};

bool isLeapYear(int);

