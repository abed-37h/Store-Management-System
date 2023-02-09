#include "invalidDate.h"
#include <cstring>
#include <iostream>

InvalidDate::InvalidDate(Invalidity _invalidity) {
	if (_invalidity == Invalidity::FORMAT)
		this->message = (char*)"Invalid date: Incorrect format.";
	else if (_invalidity == Invalidity::MONTH_OUT_OF_BOUND)
		this->message = (char*)"Invalid date: Month must be in the range of 1-12.";
	else if (_invalidity == Invalidity::DAY_OUT_OF_BOUND_31)
		this->message = (char*)"Invalid date: Day must be in the range of 1-31.";
	else if (_invalidity == Invalidity::DAY_OUT_OF_BOUND_30)
		this->message = (char*)"Invalid date: Day must be in the range of 1-30.";
	else if (_invalidity == Invalidity::DAY_OUT_OF_BOUND_29)
		this->message = (char*)"Invalid date: Day must be in the range of 1-29.";
	else if (_invalidity == Invalidity::DAY_OUT_OF_BOUND_28)
		this->message = (char*)"Invalid date: Day must be in the range of 1-28.";
	else this->message = (char*)"Invalid date.";
}

InvalidDate::InvalidDate(const char* message) {
	this->message = (char*)message;
	/*size_t length = strlen(message) + 1;
	message = new char[length];
	strcpy_s(this->message, length, message);*/
}

InvalidDate::~InvalidDate(void) {
	delete message;
}

const char* InvalidDate::what(void) const {
	//std::cerr << "invalid date: ";
	return message;
}

/*const InvalidDate InvalidDate::operator=(InvalidDate& _right) {
	if (this == &_right) return *this;
	delete[] this->message;
	size_t length = strlen(_right.message) + 1;
	this->message = new char[length];
	strcpy_s(this->message, length, _right.message);
	return *this;
}*/
