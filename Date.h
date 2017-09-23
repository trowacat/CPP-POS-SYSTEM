// compilation safegaurds
#ifndef ICT_DATE_H
#define ICT_DATE_H

#include <iostream>
// ict namespace 
namespace ict {
   // Date defined Error values
	#define ICT_DATE_H
	#define NO_ERROR 0
	#define CIN_FAILED 1
	#define YEAR_ERROR 2
	#define MON_ERROR 3
	#define DAY_ERROR 4
	#define HOUR_ERROR 5
	#define MIN_ERROR 6
	#define YEAR 0
	#define MONTH 1
	#define DAY 2
	#define HOUR 3
	#define MINUTE 4


   class Date {
   private:
	   int m_year, m_mon, m_day, m_hour, m_min, m_readErrorCode;
	   bool m_dateOnly;

     // private methods
      int value()const;
	  void errCode(int errorCode);
	  int mdays() const;

   public:
	   // Constructors
	   Date();
	   Date(int year, int mon, int day);
	   Date(int year, int mon, int day, int hour, int min = 0);

      // operator ovrloads
	  bool operator==(const Date& D) const;
	  bool operator!=(const Date& D) const;
	  bool operator<(const Date& D) const;
	  bool operator>(const Date& D) const;
	  bool operator<=(const Date& D) const;
	  bool operator>=(const Date& D) const;

      // methods
	  void set();
	  int errCode() const;
	  bool bad() const;
	  bool dateOnly() const;
	  void dateOnly(bool value);
	  bool isValid(int value, int type);
	  void set(int year, int mon, int day, int hour, int min);

      // istream  and ostream read and write methods
	  std::istream& read(std::istream& is = std::cin);
	  std::ostream& write(std::ostream& ostr = std::cout) const;

   };

   // operator<< and >> overload prototypes for cout and cin
	 std::istream& operator >> (std::istream& is, Date& date);
     std::ostream& operator<<(std::ostream& os, const Date& date);
   
}

#endif