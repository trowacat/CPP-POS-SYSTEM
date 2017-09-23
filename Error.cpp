#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>
#include "Error.h"

namespace ict {

	// CONSTRUCTORS

	Error::Error() {
		this->m_message = nullptr;
	}

	Error::Error(const char* errorMessage) {
		this->m_message = nullptr;
		message(errorMessage);
	}


	// DECONSTRUCTOR

	Error::~Error() {
		clear();
	}

	// PUBLIC MEMBER-FUNCTIONS AND OPERATOR OVERLOADS

	void Error::operator=(const char* errorMessage) {
		clear();
		message(errorMessage);
	}

	void Error::clear() {
		delete[] this->m_message;
		this->m_message = nullptr;
	}

	bool Error::isClear() const {
		bool isValid = false;
		if (this->m_message == nullptr) {
			isValid = true;
		}

		return isValid;
	}

	void Error::message(const char* value) {
		char* errorMessage = nullptr;
		int size = strlen(value);
		errorMessage = new char[size + 1];
		strcpy(errorMessage, value);
		clear();
		this->m_message = errorMessage;

	}

	Error::operator const char*() const {
		return this->m_message;
	}

	Error::operator bool() const {
		return isClear();
	}

	std::ostream& operator<<(std::ostream& os, const Error& Error) {
		if (!Error.isClear()) {
			os << Error.m_message;
		}

		return os;

	}
}