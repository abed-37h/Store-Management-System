#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
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
    bool isLeapYear(void)const;
    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);
    friend Date operator-(Date, Date);
};

