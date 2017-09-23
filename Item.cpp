#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include "Item.h"

using namespace std;

namespace ict{
    
    //CONSTRUCTORS AND DECONSTRUCTORS
    
    Item::Item(){    
		m_price = 0;
        m_sku[0] = '\0';
        m_name = nullptr;
		m_quantity = 0;
        m_taxed = false;

    }
    
    
    Item::Item(const char *sku, const char *name, double price, bool tax){     
        strcpy(m_sku, sku);
        m_sku[MAX_SKU_LEN + 1] = '\0';
        m_name = new char[strlen(name) + 1];
        strcpy(m_name, name);
        m_quantity = 0;
        m_taxed = tax;
		m_price = price;

    }
    
    Item::~Item(){
        m_name = nullptr;
        delete[] m_name;
        
    }
    
    
    Item::Item(const Item& I){
        strcpy(m_sku, I.m_sku);
        m_name = new char[strlen(I.m_name) + 1];
        strcpy(m_name, I.m_name);
        m_price = I.m_price;
        m_taxed = I.m_taxed;
        m_quantity = I.m_quantity;
    }
    
    
    Item& Item::operator=(const Item &I){
        if(this != &I){
            
            strcpy(m_sku, I.m_sku);
            
            if(m_name != nullptr){
                delete[] m_name;
            }
            
            m_name = new char[strlen(I.m_name) + 1];
            strcpy(m_name, I.m_name);
            m_price = I.m_price;
            m_taxed = I.m_taxed;
            m_quantity = I.m_quantity;
        }
        return *this;
    }
    
// GETTER FUNCTIONS
    
    const char* Item::sku()const{
return m_sku;
        
    }
    
    
    double Item::price()const{
        return m_price;
    }
    
    
    const char* Item::name()const{
        return m_name;
    }
    
    
    bool Item::taxed()const{
        return m_taxed;
    }
    
    
    int Item::quantity()const{
        return m_quantity;
    }
    
    
    
    double Item::cost()const{
        
        double beforeTax;
        
        if(m_taxed){
            beforeTax = m_price * TAX;
            return beforeTax + m_price;
        }else{
            return m_price;

        }
    }
    
    bool Item::isEmpty()const{
        
        if(m_sku[0] == 0 && m_name == nullptr && m_price == 0 && m_quantity == 0){
            return true;
        }else{
            return false;
        }
    }
// SETTER FUNCTIONS
   
    void Item::price(double price){
        m_price = price;
    }

	void Item::sku(const char* sku) {
		strncpy(m_sku, sku, MAX_SKU_LEN);
	}
    
    void Item::name(const char* name){
        delete[] m_name;
        m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
    }
    
    void Item::quantity(int quantity){
        m_quantity = quantity;
    }
    
	void Item::taxed(bool taxed) {
		m_taxed = taxed;
	}

 // MEMBER OPERATOR OVERLOADS

	int Item::operator += (int quantity) {
		return m_quantity += quantity;
	}

    
    bool Item::operator == (const char* sku){
        return strcmp(m_sku, sku) == 0;
    }
    
    
    int Item::operator -= (int quantity){
        return m_quantity -= quantity;
    }
    
    
    // NON MEMBER OPERATORS
    double operator+=(double& d, const Item& I){  
        d = I.quantity() * I.cost();
        return d;
    }
    
    
    std::ostream& operator<<(std::ostream& os, const Item& I){
        return I.write(os, true);
    }
    
    std::istream& operator>>(std::istream& is, Item &I){
        return I.read(is);
    }
    
}
