#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include <iomanip>
#include "NonPerishable.h"

using namespace std;


namespace ict {
	bool NonPerishable::ok() const {
		return (m_err.isClear());
	}

	void NonPerishable::error(const char* message) {
		m_err.message(message);
	}

	char NonPerishable::signature() const {
		return 'N';
	}

	std::fstream& NonPerishable::save(std::fstream& file) const {
		file << signature() << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity();
		return file;
	}

	std::fstream& NonPerishable::load(std::fstream& file) {
		char tempSku[MAX_SKU_LEN];
		char tempName[20];
		double tempPrice;
		int tempTaxed;
		int tempQuantity;
		
		file.getline(tempSku, MAX_SKU_LEN, ',');
		file.getline(tempName, 20, ',');
		file >> tempPrice;
		file.ignore(20, ',');
		file >> tempTaxed;
		file.ignore(20, ',');
		file >> tempQuantity;
		file.ignore(20, ',');

		sku(tempSku);
		name(tempName);
		price(tempPrice);

		if (tempTaxed == 1) {
			taxed(true);
		}
		else {
			taxed(false);
		}
		quantity(tempQuantity);

		return file;
	}


	ostream& NonPerishable::write(ostream& ostr, bool linear) const {
		if (!m_err.isClear()) {
			ostr << m_err;
		}
		else {
			if (linear) {
				ostr << setfill(' ') << left << setw(MAX_SKU_LEN) << sku() << '|'
					<< left << setw(20) << name() << '|'
					<< right << fixed << setw(7) << setprecision(2) << price();

				if (this->taxed())
					ostr << "| T" << this->signature() << "|";
				else
					ostr << "|  " << this->signature() << "|";
				ostr.width(4);
				ostr << quantity() << "|";
				ostr.width(9);
				ostr << (quantity()) * (cost()) << "|";

			}
			else {
				if (this->taxed()) {
					ostr << "Name:" << endl << this->name() << endl
						<< "Sku: " << this->sku() << endl
						<< "Price: " << this->price() << endl
						<< "Price after tax: " << this->cost() << endl
						<< "Quantity: " << this->quantity() << endl
						<< "Total Cost: " << this->cost() * this->quantity() << endl;
				}
				else {
					ostr
						<< "Name:" << endl << this->name() << endl
						<< "Sku: " << this->sku() << endl
						<< "Price: " << this->price() << endl
						<< "Price after tax: " << "N/A" << endl
						<< "Quantity: " << this->quantity() << endl
						<< "Total Cost: " << this->cost() * this->quantity() << endl;
				}
			}
		}
		return ostr;
	}

	std::istream& NonPerishable::read(std::istream& is) {
		char tempSku[MAX_SKU_LEN + 1], tempName[500], tempTaxed;
		int tempQuantity;
		double tempPrice;

		cout << "Item Entry:" << endl;

		cout << "Sku: ";
		is >> tempSku;
		is.ignore(100, '\n');
		cout << "Name:\n";
		is >> tempName;
		is.ignore(100, '\n');

		cout << "Price: ";
		is >> tempPrice;
		is.ignore(100, '\n');

		if (!is.fail() && !is.bad()) {
			is.clear();
			m_err.clear();

			cout << "Taxed: ";
			is >> tempTaxed;

			if (tempTaxed == 'Y' || tempTaxed == 'y' || tempTaxed == 'N' || tempTaxed == 'n') {
				m_err.clear();

				cout << "Quantity: ";
				is >> tempQuantity;


				if (!is.fail() && !is.bad()) {
					is.clear();
					m_err.clear();
				} else {
					m_err = "Invalid Quantity Entry";
					is.setstate(ios::failbit);
				}
			} else {
				m_err = "Invalid Taxed Entry, (y)es or (n)o";
				is.setstate(ios::failbit);
			}

		} else {
			m_err = "Invalid Price Entry";
			is.setstate(ios::failbit);
		}


		if (!is.fail() && !is.bad()) {
			sku(tempSku);
			name(tempName);
			tolower(tempTaxed) == 'y' ? taxed(true) : taxed(false);
			price(tempPrice);
			quantity(tempQuantity);
		}

		return is;
	}
}
