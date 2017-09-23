#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__

#include <iostream>
#include "NonPerishable.h"
#include "Date.h"

namespace ict {
	class Perishable : public NonPerishable {
		Date m_expiry;

	protected:
		char signature() const {
			return 'P';
		}

	public:
		Perishable() {
			m_expiry.dateOnly(1);
		}
		
		// stream overloads
		std::fstream& save(std::fstream& file) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& ostr, bool linear) const;
		std::istream& read(std::istream& istr);

	};
}





#endif
