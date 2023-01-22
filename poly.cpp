#include "poly.hpp"

#include <sstream>

int Poly::operator[](int exp) const {
    auto it = values_.find(exp);
    return it == values_.end() ? 0 : it->second;
}
Poly& Poly::operator+=(const Poly& b){
    for(auto it = b.crbegin(), end = b.crend(); it != end; it++){
    values_[it->first] += it->second;
    }
    return *this;
    }
    
Poly& Poly::operator-=(const Poly& b){
    return *this += -b;
}
std::istream& operator>>(std::istream& is, Poly& p){
   std::string line;
   if(!(is >> line)){
    return is;
   }
   std::istringstream a(line);
   Poly h;

   bool fail = false;
   for(int i, exp; a >> i;){
    if (a.get() == 'x' && a >> exp){
        h[exp] += i;
        continue;
    }
    fail = true;
    break;
   }
   if(!a.eof())
    fail = true;
   
   if(fail){
    is.clear((is.rdstate() & ~std::ios::goodbit) | std::ios::failbit);
   }
   else{
    p = h;
   }
   return is;
}
std::ostream& operator<<(std::ostream& os, const Poly& p){
    auto it = p.crbegin();
    auto end = p.crend();
    while(it != end) {
        os << it->second << "x" << it->first;
        it++;
        if(it != end){
            if (it->second == 0){
                os << "+";
            }
        }
    }
    return os;
}
Poly operator-(const Poly& p){
    Poly t;
    for(auto it = p.crbegin(), end = p.crend(); it != end; it++){
    t[it->first] = -it->second;
    }
    return t;
}
bool operator<(const Poly& a, const Poly& b){
    auto i = a.crbegin(), j = b.crbegin(), k = a.crend(), l = b.crend();
    while (i != k && i->second == 0){
        i++;
    }
    while (j != l && j->second == 0){
        j++;
    }
    if(i == k || j == l){
        return i == k && j != l;
    }
    return i->first < k->first;
}
bool operator==(const Poly& a, const Poly& b){
    return !(a < b) && !(b < a);
}
bool operator>(const Poly& a, const Poly& b){
    return b < a;
}
bool operator!=(const Poly& a, const Poly& b){
    return !(a == b);
}
Poly operator+(const Poly& a, const Poly& b){
    return Poly(a) += b;
}
Poly operator-(const Poly& a, const Poly& b){
    return Poly(a) -= b;
}

