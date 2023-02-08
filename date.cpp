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
    if (_year < 0)
        throw InvalidDate(Invalidity::YEAR_OUT_OF_BOUND);
    if (isLeapYear(_year)) this->_months = LEAPMONTHS;
    else this->_months = NONLEAPMONTHS;
    if (_month < 1 || _month > 12) 
        throw InvalidDate(Invalidity::MONTH_OUT_OF_BOUND);
    if (isLeapYear(_year) && _month == 2 && (_day < 1 || _day > 29))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_29);
    if (!isLeapYear(_year) && _month == 2 && (_day < 1 || _day > 28))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_28);
    if (this->_months[_month] == 30 && (_day < 1 || _day > 30))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_30);
    if (this->_months[_month] == 31 && (_day < 1 || _day > 31))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_31);
    this->_year = _year;
    this->_month = _month;
    this->_day = _day;
}

Date::Date(string _date) {
    std::regex pattern("[0-9]{1,4}\\-[0-9]{1,2}\\-[0-9]{1,2}");
    if (std::regex_match(_date, pattern))
        throw InvalidDate(Invalidity::FORMAT);
    std::istringstream din(_date);
    int _year, _month, _day;
    char dash;
    din >> _year >> dash >> _month >> dash >> _day;
    if (_year < 0)
        throw InvalidDate(Invalidity::YEAR_OUT_OF_BOUND);
    if (isLeapYear(_year)) this->_months = LEAPMONTHS;
    else this->_months = NONLEAPMONTHS;
    if (_month < 1 || _month > 12)
        throw InvalidDate(Invalidity::MONTH_OUT_OF_BOUND);
    if (isLeapYear(_year) && _month == 2 && (_day < 1 || _day > 29))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_29);
    if (!isLeapYear(_year) && _month == 2 && (_day < 1 || _day > 28))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_28);
    if (this->_months[_month] == 30 && (_day < 1 || _day > 30))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_30);
    if (this->_months[_month] == 31 && (_day < 1 || _day > 31))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_31);
    this->_year = _year;
    this->_month = _month;
    this->_day = _day;
}

void Date::year(const int _year) {
    if (_year < 0)
        throw InvalidDate(Invalidity::YEAR_OUT_OF_BOUND);
    if (isLeapYear(_year)) this->_months = LEAPMONTHS;
    else this->_months = NONLEAPMONTHS;
    this->_year = _year;
}

void Date::month(const int _month) {
    if (_month < 1 || _month > 12)
        throw InvalidDate(Invalidity::MONTH_OUT_OF_BOUND);
    this->_month = _month;
}

void Date::day(const int _day) {
    if (_month < 1 || _month > 12)
        throw InvalidDate(Invalidity::MONTH_OUT_OF_BOUND);
    if (isLeapYear(_year) && _month == 2 && (_day < 1 || _day > 29))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_29);
    if (!isLeapYear(_year) && _month == 2 && (_day < 1 || _day > 28))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_28);
    if (this->_months[_month] == 30 && (_day < 1 || _day > 30))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_30);
    if (this->_months[_month] == 31 && (_day < 1 || _day > 31))
        throw InvalidDate(Invalidity::DAY_OUT_OF_BOUND_31);
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
    /*if (_date1._year < _date2._year) return temp;
    map<int, int> _months1;
    if (_date1.isLeapYear()) _months1 = LEAPMONTHS;
    else _months1 = NONLEAPMONTHS;
    map<int, int> _months2;
    if (_date2.isLeapYear()) _months2 = LEAPMONTHS;
    else _months2 = NONLEAPMONTHS;*/
    if (_date1._day < _date2._day) {
        _date1._day += _date1._months[_date1._month--];
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

bool isLeapYear(int _year) {
    return (_year % 4 == 0 || _year % 400 == 0);
}
