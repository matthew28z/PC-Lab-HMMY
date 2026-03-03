#ifndef CONTEST
#include "fullratio.hpp"
#endif

#include <iostream>

rational::rational(int n, int d) : nom(n), den(d) {
    //Aplopoihsh
    int common = gcd(nom, den);
    nom /= common;
    den /= common;

    if (nom == 0) {
        den = 1;
    } else if (den < 0) { //Fernei to prosimo panw h ta antistrefei
        nom *= -1;
        den *= -1;
    } 
}

rational operator + (const rational& x, const rational& y) {
    int a = x.nom * y.den + y.nom * x.den;
    int b = x.den * y.den;

    return rational(a, b);
}

rational operator - (const rational& x, const rational& y) {
    int a = x.nom * y.den - y.nom * x.den;
    int b = x.den * y.den;

    return rational(a, b);
}

rational operator * (const rational& x, const rational& y) {
    int a = x.nom * y.nom;
    int b = x.den * y.den;

    return rational(a, b);
}

rational operator / (const rational& x, const rational& y) {
    return x * rational(y.den, y.nom);
}

std::ostream& operator << (std::ostream& out, const rational& x) {
    out << x.nom << '/' << x.den;

    return out;
}

int rational::gcd(int a, int b) {
    a = abs(a);
    b = abs(b); //den xreiazetai alla to exw balei gia sigouria

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}
