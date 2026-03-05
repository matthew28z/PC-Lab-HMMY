#ifndef CONTEST
#include "babyratio.hpp"
#endif
#include <iostream>
#include <cmath>

using namespace std;

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

rational rational::add(rational r) {
    int a = nom * r.den + r.nom * den;
    int b = den * r.den;

    return rational(a, b);
}

rational rational::sub(rational r) {
    int a = nom * r.den - r.nom * den;
    int b = den * r.den;

    return rational(a, b);
}

rational rational::mul(rational r) {
    int a = nom * r.nom;
    int b = den * r.den;

    return rational(a, b);
}

rational rational::div(rational r) {
    return  mul(rational(r.den, r.nom));
}

void rational::print() {
    cout << nom << '/' << den;
}

int rational::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}
