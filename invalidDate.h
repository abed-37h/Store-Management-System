#pragma once
#include <exception>
#include <string>

enum class Invalidity
{
    FORMAT = 1,
    YEAR_OUT_OF_BOUND,
    MONTH_OUT_OF_BOUND = 12,
    DAY_OUT_OF_BOUND_31 = 31,
    DAY_OUT_OF_BOUND_30 = 30,
    DAY_OUT_OF_BOUND_29 = 29,
    DAY_OUT_OF_BOUND_28 = 28
};

class InvalidDate :
    public std::exception
{
public:
    char* message;
    InvalidDate(Invalidity);
    InvalidDate(const char*);
    //InvalidDate(InvalidDate&);
    ~InvalidDate(void);
    const char* what(void) const;
    //const InvalidDate operator=(InvalidDate&);
};

