#include "Date.h"

#define NONLEAPMONTHS { {1,31}, {2,28}, {3,31}, {4,30}, {5,31}, {6,30}, {7,31}, {8,31}, {9,30}, {10,31}, {11,30}, {12,31} }
#define LEAPMONTHS { {1,31}, {2,29}, {3,31}, {4,30}, {5,31}, {6,30}, {7,31}, {8,31}, {9,30}, {10,31}, {11,30}, {12,31} }

Date::Date() {
    time_t secondsSinceEpoch = time(0);
    tm now;
    localtime_s(&now, &secondsSinceEpoch);
    this->_year = now.tm_year + 1900;
    this->_month = now.tm_mon + 1;
    this->_day = now.tm_mday;
}

Date::Date(int _year, int _month, int _day) {
    this->_year = _year;
    this->_month = _month;
    this->_day = _day;
}

Date::Date(string _date) {
    std::istringstream din(_date);
    char dash;
    din >> this->_year >> dash >> this->_month >> dash >> this->_day;
}

void Date::year(const int _year) {
    this->_year = _year;
}

void Date::month(const int _month) {
    this->_month = _month;
}

void Date::day(const int _day) {
    this->_day = _day;
}

const int Date::year(void)const {
    return this->_year;
}

const int Date::month(void)const {
    return this->_month;
}

const int Date::day(void)const {
    return this->_day;
}

bool Date::isLeapYear(void)const {
    return (this->_year % 4 == 0 || this->_year % 400 == 0) ? true : false;
}

bool Date::operator==(const Date& _date) const {
    return (this->_year == _date._year && this->_month == _date._month && this->_day == _date._day);
}

bool Date::operator<(const Date& _date) const {
    return (this->_year < _date._year || this->_month < _date._month || this->_day < _date._day);
}

bool Date::operator>(const Date& _date) const {
    return (this->_year > _date._year || this->_month > _date._month || this->_day > _date._day);
}

istream& operator>>(istream& in, Date& _date) {
    char dash;
    in >> _date._year >> dash >> _date._month >> dash >> _date._day;
    return in;
}

ostream& operator<<(ostream& out, const Date& _date) {
    out << _date._year << '-' << _date._month << '-' << _date._day;
    return out;
}

Date operator-(Date _date1, Date _date2) {
    Date temp(-1, -1, -1);
    if (_date1._year < _date2._year) return temp;
    map<int, int> _months1;
    if (_date1.isLeapYear()) _months1 = LEAPMONTHS;
    else _months1 = NONLEAPMONTHS;
    map<int, int> _months2;
    if (_date2.isLeapYear()) _months2 = LEAPMONTHS;
    else _months2 = NONLEAPMONTHS;
    if (_date1._day < _date2._day) {
        _date1._day += _months1[_date1._month--];
    }
    if (_date1._month < _date2._month) {
        _date1._month += 12;
        _date1._year--;
    }
    temp._day = _date1._day - _date2._day;
    temp._month = _date1._month - _date2._month;
    temp._year = _date1._year - _date2._year;
    return temp;
}
