#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__

#include "PosIO.h"
#include "POS.h"

namespace ict{
    // class Item
    
    class Item : public PosIO{
        char m_sku[MAX_SKU_LEN + 1];
        char *m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;
        
    public:
        Item(); 
        Item(const char*, const char*, double = 0.0, bool = true);    
        
        Item(const Item& I);   
        Item& operator=(const Item &I); 
        virtual ~Item(); 
        
        //Setters AND Getters
        void sku(const char* sku);
        void price(double price);
        void name(const char* name);
        void taxed(bool taxed);
        void quantity(int quantity);
  
        const char* sku()const;
        double price()const;
        const char *name()const;
        bool taxed()const;
        int quantity()const;
        double cost()const;
        bool isEmpty()const;
        
        //Member Operator overloads
        bool operator == (const char *sku);
        int operator += (int item);
        int operator -= (int quantity);
        
    };
    
    // operator +=
    double operator+=(double& d, const Item& I);
    
    // operator << and operator >>
    std::ostream& operator<<(std::ostream& os, const Item& I);
    std::istream& operator>>(std::istream& is, Item &I);
}


#endif
