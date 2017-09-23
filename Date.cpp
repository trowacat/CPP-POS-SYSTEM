#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include "Date.h"
#include "POS.h"

using namespace std;


namespace ict {

	// !*---- PRIVATE MEMBER FUNCTIONS ----*!

	void Date::set() {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		m_day = lt.tm_mday;
		m_mon = lt.tm_mon + 1;
		m_year = lt.tm_year + 1900;
		if (dateOnly()) {
			m_hour = m_min = 0;
		}
		else {
			m_hour = lt.tm_hour;
			m_min = lt.tm_min;
		}

	}

	//Set the time and set error code to NO_ERROR
	void Date::set(int year, int mon, int day, int hour, int min) {
		this->m_year = year;
		this->m_mon = mon;
		this->m_day = day;
		this->m_hour = hour;
		this->m_min = min;

		errCode(NO_ERROR);
	}

	int Date::value()const {
		return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
	}

	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
	}

	//Set the errCode
	void Date::errCode(int errorCode) {
		this->m_readErrorCode = errorCode;
	}

	/* !*---- END PRIVATE MEMBER-FUNCTIONS ----*!

	   !*---- CONSTRUCTOR FUNCTIONS ----*! */

	Date::Date() {
		this->m_dateOnly = false;
		set();
	}

	Date::Date(int year, int mon, int day) {
		this->m_dateOnly = true;
		this->m_year = year;
		this->m_mon = mon;
		this->m_day = day;

		errCode(NO_ERROR);
	}

	Date::Date(int year, int mon, int day, int hour, int min) {
		this->m_dateOnly = false;
		set(year, mon, day, hour, min);

		errCode(NO_ERROR);
	}

	/* !*---- END CONSTRUCTOR FUNCTIONS ----*!

	   !*---- PUBLIC MEMBER-FUNCTIONS ----*! */

	   // RELATIONAL OPERATOR OVERLOADS:

	bool Date::operator==(const Date& D) const {
		bool isValid;

		if (this->value() == D.value())
			isValid = true;

		else
			isValid = false;

		return isValid;
	}


	bool Date::operator!=(const Date& D) const {
		bool isValid;

		if (this->value() != D.value())
			isValid = true;

		else
			isValid = false;

		return isValid;
	}


	bool Date::operator<(const Date& D) const {
		bool isValid;

		if (this->value() < D.value())
			isValid = true;

		else
			isValid = false;

		return isValid;
	}


	bool Date::operator>(const Date& D) const {
		bool isValid;

		if (this->value() > D.value())
			isValid = true;

		else
			isValid = false;

		return isValid;
	}


	bool Date::operator<=(const Date& D) const {
		bool isValid;

		if (this->value() <= D.value())
			isValid = true;

		else
			isValid = false;

		return isValid;
	}


	bool Date::operator>=(const Date& D) const {
		bool isValid;

		if (this->value() >= D.value())
			isValid = true;

		else
			isValid = false;

		return isValid;
	}

	// ACCESSOR OR GETTER MEMBER-FUNCTIONS:

	int Date::errCode() const {
		return this->m_readErrorCode;
	}

	bool Date::bad() const {
		return this->errCode() != NO_ERROR;
	}

	bool Date::dateOnly() const {
		return this->m_dateOnly;
	}

	void Date::dateOnly(bool value) {
		this->m_dateOnly = value;
		if (value) {
			this->m_hour = 0;
			this->m_min = 0;
		}
	}

	// IO MEMBER-FUNCTIONS:

	istream& Date::read(std::istream& is) {
		bool error = false;
		this->m_readErrorCode = NO_ERROR;
		if (this->m_dateOnly == true) {
			is >> this->m_year;
			is.get();
			is >> this->m_mon;
			is.get();
			is >> this->m_day;
		}

		else {
			is >> this->m_year;
			is.get();
			is >> this->m_mon;
			is.get();
			is >> this->m_day;
			is.get();
			is >> this->m_hour;
			is.get();
			is >> this->m_min;
		}

		if (is.fail()) {
			this->m_readErrorCode = CIN_FAILED;
			
		}
		else {	if (!isValid(m_year, YEAR)) {
				this->m_readErrorCode = YEAR_ERROR;
				error = true;
			}
			if (!isValid(m_mon, MONTH) && error == false){
				this->m_readErrorCode = MON_ERROR;
				error = true;
		}
			if (!isValid(m_day, DAY) && error == false) {
				this->m_readErrorCode = DAY_ERROR;
				error = true;
			}
			if (this->m_dateOnly == false && error == false) {
				if (!isValid(m_hour, HOUR)) {
					this->m_readErrorCode = HOUR_ERROR;
					error = true;
				}
				if (!isValid(m_min, MINUTE) && error == false)
					this->m_readErrorCode = MIN_ERROR;
			}

		}

		return is;
	}

	ostream& Date::write(std::ostream& ostr) const {
		if (this->m_dateOnly) {
			ostr << this->m_year << "/" << setfill('0') << setw(2) << this->m_mon << "/" << setfill('0') << setw(2)  << this->m_day;
		}
		else {
			ostr << this->m_year << "/" << setfill('0') << setw(2) << this->m_mon << "/" << setfill('0') << setw(2) << this->m_day << ", " << this->m_hour << ":" << this->m_min;
		}

		return ostr;
	}


	// NON-MEMBER IO OPERATOR OVERLOADS [[HELPERS]]
	
	std::istream& operator >> (std::istream& is, Date& date) {
		date.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& date) {
		date.write(os);
		return os;
	}
	 
	// MY FUNCTIONS

	bool Date::isValid(int value, int type) {
		bool isValid = true;
		if (type == YEAR) {
			if (value < MIN_YEAR || value > MAX_YEAR)
				isValid = false;
		}
		if (type == MONTH) {
			if (value < 1 || value > 12)
				isValid = false;
		}
		if (type == DAY) {
			if (value < 1 || value > 31)
				isValid = false;
		}
		if (type == HOUR) {
			if (value < 0 || value > 24)
				isValid = false;
		}
		if (type == MINUTE) {
			if (value < 0 || value > 59)
				isValid = false;
		}

		return isValid;
	}


}