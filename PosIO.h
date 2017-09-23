#ifndef ICT_POSIO_H__
#define ICT_POSIO_H__
#include <iostream>
#include <fstream>

namespace ict {
    
    class PosIO{        
    public:  
        virtual std::fstream& save(std::fstream& file)const = 0;
        virtual std::fstream& load(std::fstream& file) = 0;
        virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
        virtual std::istream& read(std::istream& is) = 0;
       
    };
}
#endif
