#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <string>
#include <iostream>
#include <fstream>
#include "Perishable.h"

using namespace std;

namespace ict {

	fstream& Perishable::save(fstream& file)const {
		NonPerishable::save(file);
		file << ',' << m_expiry;

		return file;
	}

	fstream& Perishable::load(fstream& file) {
		NonPerishable::load(file);
		file.ignore();
		file >> m_expiry;

		return file;
	}

	ostream& Perishable::write(ostream& ostr, bool linear)const {
		NonPerishable::write(ostr, linear);
		if (ok() && linear == 0) {
			cout << "Expiry date: " << m_expiry << endl;
		}

		return ostr;
	}

	istream& Perishable::read(istream& is) {
		cout << "Perishable ";

		NonPerishable::read(is);

		if (!is.fail()) {
			cout << "Expiry date (YYYY/MM/DD): ";
			is >> m_expiry;

			if (m_expiry.bad()) {
				switch (m_expiry.errCode()) {

				case CIN_FAILED:
					NonPerishable::error("Invalid Date Entry");
					break;


				case YEAR_ERROR:
					NonPerishable::error("Invalid Year in Date Entry");
					break;

				case MON_ERROR:
					NonPerishable::error("Invalid Month in Date Entry");
					break;

				case DAY_ERROR:
					NonPerishable::error("Invalid Day in Date Entry");
					break;
				}
				is.setstate(ios::failbit);
			}
		}

		return is;
	}



}